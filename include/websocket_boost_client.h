//
// Created by carlos on 11-2-24.
//

#ifndef DYDX_CLIENT_WEBSOCKET_BOOST_CLIENT_H
#define DYDX_CLIENT_WEBSOCKET_BOOST_CLIENT_H

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>

using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
namespace websocket =
    boost::beast::websocket; // from <boost/beast/websocket.hpp>

// Sends a WebSocket message and prints the response
class BoostWebSocketClient {
  private:
    tcp::resolver resolver_;
    boost::asio::ssl::context       ctx_webSocket{boost::asio::ssl::context::tlsv12_client};
    websocket::stream<boost::beast::ssl_stream<tcp::socket>> ws_;
    boost::beast::multi_buffer buffer_;
    std::string host_;
    std::string target_;
  public:
    // Resolver and socket require an io_context
    explicit BoostWebSocketClient(boost::asio::io_context &ioc);

    // Start the asynchronous operation
    void connect(std::string_view host, std::string_view port, std::string_view target);
    void on_resolve(boost::system::error_code ec,
                    tcp::resolver::results_type results);
    void on_connect(boost::system::error_code ec);
    void on_handshake(boost::system::error_code ec);
    void send_message(boost::asio::const_buffer data);
    void on_write(boost::system::error_code ec, std::size_t bytes_transferred);
    void read_data();
    void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
    void close();
    void on_close(boost::system::error_code ec);
};

#endif // DYDX_CLIENT_WEBSOCKET_BOOST_CLIENT_H
