//
// Created by carlos on 25-2-24.
//

#ifndef DYDX_CLIENT_DYDX_CONFIG_H
#define DYDX_CLIENT_DYDX_CONFIG_H

#include <cstdint>
#include <string>

struct DyDxConfig {
    std::string chainId;
    uint64_t feeMinimumGasPrice;
    std::string feeDenom;
};

inline const std::string NETWORK_ID_TESTNET = "dydx-testnet-4";
inline const DyDxConfig EXCHANGE_CONFIG_LOCAL_PLAINTEXT_NODE_TESTNET{.chainId = NETWORK_ID_TESTNET, .feeMinimumGasPrice = 40000000000, .feeDenom = "adv4tnt"};

#endif // DYDX_CLIENT_DYDX_CONFIG_H
