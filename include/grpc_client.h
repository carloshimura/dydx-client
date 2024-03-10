//
// Created by carlos on 22-2-24.
//

#ifndef DYDX_CLIENT_GRPC_CLIENT_H
#define DYDX_CLIENT_GRPC_CLIENT_H

#include "account.h"

#include <memory>
#include <string>

#include <grpcpp/security/credentials.h>

#include "cosmos/auth/v1beta1/query.grpc.pb.h"
#include "cosmos/base/tendermint/v1beta1/query.grpc.pb.h"
#include "cosmos/tx/v1beta1/service.grpc.pb.h"
#include "dydxprotocol/clob/tx.grpc.pb.h"

class GRPCClient {
public:
    explicit GRPCClient(const std::string& address);
    void sendOrder(dydxprotocol::clob::MsgPlaceOrder& msgPlaceOrder);
    std::optional<std::string> broadcastTransaction(cosmos::tx::v1beta1::Tx& tx, google::protobuf::Arena& arena);
    RemoteAccount queryAccount(const std::string& address);
    int64_t getLatestBlockHeight();

private:
    grpc::SslCredentialsOptions options;
    std::shared_ptr<grpc::ChannelCredentials> credentials;
    std::shared_ptr<grpc::Channel> channel_;
    std::unique_ptr<dydxprotocol::clob::Msg::Stub> stub_;
    std::unique_ptr<cosmos::tx::v1beta1::TxService::Stub> txStub_;
    std::unique_ptr<cosmos::auth::v1beta1::Query::Stub> queryStub_;
    std::unique_ptr<cosmos::base::tendermint::v1beta1::QueryService::Stub> queryBlockStub_;
};

#endif // DYDX_CLIENT_GRPC_CLIENT_H
