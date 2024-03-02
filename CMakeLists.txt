cmake_minimum_required(VERSION 3.23)

project(
        dydx-client
        VERSION 1.0
        LANGUAGES C CXX)

include(CheckIPOSupported)

find_package(GTest CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(bip3x CONFIG REQUIRED)
find_package(toolbox CONFIG REQUIRED)
find_package(glaze CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

if (BUILD_PROTOBUF_FILES)
    # build from .proto files
    SET(PROTO_FILES
            proto/dydxprotocol/subaccounts/perpetual_position.proto
            proto/dydxprotocol/subaccounts/asset_position.proto
            proto/cosmos_proto/cosmos.proto
            proto/dydxprotocol/subaccounts/subaccount.proto
            proto/gogoproto/gogo.proto
            proto/dydxprotocol/clob/order.proto
            proto/dydxprotocol/clob/tx.proto
            proto/dydxprotocol/clob/matches.proto
            proto/dydxprotocol/clob/order_removals.proto
            proto/cosmos/auth/v1beta1/auth.proto
            proto/cosmos/auth/v1beta1/query.proto
            proto/cosmos/query/v1/query.proto
            proto/cosmos/crypto/secp256k1/keys.proto
            proto/cosmos/tx/signing/v1beta1/signing.proto
            proto/cosmos/tx/v1beta1/tx.proto
            proto/cosmos/tx/v1beta1/service.proto
            proto/cosmos/crypto/multisig/v1beta1/multisig.proto
            proto/cosmos/base/v1beta1/coin.proto
            proto/cosmos/base/abci/v1beta1/abci.proto
            proto/cosmos/base/query/v1beta1/pagination.proto
            proto/amino/amino.proto
            proto/tendermint/abci/types.proto
            proto/tendermint/crypto/proof.proto
            proto/tendermint/types/block.proto
            proto/tendermint/types/evidence.proto
            proto/tendermint/crypto/keys.proto
            proto/tendermint/types/params.proto
            proto/tendermint/types/types.proto
            proto/tendermint/types/validator.proto
            proto/tendermint/version/types.proto
            proto/google/api/annotations.proto
            proto/google/api/http.proto
            proto/cosmos/base/tendermint/v1beta1/query.proto
            proto/cosmos/base/tendermint/v1beta1/types.proto
            proto/tendermint/p2p/types.proto
    )


    add_library(proto-objects OBJECT ${PROTO_FILES})
    target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf grpc::grpc)
    set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    target_include_directories(proto-objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")
    file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")
    protobuf_generate(
            TARGET proto-objects
            IMPORT_DIRS "${CMAKE_SOURCE_DIR}/proto"
            PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

    protobuf_generate(
            TARGET proto-objects
            LANGUAGE grpc
            GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
            PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
            IMPORT_DIRS ${PROTO_IMPORT_DIRS} "${CMAKE_SOURCE_DIR}/proto"
            PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")
else()
    # Use pre-built files patched due to invalid service name (for C++)
    SET(PROTO_FILES
            generated/dydxprotocol/clob/tx.pb.h
            generated/dydxprotocol/clob/order_removals.grpc.pb.h
            generated/dydxprotocol/clob/order_removals.pb.cc
            generated/dydxprotocol/clob/order.pb.h
            generated/dydxprotocol/clob/matches.pb.h
            generated/dydxprotocol/clob/matches.grpc.pb.h
            generated/dydxprotocol/clob/matches.grpc.pb.cc
            generated/dydxprotocol/clob/order.grpc.pb.cc
            generated/dydxprotocol/clob/order.grpc.pb.h
            generated/dydxprotocol/clob/tx.grpc.pb.h
            generated/dydxprotocol/clob/order_removals.grpc.pb.cc
            generated/dydxprotocol/clob/tx.grpc.pb.cc
            generated/dydxprotocol/clob/matches.pb.cc
            generated/dydxprotocol/clob/order.pb.cc
            generated/dydxprotocol/clob/tx.pb.cc
            generated/dydxprotocol/clob/order_removals.pb.h
            generated/dydxprotocol/subaccounts/perpetual_position.grpc.pb.cc
            generated/dydxprotocol/subaccounts/perpetual_position.pb.cc
            generated/dydxprotocol/subaccounts/asset_position.grpc.pb.cc
            generated/dydxprotocol/subaccounts/subaccount.pb.cc
            generated/dydxprotocol/subaccounts/perpetual_position.pb.h
            generated/dydxprotocol/subaccounts/subaccount.pb.h
            generated/dydxprotocol/subaccounts/perpetual_position.grpc.pb.h
            generated/dydxprotocol/subaccounts/asset_position.grpc.pb.h
            generated/dydxprotocol/subaccounts/subaccount.grpc.pb.h
            generated/dydxprotocol/subaccounts/asset_position.pb.h
            generated/dydxprotocol/subaccounts/subaccount.grpc.pb.cc
            generated/dydxprotocol/subaccounts/asset_position.pb.cc
            generated/google/api/http.grpc.pb.cc
            generated/google/api/annotations.grpc.pb.cc
            generated/google/api/annotations.grpc.pb.h
            generated/google/api/annotations.pb.h
            generated/google/api/annotations.pb.cc
            generated/google/api/http.pb.cc
            generated/google/api/http.grpc.pb.h
            generated/google/api/http.pb.h
            generated/gogoproto/gogo.pb.h
            generated/gogoproto/gogo.grpc.pb.h
            generated/gogoproto/gogo.grpc.pb.cc
            generated/gogoproto/gogo.pb.cc
            generated/amino/amino.pb.h
            generated/amino/amino.grpc.pb.h
            generated/amino/amino.pb.cc
            generated/amino/amino.grpc.pb.cc
            generated/tendermint/abci/types.pb.cc
            generated/tendermint/abci/types.pb.h
            generated/tendermint/abci/types.grpc.pb.h
            generated/tendermint/abci/types.grpc.pb.cc
            generated/tendermint/p2p/types.pb.cc
            generated/tendermint/p2p/types.pb.h
            generated/tendermint/p2p/types.grpc.pb.h
            generated/tendermint/p2p/types.grpc.pb.cc
            generated/tendermint/crypto/keys.grpc.pb.cc
            generated/tendermint/crypto/proof.grpc.pb.cc
            generated/tendermint/crypto/keys.grpc.pb.h
            generated/tendermint/crypto/keys.pb.h
            generated/tendermint/crypto/proof.pb.h
            generated/tendermint/crypto/keys.pb.cc
            generated/tendermint/crypto/proof.grpc.pb.h
            generated/tendermint/crypto/proof.pb.cc
            generated/tendermint/types/types.pb.cc
            generated/tendermint/types/block.grpc.pb.cc
            generated/tendermint/types/params.grpc.pb.cc
            generated/tendermint/types/validator.pb.cc
            generated/tendermint/types/validator.pb.h
            generated/tendermint/types/params.grpc.pb.h
            generated/tendermint/types/evidence.pb.h
            generated/tendermint/types/params.pb.h
            generated/tendermint/types/block.pb.cc
            generated/tendermint/types/types.pb.h
            generated/tendermint/types/block.pb.h
            generated/tendermint/types/validator.grpc.pb.h
            generated/tendermint/types/evidence.grpc.pb.cc
            generated/tendermint/types/evidence.pb.cc
            generated/tendermint/types/evidence.grpc.pb.h
            generated/tendermint/types/validator.grpc.pb.cc
            generated/tendermint/types/params.pb.cc
            generated/tendermint/types/types.grpc.pb.h
            generated/tendermint/types/block.grpc.pb.h
            generated/tendermint/types/types.grpc.pb.cc
            generated/tendermint/version/types.pb.cc
            generated/tendermint/version/types.pb.h
            generated/tendermint/version/types.grpc.pb.h
            generated/tendermint/version/types.grpc.pb.cc
            generated/cosmos_proto/cosmos.grpc.pb.cc
            generated/cosmos_proto/cosmos.grpc.pb.h
            generated/cosmos_proto/cosmos.pb.cc
            generated/cosmos_proto/cosmos.pb.h
            generated/cosmos/crypto/multisig/v1beta1/multisig.grpc.pb.cc
            generated/cosmos/crypto/multisig/v1beta1/multisig.pb.h
            generated/cosmos/crypto/multisig/v1beta1/multisig.pb.cc
            generated/cosmos/crypto/multisig/v1beta1/multisig.grpc.pb.h
            generated/cosmos/crypto/secp256k1/keys.grpc.pb.cc
            generated/cosmos/crypto/secp256k1/keys.grpc.pb.h
            generated/cosmos/crypto/secp256k1/keys.pb.h
            generated/cosmos/crypto/secp256k1/keys.pb.cc
            generated/cosmos/base/abci/v1beta1/abci.pb.cc
            generated/cosmos/base/abci/v1beta1/abci.grpc.pb.h
            generated/cosmos/base/abci/v1beta1/abci.pb.h
            generated/cosmos/base/abci/v1beta1/abci.grpc.pb.cc
            generated/cosmos/base/query/v1beta1/pagination.pb.h
            generated/cosmos/base/query/v1beta1/pagination.grpc.pb.cc
            generated/cosmos/base/query/v1beta1/pagination.grpc.pb.h
            generated/cosmos/base/query/v1beta1/pagination.pb.cc
            generated/cosmos/base/v1beta1/coin.pb.h
            generated/cosmos/base/v1beta1/coin.pb.cc
            generated/cosmos/base/v1beta1/coin.grpc.pb.cc
            generated/cosmos/base/v1beta1/coin.grpc.pb.h
            generated/cosmos/base/tendermint/v1beta1/query.grpc.pb.cc
            generated/cosmos/base/tendermint/v1beta1/types.pb.cc
            generated/cosmos/base/tendermint/v1beta1/query.grpc.pb.h
            generated/cosmos/base/tendermint/v1beta1/types.pb.h
            generated/cosmos/base/tendermint/v1beta1/query.pb.cc
            generated/cosmos/base/tendermint/v1beta1/query.pb.h
            generated/cosmos/base/tendermint/v1beta1/types.grpc.pb.h
            generated/cosmos/base/tendermint/v1beta1/types.grpc.pb.cc
            generated/cosmos/query/v1/query.grpc.pb.cc
            generated/cosmos/query/v1/query.grpc.pb.h
            generated/cosmos/query/v1/query.pb.cc
            generated/cosmos/query/v1/query.pb.h
            generated/cosmos/auth/v1beta1/query.grpc.pb.cc
            generated/cosmos/auth/v1beta1/query.grpc.pb.h
            generated/cosmos/auth/v1beta1/query.pb.cc
            generated/cosmos/auth/v1beta1/query.pb.h
            generated/cosmos/auth/v1beta1/auth.pb.cc
            generated/cosmos/auth/v1beta1/auth.grpc.pb.cc
            generated/cosmos/auth/v1beta1/auth.grpc.pb.h
            generated/cosmos/auth/v1beta1/auth.pb.h
            generated/cosmos/tx/signing/v1beta1/signing.grpc.pb.h
            generated/cosmos/tx/signing/v1beta1/signing.grpc.pb.cc
            generated/cosmos/tx/signing/v1beta1/signing.pb.cc
            generated/cosmos/tx/signing/v1beta1/signing.pb.h
            generated/cosmos/tx/v1beta1/tx.pb.h
            generated/cosmos/tx/v1beta1/service.grpc.pb.cc
            generated/cosmos/tx/v1beta1/tx.grpc.pb.h
            generated/cosmos/tx/v1beta1/service.grpc.pb.h
            generated/cosmos/tx/v1beta1/service.pb.cc
            generated/cosmos/tx/v1beta1/tx.grpc.pb.cc
            generated/cosmos/tx/v1beta1/tx.pb.cc
            generated/cosmos/tx/v1beta1/service.pb.h

    )
    add_library(proto-objects OBJECT ${PROTO_FILES})
    include_directories(${CMAKE_SOURCE_DIR}/generated)
    target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf grpc::grpc)
endif()

SET(SOURCES
        src/main.cpp
        include/order.h
        include/bech32.h
        src/bech32.cpp
        include/account.h
        include/rest_client.h
        src/grpc_client.cpp
        src/account.cpp
        include/grpc_client.h
        include/dydx_config.h
        include/market_info.h
)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/trezor-crypto)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        proto-objects
        gtest::gtest
        Boost::boost
        openssl::openssl
        spdlog::spdlog
        OpenSSL::Crypto
        protobuf::protobuf
        grpc::grpc
        toolbox::toolbox
        bip3x::bip3x
        glaze::glaze)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY
        $<$<CONFIG:Release>:INTERPROCEDURAL_OPTIMIZATION>
)