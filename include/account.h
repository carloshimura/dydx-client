//
// Created by carlos on 18-2-24.
//

#ifndef DYDX_CLIENT_ACCOUNT_H
#define DYDX_CLIENT_ACCOUNT_H

#include "bech32.h"

#include <bip3x/bip3x_hdkey_encoder.h>
#include <bip3x/bip3x_mnemonic.h>
#include <bip3x/crypto/ripemd160.h>
#include <bip3x/crypto/sha2.hpp>
#include <toolbox/data/base64.h>
#include <toolbox/data/bytes_array.h>

#include <cstdint>
#include <string>

using BlockNumber = uint32_t;
using AssetId = uint32_t;
using BytesVec = std::vector<uint8_t>;

struct LocalAccount {
    struct SubAccount {
        std::string m_address;
        uint32_t m_number;
    };
    SubAccount m_sub_account;
    std::string m_mnemonic;
    std::array<unsigned char, 33> m_public_key;
    std::array<unsigned char, 32> m_private_key;
    std::string m_encoded_key;
    mutable uint64_t m_sequence{0};
    uint64_t getSequence() const { return m_sequence; }
};

struct RemoteAccount {
    std::string address;
    uint64_t number{0};
    uint64_t sequence{0};
};

BytesVec calc_fingerprint(bip3x::hdkey& key);

BytesVec to_5bits(const BytesVec& bytes);

constexpr uint32_t LONG_TERM_TIME_TO_LIVE_SECONDS = 24 * 60 * 60;
constexpr BlockNumber SHORT_TERM_TIME_TO_LIVE_BLOCKS = 15;
constexpr AssetId ASSET_USDC = 0;
inline const std::string BECH32_PREFIX = "dydx";
inline const std::string BIP44_DERIVATION_PATH = "m/44'/118'/0'/0/0";

LocalAccount accountFromMnemonic(std::string mnemonic, uint32_t subAccountNumber);

#endif // DYDX_CLIENT_ACCOUNT_H
