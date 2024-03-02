#include <spdlog/spdlog.h>

#include "account.h"
#include "grpc_client.h"
#include "market_info.h"
#include "order.h"
#include "rest_client.h"

#include <google/protobuf/text_format.h>

#include <cstdint>
#include <random>

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S.%F] %v");
    boost::asio::io_context context;

    static const std::string dydxV4Mnemonic =
        "night scan essay distance just royal regret mind various blast swap exit myth raw expire insane slot ranch lock sun wild bring series nurse";

    auto account = accountFromMnemonic(dydxV4Mnemonic, 0);
    std::string printablePrivateKey(reinterpret_cast<const char *>(account.m_private_key.data()), account.m_private_key.size());
    std::string printablePublicKey(reinterpret_cast<const char *>(account.m_public_key.data()), account.m_public_key.size());
    spdlog::info("Account info: .address = {}, .pub_key = {}, .priv_key = {}", account.m_sub_account.m_address,
                 toolbox::data::base64_encode(printablePublicKey), toolbox::data::base64_encode(printablePrivateKey));

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, std::numeric_limits<uint32_t>::max()); // distribution in range [1, 6]

    RestClient validatorRestClient("dydx-lcd-testnet.enigma-validator.com", "443");
    RestClient indexerRestClient("indexer.v4testnet.dydx.exchange", "443");
    GRPCClient orderGRPCClient("test-dydx-grpc.kingnodes.com:443");

    auto shortTermClientID = dist(rng);

    auto market = fromJson(indexerRestClient.sendGetRequestAndWaitForResponse("/v4/perpetualMarkets"), "ETH-USD");
    auto quantums = calculateQuantums(0.01, market.atomicResolution, market.stepBaseQuantums);
    auto subticks = calculateSubticks(40000, market.atomicResolution, market.quantumConversionExponent, market.subticksPerTick);

    auto nextValidBlockHeight = orderGRPCClient.getLatestBlockHeight() + 1U;
    auto goodTilBlock = nextValidBlockHeight + 10U;
    uint32_t clientMetadata = 0U;
    auto baseAccount = orderGRPCClient.queryAccount(account.m_sub_account.m_address);
    spdlog::info("Remote Account: .address = {}, .number = {}, .sequence = {}", baseAccount.address, baseAccount.number, baseAccount.sequence);

    std::chrono::time_point<std::chrono::high_resolution_clock> timeAfterBroadcastNewOrder;
    std::chrono::time_point<std::chrono::high_resolution_clock> timeAfterBroadcastCancelOrder;
    auto timeBeforeSendingNewOrder = std::chrono::high_resolution_clock::now();
    auto order =
        generatePlaceOrderMessage(account.m_sub_account.m_address, account.m_sub_account.m_number, shortTermClientID, market.clobPairID,
                                  dydxprotocol::clob::Order_Side_SIDE_BUY, dydxprotocol::clob::Order_TimeInForce_TIME_IN_FORCE_UNSPECIFIED, quantums, subticks,
                                  goodTilBlock, dydxprotocol::clob::Order_ConditionType_CONDITION_TYPE_UNSPECIFIED, 0U, false, false, clientMetadata);

    auto tx = createTx(EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, account, baseAccount, order, 0U);
    auto hash = orderGRPCClient.broadcastTransaction(tx, timeAfterBroadcastNewOrder);

    auto timeBeforeCancelOrder = std::chrono::high_resolution_clock::now();
    if (hash) {
        auto cancel =
            generateCancelOrderMessage(baseAccount.address, account.m_sub_account.m_number, shortTermClientID, market.clobPairID, goodTilBlock, false, false);
        auto cancelTx = createTx(EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, account, baseAccount, cancel, 0U);
        auto cancelHash = orderGRPCClient.broadcastTransaction(cancelTx, timeAfterBroadcastCancelOrder);
    } else {
        timeAfterBroadcastCancelOrder = std::chrono::high_resolution_clock::now();
        spdlog::error("No hash after order created!!!");
    }

    spdlog::info("CreateOrder time: {} nanoseconds",
                 std::chrono::duration_cast<std::chrono::nanoseconds>(timeAfterBroadcastNewOrder - timeBeforeSendingNewOrder).count() / 1000);
    spdlog::info("CancelOrder time: {} nanoseconds",
                 std::chrono::duration_cast<std::chrono::nanoseconds>(timeAfterBroadcastCancelOrder - timeBeforeCancelOrder).count() / 1000);

    return EXIT_SUCCESS;
}