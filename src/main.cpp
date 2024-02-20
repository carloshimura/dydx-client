#include <spdlog/spdlog.h>

#include "account.h"
#include "bech32.h"
#include "websocket_boost_client.h"
#include "rest_client.h"

#include <fmt/format.h>
#include <bip3x/bip3x_crypto.h>
#include <bip3x/bip3x_hdkey_encoder.h>
#include <bip3x/bip3x_mnemonic.h>
#include <bip3x/crypto/ripemd160.h>
#include <bip3x/crypto/sha2.hpp>
#include <bip3x/details/utils.h>

using Address = std::string;
using BlockNumber = uint32_t;
using ClobPairId = uint32_t;
using AssetId = uint32_t;
using OrderId = std::string;
using OrderCid = uint32_t;
using AccountNumber = uint32_t;
using SubaccountNumber = uint32_t;
using Quantums = uint64_t;
using Subticks = uint64_t;
using BytesVec = std::vector<uint8_t>;

constexpr uint32_t LONG_TERM_TIME_TO_LIVE_SECONDS = 24 * 60 * 60;
constexpr BlockNumber SHORT_TERM_TIME_TO_LIVE_BLOCKS = 15;
constexpr AssetId ASSET_USDC = 0;
inline const std::string BECH32_PREFIX = "dydx";
inline const std::string BIP44_DERIVATION_PATH = "m/44'/118'/0'/0/0";

inline const std::string EXAMPLE_WALLET_MNEMONIC =
    "minute envelope used million door host inject language crumble prison "
    "agree fish"; // On Goerli Network
inline const std::string EXAMPLE_DYDX_V4_MNEMONIC =
    "daughter apart kitchen detect differ under impose shiver fade swap tape "
    "emerge game gather adult build enlist leg win minute edge note bring "
    "phone";

BytesVec calc_fingerprint(bip3x::hdkey &key) {
    BytesVec sha_digest(32);
    trezor::SHA256_CTX ctx;
    sha256_Init(&ctx);
    sha256_Update(&ctx, key.public_key.cdata(), 33);
    sha256_Final(&ctx, sha_digest.data());

    BytesVec final_digest(20);
    ripemd160(sha_digest.data(), 32, final_digest.data());
    return final_digest;
}

BytesVec to_5bits(const BytesVec &bytes) {
    assert(bytes.size() % 5 == 0);
    constexpr int FROM_BITS = 8;
    constexpr int TO_BITS = 5;
    constexpr int MAX_VALUE = (1 << TO_BITS) - 1;
    constexpr int MAX_ACC = (1 << (FROM_BITS + TO_BITS - 1)) - 1;
    int acc = 0;
    int bits = 0;
    BytesVec result;
    for (uint8_t const by : bytes) {
        acc = ((acc << FROM_BITS) | by) & MAX_ACC;
        bits += FROM_BITS;
        while (bits >= TO_BITS) {
            bits -= TO_BITS;
            result.push_back((acc >> bits) & MAX_VALUE);
        }
    }
    return result;
}

LocalAccount accountFromMnemonic(std::string mnemonic,
                                 uint32_t subaccount_number) {
    const bip3x::bytes_64 seed =
        bip3x::bip3x_hdkey_encoder::make_bip39_seed(mnemonic);
    bip3x::hdkey key = bip3x::bip3x_hdkey_encoder::make_bip32_root_key(seed);
    bip3x::bip3x_hdkey_encoder::extend_key(key, BIP44_DERIVATION_PATH);
    auto fingerprint = calc_fingerprint(key);
    auto address = bech32::Encode(bech32::Encoding::BECH32, BECH32_PREFIX,
                                  to_5bits(fingerprint));
    return LocalAccount{
        .m_sub_account =
            LocalAccount::SubAccount{
                .m_address = std::move(address),
                .m_number = subaccount_number,
            },
        .m_mnemonic = std::move(mnemonic),
        .m_public_key = key.public_key.get(),
        .m_private_key = key.private_key.get(),
    };
}

std::string sign(std::string_view message,  toolbox::data::bytes_array<32> private_key) {
    std::string result;
    result.resize(64);
    ecdsa_sign(&secp256k1, HASHER_SHA2,
               reinterpret_cast<const uint8_t *>(private_key.data()),
               reinterpret_cast<const uint8_t *>(message.data()),
               message.size(), reinterpret_cast<uint8_t *>(result.data()),
               nullptr, nullptr);
    return result;
}

std::string create_request() {
    return R"({"type": "subscribe", "channel": "v4_subaccounts", "id": "BTC-USD})";
}

int main(int argc, char **argv) {
    spdlog::set_pattern("[%H:%M:%S.%F] %v");
    boost::asio::io_context context;

    auto local_account_info = accountFromMnemonic(EXAMPLE_DYDX_V4_MNEMONIC, 0);
    auto start_time_height = std::chrono::high_resolution_clock::now();
    RestClient rest("dydx-lcd-testnet.enigma-validator.com", "443");
    auto response = rest.sendGetRequestAndWaitForResponse("/cosmos/base/tendermint/v1beta1/blocks/latest");
    auto last_block = response["block"]["header"]["height"].get<std::string>();

    auto end_time_height = std::chrono::high_resolution_clock::now();
    spdlog::info("Time: {} nanoseconds",
                 std::chrono::duration_cast<std::chrono::nanoseconds>(
                     end_time_height - start_time_height)
                         .count() /
                     1000);
    spdlog::info("Received response: {}", last_block);
//    BoostWebSocketClient client(context);
//    std::string_view host = "indexer.v4testnet.dydx.exchange";
//    std::string_view port = "443";
//    std::string_view target = "/v4/ws";
//    client.connect(host, port, target);
//    client.read_data();
//    auto buf = boost::asio::buffer("Hey, I'm here");
//    auto start_time_message = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 1000; ++i)
//        client.send_message(buf);
//    auto end_time_message = std::chrono::high_resolution_clock::now();
//    spdlog::info("Time: {} nanoseconds",
//                 std::chrono::duration_cast<std::chrono::nanoseconds>(
//                     start_time_message - end_time_message)
//                         .count() /
//                     1000);

//    client.close();
    return EXIT_SUCCESS;
}