//
// Created by carlos on 10-3-24.
//

//
// Created by carlos on 11-2-24.
//

#include "order.h"
#include "dydx_config.h"

#include "cosmos/crypto/secp256k1/keys.pb.h"
#include "cosmos/tx/signing/v1beta1/signing.pb.h"
#include "cosmos/tx/v1beta1/tx.pb.h"
#include "cosmos_proto/cosmos.pb.h"
#include "dydxprotocol/clob/order.pb.h"
#include "dydxprotocol/clob/tx.pb.h"

#include "secp256k1.h"

#include <spdlog/spdlog.h>

int quickPow10(int n) {
    static int pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

    return pow10[n];
}

uint64_t calculateQuantums(double size, int32_t atomic_resolution, uint64_t step_base_quantums) {
    int exponent = -1 * atomic_resolution;
    double pow = exponent < 10 ? quickPow10(exponent) : std::pow(10, exponent);
    auto rawQuantums = size * pow;
    return std::max(static_cast<uint64_t>(std::round(rawQuantums)), step_base_quantums);
}

uint64_t calculateSubticks(double price, int32_t atomic_resolution, int32_t quantum_conversion_exponent, uint64_t subticks_per_tick) {
    static constexpr int32_t quoteQuantumsAtomicResolution = -6;
    auto exponent = atomic_resolution - quantum_conversion_exponent - quoteQuantumsAtomicResolution;
    double pow = exponent < 10 ? quickPow10(exponent) : std::pow(10, exponent);
    auto rawSubticks = price * pow;
    auto subticks = static_cast<uint64_t>(std::round(rawSubticks));
    return std::max(subticks, subticks_per_tick);
}

dydxprotocol::clob::MsgPlaceOrder generatePlaceOrderMessage(const std::string& address, uint32_t subaccount_number, uint32_t order_cid, uint32_t clob_pair_id,
                                                            dydxprotocol::clob::Order_Side side, dydxprotocol::clob::Order_TimeInForce time_in_force,
                                                            uint64_t quantums, uint64_t subticks, uint32_t good_till,
                                                            dydxprotocol::clob::Order_ConditionType condition_type, uint64_t condition_order_trigger_subticks,
                                                            bool reduce_only, bool long_term, uint32_t client_metadata) {
    dydxprotocol::clob::MsgPlaceOrder place_order;
    dydxprotocol::clob::Order& order = *place_order.mutable_order();
    dydxprotocol::clob::OrderId& order_id = *order.mutable_order_id();
    dydxprotocol::subaccounts::SubaccountId& subaccount_id = *order_id.mutable_subaccount_id();
    *subaccount_id.mutable_owner() = address;
    subaccount_id.set_number(subaccount_number);
    order_id.set_client_id(order_cid);

    order_id.set_order_flags(condition_type == dydxprotocol::clob::Order_ConditionType_CONDITION_TYPE_UNSPECIFIED ? (long_term ? 64 : 0) : 32);
    order_id.set_clob_pair_id(clob_pair_id);
    order.set_side(side);
    order.set_quantums(quantums);
    order.set_subticks(subticks);
    if (long_term) {
        order.set_good_til_block_time(good_till);
    } else {
        order.set_good_til_block(good_till);
    }
    order.set_time_in_force(time_in_force);
    order.set_reduce_only(reduce_only);
    order.set_client_metadata(client_metadata);
    order.set_condition_type(condition_type);
    order.set_conditional_order_trigger_subticks(condition_order_trigger_subticks);
    return place_order;
}

dydxprotocol::clob::MsgCancelOrder generateCancelOrderMessage(const std::string& address, uint32_t subaccount_number, uint32_t order_cid, uint32_t clob_pair_id,
                                                              uint32_t good_till, bool conditional, bool long_term) {
    dydxprotocol::clob::MsgCancelOrder cancel_order;
    dydxprotocol::clob::OrderId& order_id = *cancel_order.mutable_order_id();
    dydxprotocol::subaccounts::SubaccountId& subaccount_id = *order_id.mutable_subaccount_id();
    *subaccount_id.mutable_owner() = address;
    subaccount_id.set_number(subaccount_number);
    order_id.set_client_id(order_cid);
    order_id.set_order_flags(conditional ? 32 : (long_term ? 64 : 0));
    order_id.set_clob_pair_id(clob_pair_id);
    if (long_term) {
        cancel_order.set_good_til_block_time(good_till);
    } else {
        cancel_order.set_good_til_block(good_till);
    }
    return cancel_order;
}

void createTx(cosmos::tx::v1beta1::Tx& tx, cosmos::tx::v1beta1::SignDoc& signDoc, const DyDxConfig& exchange_info, const LocalAccount& accountInfo,
              const RemoteAccount& remoteAccount, const google::protobuf::Message& message, uint64_t gas_limit) {
    tx.mutable_auth_info()->mutable_fee()->set_gas_limit(gas_limit);
    auto& amount = *tx.mutable_auth_info()->mutable_fee()->add_amount();
    uint64_t fee = std::ceil(gas_limit * exchange_info.feeMinimumGasPrice);
    *amount.mutable_amount() = std::to_string(fee);
    *amount.mutable_denom() = exchange_info.feeDenom;

    auto& signerInfo = *tx.mutable_auth_info()->add_signer_infos();
    cosmos::crypto::secp256k1::PubKey publicKey;
    const std::string pubKeyString(accountInfo.m_public_key.data(), accountInfo.m_public_key.data() + accountInfo.m_public_key.size());
    *publicKey.mutable_key() = pubKeyString;
    signerInfo.mutable_public_key()->PackFrom(publicKey, "/");
    signerInfo.mutable_mode_info()->mutable_single()->set_mode(cosmos::tx::signing::v1beta1::SIGN_MODE_DIRECT);
    signerInfo.set_sequence(remoteAccount.sequence);
}

void addSignature(LocalAccount& localAccount, secp256k1_ecdsa_signature& signature, const secp256k1_context* signContext, cosmos::tx::v1beta1::Tx* tx,
                  size_t byteSize, const uint8_t* txSerialized) {
    uint8_t hash[32];
    hasher_Raw(HASHER_SHA2, txSerialized, byteSize, hash);
    auto return_val = secp256k1_ecdsa_sign(signContext, &signature, hash, localAccount.m_private_key.data(), NULL, NULL);
    assert(return_val);
    secp256k1_ecdsa_signature_serialize_compact(signContext, reinterpret_cast<unsigned char*>(tx->mutable_signatures(0)->data()), &signature);
    assert(return_val);
}

void setOrderAndSign(const secp256k1_context* ctx, const RemoteAccount& remoteAccount, cosmos::tx::v1beta1::Tx* tx, cosmos::tx::v1beta1::SignDoc* txSign,
                     const google::protobuf::Message& orderMessage, LocalAccount& localAccount, secp256k1_ecdsa_signature& sig) {
    tx->mutable_body()->mutable_messages(0)->PackFrom(orderMessage, "/");
    txSign->set_body_bytes(tx->body().SerializeAsString());
    txSign->set_auth_info_bytes(tx->auth_info().SerializeAsString());
    txSign->set_chain_id(EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET.chainId);
    txSign->set_account_number(remoteAccount.number);

    std::size_t byteSize = txSign->ByteSizeLong();
    uint8_t txSerialized[byteSize];

    txSign->SerializeToArray(txSerialized, byteSize);
    addSignature(localAccount, sig, ctx, tx, byteSize, txSerialized);
}
