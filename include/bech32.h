//
// Created by carlos on 18-2-24.
//

#ifndef DYDX_CLIENT_BECH32_H
#define DYDX_CLIENT_BECH32_H

#include <cstdint>
#include <string>
#include <vector>

namespace bech32 {

enum class Encoding {
    INVALID, //!< Failed decoding
    BECH32,  //!< Bech32 encoding as defined in BIP173
    BECH32M, //!< Bech32m encoding as defined in BIP350
};

/** Encode a Bech32 or Bech32m string. If hrp contains uppercase characters, this will cause an
 *  assertion error. Encoding must be one of BECH32 or BECH32M. */
std::string Encode(Encoding encoding, const std::string& hrp, const std::vector<uint8_t>& values);

struct DecodeResult {
    Encoding encoding;         //!< What encoding was detected in the result; Encoding::INVALID if failed.
    std::string hrp;           //!< The human readable part
    std::vector<uint8_t> data; //!< The payload (excluding checksum)

    DecodeResult() : encoding(Encoding::INVALID) {}
    DecodeResult(Encoding enc, std::string&& h, std::vector<uint8_t>&& d) : encoding(enc), hrp(std::move(h)), data(std::move(d)) {}
};

/** Decode a Bech32 or Bech32m string. */
DecodeResult Decode(const std::string& str);

/** Return the positions of errors in a Bech32 string. */
std::pair<std::string, std::vector<int>> LocateErrors(const std::string& str);

} // namespace bech32

#endif // DYDX_CLIENT_BECH32_H
