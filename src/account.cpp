//
// Created by carlos on 27-2-24.
//
#include "account.h"

BytesVec calc_fingerprint(bip3x::hdkey& key) {
    BytesVec sha_digest(32);
    trezor::SHA256_CTX ctx;
    sha256_Init(&ctx);
    sha256_Update(&ctx, key.public_key.cdata(), 33);
    sha256_Final(&ctx, sha_digest.data());

    BytesVec final_digest(20);
    ripemd160(sha_digest.data(), 32, final_digest.data());
    return final_digest;
}

BytesVec to_5bits(const BytesVec& bytes) {
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

LocalAccount accountFromMnemonic(std::string mnemonic, uint32_t subaccount_number) {
    const bip3x::bytes_64 seed = bip3x::bip3x_hdkey_encoder::make_bip39_seed(mnemonic);
    bip3x::hdkey key = bip3x::bip3x_hdkey_encoder::make_bip32_root_key(seed);
    bip3x::bip3x_hdkey_encoder::extend_key(key, BIP44_DERIVATION_PATH);
    auto fingerprint = calc_fingerprint(key);
    auto address = bech32::Encode(bech32::Encoding::BECH32, BECH32_PREFIX, to_5bits(fingerprint));
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