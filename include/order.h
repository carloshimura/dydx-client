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

#include "account.h"
#include "secp256k1.h"

#include <glaze/glaze.hpp>

struct Order {
    int baseAsset;
    int exchangeId;
    int level;
    int orderType;
    bool buy;
    bool cancelAndCreate;
    double timestamp;
    double amount;
    double price;

    [[nodiscard]] std::string assetToMarket() const {
        if (baseAsset == 1)
            return "BTC-USD";
        if (baseAsset == 2)
            return "ETH-USD";
        return "UNKOWN";
    }
};

template <> struct glz::meta<Order> {
    using T = Order;
    static constexpr auto value =
        object(&T::baseAsset, &T::exchangeId, &T::level, &T::orderType, &T::buy, &T::cancelAndCreate, &T::timestamp, &T::amount, &T::price);
};

uint64_t calculateQuantums(double size, int32_t atomic_resolution, uint64_t step_base_quantums);

uint64_t calculateSubticks(double price, int32_t atomic_resolution, int32_t quantum_conversion_exponent, uint64_t subticks_per_tick);

dydxprotocol::clob::MsgPlaceOrder generatePlaceOrderMessage(const std::string& address, uint32_t subaccount_number, uint32_t order_cid, uint32_t clob_pair_id,
                                                            dydxprotocol::clob::Order_Side side, dydxprotocol::clob::Order_TimeInForce time_in_force,
                                                            uint64_t quantums, uint64_t subticks, uint32_t good_till,
                                                            dydxprotocol::clob::Order_ConditionType condition_type, uint64_t condition_order_trigger_subticks,
                                                            bool reduce_only, bool long_term, uint32_t client_metadata);

dydxprotocol::clob::MsgCancelOrder generateCancelOrderMessage(const std::string& address, uint32_t subaccount_number, uint32_t order_cid, uint32_t clob_pair_id,
                                                              uint32_t good_till, bool conditional, bool long_term);

// void sign(const uint8_t* message, size_t size,  uint8_t* result, const LocalAccount& account_info, std::chrono::nanoseconds& time) {
//     ecdsa_sign(&secp256k1, HASHER_SHA2, reinterpret_cast<const uint8_t *>(account_info.m_private_key.data()), reinterpret_cast<const uint8_t *>(message),
//                size, result, nullptr, nullptr);
// }
//
// void addSignature(cosmos::tx::v1beta1::Tx& tx, cosmos::tx::v1beta1::SignDoc& sign_doc, const LocalAccount& local_account_info, const RemoteAccount&
// remote_account, std::chrono::nanoseconds& aTime) {
//     *sign_doc.mutable_body_bytes() = tx.body().SerializeAsString();
//     *sign_doc.mutable_auth_info_bytes() = tx.auth_info().SerializeAsString();
//     *sign_doc.mutable_chain_id() = EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET.chainId;
//     sign_doc.set_account_number(remote_account.number);
//     uint8_t signature[64]{0};
//     std::size_t byteSize = sign_doc.ByteSizeLong();
//     uint8_t bytes[byteSize];
//     sign_doc.SerializeToArray(bytes, byteSize);
//     sign(bytes, byteSize, signature, local_account_info, aTime);
//     tx.add_signatures(signature, 64);
// }

void createTx(cosmos::tx::v1beta1::Tx& tx, cosmos::tx::v1beta1::SignDoc& signDoc, const DyDxConfig& exchange_info, const LocalAccount& accountInfo,
              const RemoteAccount& remoteAccount, const google::protobuf::Message& message, uint64_t gas_limit);
void addSignature(LocalAccount& localAccount, secp256k1_ecdsa_signature& signature, const secp256k1_context* signContext, cosmos::tx::v1beta1::Tx* tx,
                  size_t byteSize, const uint8_t* txSerialized);
void setOrderAndSign(const secp256k1_context* ctx, const RemoteAccount& remoteAccount, cosmos::tx::v1beta1::Tx* tx, cosmos::tx::v1beta1::SignDoc* txSign,
                     const google::protobuf::Message& orderMessage, LocalAccount& localAccount, secp256k1_ecdsa_signature& sig);

#endif // DYDX_CLIENT_ORDER_H
