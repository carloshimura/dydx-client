//
// Created by carlos on 25-2-24.
//

#ifndef DYDX_CLIENT_MARKET_INFO_H
#define DYDX_CLIENT_MARKET_INFO_H

#include <cstdint>
#include <glaze/json.hpp>
#include <string>

struct MarketInfo {
    std::string key;
    uint32_t clobPairID;
    int32_t atomicResolution;
    int32_t quantumConversionExponent;
    uint64_t stepBaseQuantums;
    uint64_t subticksPerTick;
};

MarketInfo fromJson(const glz::json_t& json, std::string_view key) {
    auto marketPair = json["markets"][key];
    return MarketInfo{.key = std::string(key),
                      .clobPairID = static_cast<uint32_t>(std::stoul(marketPair["clobPairId"].get<std::string>())),
                      .atomicResolution = static_cast<int32_t>(marketPair["atomicResolution"].get<double>()),
                      .quantumConversionExponent = static_cast<int32_t>(marketPair["quantumConversionExponent"].get<double>()),
                      .stepBaseQuantums = static_cast<uint64_t>(marketPair["stepBaseQuantums"].get<double>()),
                      .subticksPerTick = static_cast<uint64_t>(marketPair["subticksPerTick"].get<double>())};
}

#endif // DYDX_CLIENT_MARKET_INFO_H
