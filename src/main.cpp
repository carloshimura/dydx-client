#include <spdlog/spdlog.h>

#include "account.h"
#include "grpc_client.h"
#include "market_info.h"
#include "order.h"
#include "rest_client.h"

#include <benchmark/benchmark.h>
#include <boost/container/flat_map.hpp>
#include <google/protobuf/text_format.h>

#include <random>

#include <sys/random.h>

int fillRandom(unsigned char* data, size_t size) {
    /* If `getrandom(2)` is not available you should fall back to /dev/urandom */
    ssize_t res = getrandom(data, size, 0);
    if (res < 0 || (size_t)res != size) {
        return 0;
    }
    return 1;

}


void benchmarkSendNewAndCancelOrder(benchmark::State& state) {
    constexpr bool shouldSendOrders = true;
    RestClient indexerRestClient("indexer.v4testnet.dydx.exchange", "443");
    GRPCClient orderGRPCClient("test-dydx-grpc.kingnodes.com:443");
    auto nextValidBlockHeight = orderGRPCClient.getLatestBlockHeight() + 1U;
    auto goodTilBlock = nextValidBlockHeight + 10U;
    uint32_t clientMetadata = 0U;
    auto marketsJson = indexerRestClient.sendGetRequestAndWaitForResponse("/v4/perpetualMarkets");
    boost::container::flat_map<std::string, MarketInfo> markets;
    markets["ETH-USD"] = fromJson(marketsJson, "ETH-USD");
    markets["BTC-USD"] = fromJson(marketsJson, "BTC-USD");
    static const std::string dydxV4Mnemonic =
        "night scan essay distance just royal regret mind various blast swap exit myth raw expire insane slot ranch lock sun wild bring series nurse";
    std::array<std::string, 10> ordersJson = {
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.576, "price":3475.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.6, "price":3575.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.589, "price":3675.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.7, "price":3775.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.452, "price":3476.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.577, "price":3477.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.578, "price":3478.1})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.589, "price":3479.9})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.58, "price":3475.5})",
        R"({"baseAsset":2, "exchangeId":81, "level":1, "orderType":1, "buy":true, "cancelAndCreate":true, "timestamp":1709203259489729929, "amount":0.68, "price":3475.6})"};
    auto orderIndex = 0U;
    auto localAccount = accountFromMnemonic(dydxV4Mnemonic, 0);

    unsigned char randomize[32];
    secp256k1_pubkey pubkey;
    secp256k1_ecdsa_signature signature;
    /* Before we can call actual API functions, we need to create a "context". */
    secp256k1_context* signContext = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    if (!fillRandom(randomize, sizeof(randomize))) {
        printf("Failed to generate randomness\n");
        std::exit(EXIT_FAILURE);
    }
    /* Randomizing the context is recommended to protect against side-channel
     * leakage See `secp256k1_context_randomize` in secp256k1.h for more
     * information about it. This should never fail. */
    auto randomizeResult = secp256k1_context_randomize(signContext, randomize);
    assert(randomizeResult);

    std::random_device dev;
    google::protobuf::Arena arena(nullptr, 8192);
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, std::numeric_limits<uint32_t>::max()); // distribution in range 1 to uint32_max
    std::string signReservation;
    signReservation.reserve(64);
    for (auto i = 0U; i < 64; ++i) {
        signReservation.push_back('\0');
    }

    auto remoteAccount = orderGRPCClient.queryAccount(localAccount.m_sub_account.m_address);

    auto buyOrder = generatePlaceOrderMessage(localAccount.m_sub_account.m_address, localAccount.m_sub_account.m_number, 0, 0,
                                              dydxprotocol::clob::Order_Side_SIDE_BUY, dydxprotocol::clob::Order_TimeInForce_TIME_IN_FORCE_UNSPECIFIED, 0U, 0U,
                                              123456, dydxprotocol::clob::Order_ConditionType_CONDITION_TYPE_UNSPECIFIED, 0U, false, false, clientMetadata);

    auto cancelOrder = generateCancelOrderMessage(remoteAccount.address, localAccount.m_sub_account.m_number, 0U, 0U, 0U, false, false);

    auto* buyTransaction = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::Tx>(&arena);
    buyTransaction->mutable_body()->add_messages();
    auto* buyTransactionSign = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::SignDoc>(&arena);

    auto* cancelTransaction = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::Tx>(&arena);
    cancelTransaction->mutable_body()->add_messages();
    auto* cancelTransactionSignature = google::protobuf::Arena::CreateMessage<cosmos::tx::v1beta1::SignDoc>(&arena);

    createTx(*buyTransaction, *buyTransactionSign, EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, localAccount, remoteAccount, buyOrder, 0U);
    buyTransaction->add_signatures(signReservation);

    createTx(*cancelTransaction, *cancelTransactionSignature, EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET, localAccount, remoteAccount, cancelOrder, 0U);
    cancelTransaction->add_signatures(signReservation);

    // Perform setup here
    for (auto _ : state) {
        Order myOrder{};
        auto ec = glz::read_json<Order>(myOrder, ordersJson[(++orderIndex) % ordersJson.size()]);
        // This code gets timed
        auto shortTermClientID = dist(rng);
        const auto& market = markets[myOrder.assetToMarket()];
        const auto quantums = calculateQuantums(myOrder.amount, market.atomicResolution, market.stepBaseQuantums);
        const auto subticks = calculateSubticks(myOrder.price, market.atomicResolution, market.quantumConversionExponent, market.subticksPerTick);
        buyOrder.mutable_order()->mutable_order_id()->set_client_id(shortTermClientID);
        buyOrder.mutable_order()->mutable_order_id()->set_clob_pair_id(market.clobPairID);
        buyOrder.mutable_order()->set_subticks(subticks);
        buyOrder.mutable_order()->set_quantums(quantums);
        buyOrder.mutable_order()->set_good_til_block(goodTilBlock);

        setOrderAndSign(signContext, remoteAccount, buyTransaction, buyTransactionSign, buyOrder, localAccount, signature);

        if constexpr (shouldSendOrders) {
            auto hashResult = orderGRPCClient.broadcastTransaction(*buyTransaction, arena);
        }


        cancelOrder.mutable_order_id()->set_client_id(shortTermClientID);
        cancelOrder.mutable_order_id()->set_clob_pair_id(market.clobPairID);
        cancelOrder.set_good_til_block(goodTilBlock);
        setOrderAndSign(signContext, remoteAccount, cancelTransaction, cancelTransactionSignature, cancelOrder, localAccount, signature);

        if constexpr (shouldSendOrders) {
            auto cancelHash = orderGRPCClient.broadcastTransaction(*cancelTransaction, arena);
        }
        buyTransaction->mutable_body()->mutable_messages(0)->Clear();
        cancelTransaction->mutable_body()->mutable_messages(0)->Clear();
    }
}

BENCHMARK(benchmarkSendNewAndCancelOrder);
// Run the benchmark
BENCHMARK_MAIN();
