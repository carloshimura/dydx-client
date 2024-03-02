#include <spdlog/spdlog.h>

#include "account.h"
#include "grpc_client.h"
#include "market_info.h"
#include "order.h"
#include "rest_client.h"

#include <boost/container/flat_map.hpp>
#include <google/protobuf/text_format.h>

#include <random>

static constexpr auto numberOfOrders = 100U;

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S.%F] %v");
    if (argc < 2) {
        spdlog::error("Invalid number of arguments");
    }
    // example of json as terminal argument: {\"baseAsset\":2, \"exchangeId\":81, \"level\":1, \"orderType\":1, \"buy\":true, \"cancelAndCreate\":true, \"timestamp\":1709203259489729929, \"amount\":0.576, \"price\":3475.1}
    std::string full_arg;
    for (int i = 1; i < argc; ++i) {
        full_arg.append(argv[i]);
    }

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


    auto marketsJson = indexerRestClient.sendGetRequestAndWaitForResponse("/v4/perpetualMarkets");
    boost::container::flat_map<std::string, MarketInfo> markets;
    markets["ETH-USD"] = fromJson(marketsJson, "ETH-USD");
    markets["BTC-USD"] = fromJson(marketsJson, "BTC-USD");

    auto nextValidBlockHeight = orderGRPCClient.getLatestBlockHeight() + 1U;
    auto goodTilBlock = nextValidBlockHeight + 10U;
    uint32_t clientMetadata = 0U;
    auto baseAccount = orderGRPCClient.queryAccount(account.m_sub_account.m_address);
    spdlog::info("Remote Account: .address = {}, .number = {}, .sequence = {}", baseAccount.address, baseAccount.number, baseAccount.sequence);


    order myOrder{};
    auto ec = glz::read_json<order>(myOrder, full_arg);
    if (ec) {
        std::string errorMsg;
        spdlog::error("Failed to parse order: {}", glz::format_error(ec, full_arg));
        return EXIT_FAILURE;
    }
    const auto& market = markets[myOrder.assetToMarket()];

    // pre allocate all needed memory

    google::protobuf::Arena arena(nullptr, 8192);


    std::array<std::chrono::high_resolution_clock::time_point, numberOfOrders> startTime;
    std::array<std::chrono::high_resolution_clock::time_point, numberOfOrders> cancelStartTime;
    std::array<std::chrono::high_resolution_clock::time_point, numberOfOrders> endTime;
    std::array<std::chrono::high_resolution_clock::time_point, numberOfOrders> cancelEndTime;
    std::array<std::chrono::nanoseconds, numberOfOrders*2> signTime{};
    for (int i = 0; i < numberOfOrders; ++i) {
        startTime[i] = std::chrono::high_resolution_clock::now();
        auto shortTermClientID = dist(rng);
        auto* tx = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::Tx>(&arena);
        tx->mutable_body()->add_messages();
        auto* txSign = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::SignDoc>(&arena);

        auto* cancelTx = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::Tx>(&arena);
        cancelTx->mutable_body()->add_messages();
        auto* cancelTxSign = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::SignDoc>(&arena);
        auto placeOrder =
            generatePlaceOrderMessage(account.m_sub_account.m_address, account.m_sub_account.m_number, shortTermClientID, market.clobPairID,
                                      dydxprotocol::clob::Order_Side_SIDE_BUY, dydxprotocol::clob::Order_TimeInForce_TIME_IN_FORCE_UNSPECIFIED, calculateQuantums(myOrder.amount, market.atomicResolution, market.stepBaseQuantums), calculateSubticks(myOrder.price, market.atomicResolution, market.quantumConversionExponent, market.subticksPerTick),
                                      goodTilBlock, dydxprotocol::clob::Order_ConditionType_CONDITION_TYPE_UNSPECIFIED, 0U, false, false, clientMetadata);

        createTx(*tx, *txSign, EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, account, baseAccount, placeOrder, 0U, signTime[2*i]);
        auto hash = orderGRPCClient.broadcastTransaction(*tx, arena, endTime[i]);

        cancelStartTime[i] = std::chrono::high_resolution_clock::now();
        if (hash) {
            auto cancel =
                generateCancelOrderMessage(baseAccount.address, account.m_sub_account.m_number, shortTermClientID, market.clobPairID, goodTilBlock, false, false);

            createTx(*cancelTx, *cancelTxSign, EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, account, baseAccount, cancel, 0U, signTime[(2*i) + 1]);
            auto cancelHash = orderGRPCClient.broadcastTransaction(*cancelTx, arena, cancelEndTime[i]);
        } else {
            cancelEndTime[i] = std::chrono::high_resolution_clock::now();
            spdlog::error("No hash after order created!!!");
        }
    }
    uint64_t sumCreate = 0;
    uint64_t sumCancel = 0;
    uint64_t sumSign = 0;
    for (int i = 0; i < 100; ++i) {
        sumCreate += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime[i] - startTime[i]).count();
        sumCancel += std::chrono::duration_cast<std::chrono::nanoseconds>(cancelEndTime[i] - cancelStartTime[i]).count();
        sumSign += signTime[2*i].count() + signTime[(2*i) + 1].count();
    }
    spdlog::info("Average create = {} nanoseconds", sumCreate/numberOfOrders);
    spdlog::info("Average cancel = {} nanoseconds", sumCancel/numberOfOrders);
    spdlog::info("Average sign = {} nanoseconds", sumSign/(numberOfOrders*2));


    return EXIT_SUCCESS;
}