//
// Created by carlos on 22-2-24.
//

#include "../include/grpc_client.h"

#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <google/protobuf/text_format.h>
#include <spdlog/spdlog.h>

GRPCClient::GRPCClient(const std::string& address)
    : options{}, credentials(grpc::SslCredentials(options)), channel_(grpc::CreateChannel(address, credentials)),
      stub_(dydxprotocol::clob::Msg::NewStub(channel_)), txStub_(cosmos::tx::v1beta1::TxService::NewStub(channel_)),
      queryStub_(cosmos::auth::v1beta1::Query::NewStub(channel_)), queryBlockStub_(cosmos::base::tendermint::v1beta1::QueryService::NewStub(channel_)) {}

void GRPCClient::sendOrder(dydxprotocol::clob::MsgPlaceOrder& msgPlaceOrder) {
    grpc::ClientContext context;
    dydxprotocol::clob::MsgPlaceOrderResponse response;
    auto rpcResponse = stub_->PlaceOrder(&context, msgPlaceOrder, &response);
    if (rpcResponse.ok()) {
        std::string output;
        google::protobuf::TextFormat::PrintToString(response, &output);
        spdlog::info("Order response: {}", output);
    } else {
        spdlog::error("Place Order rpc failed: {}", rpcResponse.error_message());
    }
}

RemoteAccount GRPCClient::queryAccount(const std::string& address) {
    cosmos::auth::v1beta1::QueryAccountRequest req;
    grpc::ClientContext context;
    cosmos::auth::v1beta1::QueryAccountResponse resp;
    req.set_address(address);

    auto rpcResponse = queryStub_->Account(&context, req, &resp);
    if (rpcResponse.ok()) {
        std::string output;
        google::protobuf::TextFormat::PrintToString(resp, &output);
        // spdlog::info("Account response: {}", output);
        if (resp.account().Is<cosmos::auth::v1beta1::BaseAccount>()) {
            cosmos::auth::v1beta1::BaseAccount baseAccount;
            resp.account().UnpackTo(&baseAccount);
            return {.address = baseAccount.address(), .number = baseAccount.account_number(), .sequence = baseAccount.sequence()};
        }
        spdlog::error("Did not receive correct account");
    } else {
        spdlog::error("Account rpc failed: {}", rpcResponse.error_message());
    }
    return RemoteAccount{};
}

std::optional<std::string> GRPCClient::broadcastTransaction(cosmos::tx::v1beta1::Tx& tx, google::protobuf::Arena& arena) {
    cosmos::tx::v1beta1::BroadcastTxRequest* txRequest = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::BroadcastTxRequest>(&arena);
    txRequest->set_mode(cosmos::tx::v1beta1::BROADCAST_MODE_SYNC);
    txRequest->set_tx_bytes(tx.SerializeAsString());
    grpc::ClientContext context_;
    cosmos::tx::v1beta1::BroadcastTxResponse* resp = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::BroadcastTxResponse>(&arena);
    auto response = txStub_->BroadcastTx(&context_, *txRequest, resp);
    if (response.ok()) {
        std::string output;
        google::protobuf::TextFormat::PrintToString(*resp, &output);
        spdlog::info("Broadcast transaction: {}", output);
        if (resp->has_tx_response()) {
            return resp->tx_response().txhash();
        }
    } else {
        spdlog::error("BroadcastTx rpc failed: {}", response.error_message());
    }
    return {};
}

int64_t GRPCClient::getLatestBlockHeight() {
    cosmos::base::tendermint::v1beta1::GetLatestBlockRequest req;
    grpc::ClientContext context;
    cosmos::base::tendermint::v1beta1::GetLatestBlockResponse resp;

    auto rpcResponse = queryBlockStub_->GetLatestBlock(&context, req, &resp);
    if (rpcResponse.ok()) {
        return resp.block().header().height();
    } else {
        spdlog::error("Latest block rpc failed: {}", rpcResponse.error_message());
    }
    return 0;
}
