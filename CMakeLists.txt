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


SET(SOURCES
        src/main.cpp
        src/websocket_boost_client.cpp
        include/websocket_boost_client.h
        include/wallet.h
        include/order.h
)

add_executable(${PROJECT_NAME}
        include/bech32.h
        src/bech32.cpp
        src/account.cpp
        include/account.h
        src/rest_client.cpp
        include/rest_client.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/trezor-crypto)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${BIP3X_SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        gtest::gtest
        Boost::boost
        openssl::openssl
        spdlog::spdlog
        OpenSSL::Crypto
        toolbox::toolbox
        bip3x::bip3x
        glaze::glaze)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
#set_property(TARGET ${PROJECT_NAME} PROPERTY
#        $<$<CONFIG:Release>:INTERPROCEDURAL_OPTIMIZATION>
#)