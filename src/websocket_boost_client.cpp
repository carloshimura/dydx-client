//
// Created by carlos on 11-2-24.
//

#include "websocket_boost_client.h"

#include <boost/asio/ssl.hpp>

namespace {
void fail(boost::system::error_code ec, std::string_view where) {
    spdlog::error("Error on {}: {}", where, ec.what());
}
} // namespace

// Resolver and socket require an io_context
BoostWebSocketClient::BoostWebSocketClient(boost::asio::io_context &ioc)
    : resolver_(ioc), ws_(ioc, ctx_webSocket) {}

// Start the asynchronous operation
void BoostWebSocketClient::connect(std::string_view host, std::string_view port, std::string_view target) {
    // Save these for later
    host_ = host;
    target_ = target;
    boost::system::error_code ec;

    if (!SSL_set_tlsext_host_name(ws_.next_layer().native_handle(),
                                  host_.c_str())) {
        throw boost::beast::system_error(
            boost::beast::error_code(static_cast<int>(::ERR_get_error()),
                                     boost::asio::error::get_ssl_category()),
            "Failed to set SNI Hostname");
    }

    auto resolve = resolver_.resolve(host, port, ec);
    on_resolve(ec, resolve);
}

void BoostWebSocketClient::on_resolve(boost::system::error_code ec,
                                 tcp::resolver::results_type results) {
    if (ec)
        return fail(ec, "resolve");

    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(ws_.next_layer().next_layer(), results.begin(),
                         results.end(), ec);
    on_connect(ec);
}

void BoostWebSocketClient::on_connect(boost::system::error_code ec) {
    if (ec)
        return fail(ec, "connect");

    ws_.next_layer().handshake(boost::asio::ssl::stream_base::client, ec);
    on_handshake(ec);
}

void BoostWebSocketClient::on_handshake(boost::system::error_code ec) {
    if (ec)
        return fail(ec, "handshake");

    ws_.handshake(host_, target_, ec);
    if (ec) {
        return fail(ec, "handshake follow up");
    }
}

void BoostWebSocketClient::send_message(boost::asio::const_buffer data) {

    boost::system::error_code ec;
    auto transferred = ws_.write(boost::asio::buffer(data), ec);
    on_write(ec, transferred);
}
void BoostWebSocketClient::on_write(boost::system::error_code ec,
                               std::size_t ) {
//    boost::ignore_unused(bytes_transferred);

    if (ec) {
        fail(ec, "write");
        return;
    } else {
//        spdlog::info("Sent!");
    }
}

void BoostWebSocketClient::read_data() {
    // Read a message into our buffer
    boost::system::error_code ec;
    auto transferred = ws_.read(buffer_, ec);
    on_read(ec, transferred);
}
void BoostWebSocketClient::on_read(boost::system::error_code ec,
                              std::size_t bytes_transferred) {

    if (ec)
        return fail(ec, "read");
    std::string data = boost::beast::buffers_to_string(buffer_.data());
    spdlog::info("Received: {}", data);
}

void BoostWebSocketClient::close() {
    // Close the WebSocket connection
    boost::system::error_code ec;
    ws_.close(websocket::close_code::normal, ec);
    on_close(ec);
}

void BoostWebSocketClient::on_close(boost::system::error_code ec) {
    if (ec)
        return fail(ec, "close");
}
