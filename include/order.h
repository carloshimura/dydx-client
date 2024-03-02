//
// Created by carlos on 11-2-24.
//

#ifndef DYDX_CLIENT_ORDER_H
#define DYDX_CLIENT_ORDER_H

#include "dydx_config.h"

#include "cosmos/crypto/secp256k1/keys.pb.h"
#include "cosmos/tx/signing/v1beta1/signing.pb.h"
#include "cosmos/tx/v1beta1/tx.pb.h"
#include "cosmos_proto/cosmos.pb.h"
#include "dydxprotocol/clob/order.pb.h"
#include "dydxprotocol/clob/tx.pb.h"

#include <bip3x/bip3x_crypto.h>

uint64_t calculateQuantums(double size, int32_t atomic_resolution, uint64_t step_base_quantums) {
    auto rawQuantums = size * std::pow(10, -1 * atomic_resolution);
    return std::max(static_cast<uint64_t>(std::round(rawQuantums)), step_base_quantums);
}

uint64_t calculateSubticks(double price, int32_t atomic_resolution, int32_t quantum_conversion_exponent, uint64_t subticks_per_tick) {
    static constexpr int32_t quoteQuantumsAtomicResolution = -6;
    auto exponent = atomic_resolution - quantum_conversion_exponent - quoteQuantumsAtomicResolution;
    auto rawSubticks = price * std::pow(10, exponent);
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

std::string sign(std::string_view message, toolbox::data::bytes_array<32> private_key) {
//    auto start_time_order = std::chrono::high_resolution_clock::now();
    std::string result;
    result.resize(64);
    ecdsa_sign(&secp256k1, HASHER_SHA2, reinterpret_cast<const uint8_t *>(private_key.data()), reinterpret_cast<const uint8_t *>(message.data()),
               message.size(), reinterpret_cast<uint8_t *>(result.data()), nullptr, nullptr);

//    auto end_time_order = std::chrono::high_resolution_clock::now();
//    spdlog::info("Signature time: {} nanoseconds", std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_order - start_time_order).count() / 1000);
    return result;
}

void addSignature(cosmos::tx::v1beta1::Tx& tx, const LocalAccount& local_account_info, const RemoteAccount& remote_account) {
    cosmos::tx::v1beta1::SignDoc sign_doc;
    *sign_doc.mutable_body_bytes() = tx.body().SerializeAsString();
    *sign_doc.mutable_auth_info_bytes() = tx.auth_info().SerializeAsString();
    *sign_doc.mutable_chain_id() = EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET.chainId;
    sign_doc.set_account_number(remote_account.number);
    auto docAsString = sign_doc.SerializeAsString();
    auto signature = sign(sign_doc.SerializeAsString(), local_account_info.m_private_key);
    tx.add_signatures(signature.data(), signature.size());
}

cosmos::tx::v1beta1::Tx createTx(const DyDxConfig& exchange_info, const LocalAccount& account_info, const RemoteAccount& remote_account,
                                 const google::protobuf::Message& message, uint64_t gas_limit) {
    cosmos::tx::v1beta1::Tx tx;
    tx.mutable_body()->add_messages()->PackFrom(message, "/");
    tx.mutable_auth_info()->mutable_fee()->set_gas_limit(gas_limit);
    auto& amount = *tx.mutable_auth_info()->mutable_fee()->add_amount();
    uint64_t fee = std::ceil(gas_limit * exchange_info.feeMinimumGasPrice);
    *amount.mutable_amount() = std::to_string(fee);
    *amount.mutable_denom() = exchange_info.feeDenom;
    auto& signer_info = *tx.mutable_auth_info()->add_signer_infos();
    cosmos::crypto::secp256k1::PubKey pub_key;
    const auto& pub_key_bytes = account_info.m_public_key;
    std::string const pub_key_string(pub_key_bytes.data(), pub_key_bytes.data() + pub_key_bytes.size());
    *pub_key.mutable_key() = pub_key_string;
    signer_info.mutable_public_key()->PackFrom(pub_key, "/");
    signer_info.mutable_mode_info()->mutable_single()->set_mode(cosmos::tx::signing::v1beta1::SIGN_MODE_DIRECT);
    signer_info.set_sequence(remote_account.sequence);

    addSignature(tx, account_info, remote_account);
    return tx;
}

#endif // DYDX_CLIENT_ORDER_H
