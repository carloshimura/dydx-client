//
// Created by carlos on 18-2-24.
//

#ifndef DYDX_CLIENT_ACCOUNT_H
#define DYDX_CLIENT_ACCOUNT_H

#include <toolbox/data/bytes_array.h>


#include <string>
#include <cstdint>

struct LocalAccount {
    struct SubAccount {
        std::string m_address;
        uint32_t m_number;
    };
    SubAccount m_sub_account;
    std::string m_mnemonic;
    toolbox::data::bytes_array<33> m_public_key;
    toolbox::data::bytes_array<32> m_private_key;
};

#endif // DYDX_CLIENT_ACCOUNT_H
