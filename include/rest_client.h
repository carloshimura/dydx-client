//
// Created by carlos on 20-2-24.
//

#ifndef DYDX_CLIENT_REST_CLIENT_H
#define DYDX_CLIENT_REST_CLIENT_H

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <glaze/json.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class RestClient {
private:
    std::string host;
    std::string port;

public:
    RestClient(std::string_view host, std::string_view port) : host(host), port(port) {}

    glz::json_t sendGetRequestAndWaitForResponse(std::string_view target) {
        // Check command line arguments.

        // The io_context is required for all I/O
        net::io_context ioc;

        // The SSL context is required, and holds certificates
        ssl::context ctx(ssl::context::tlsv12_client);

        // Do not verify the remote server's certificate
        ctx.set_verify_mode(ssl::verify_none);

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, 11};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        //        req.set(http::field::content_type, "application/json");

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out

        // Gracefully close the stream
        beast::error_code ec;
        stream.shutdown(ec);
        if (ec == net::error::eof) {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if (ec == ssl::error::stream_truncated) {
            // Rationale:
            // https://github.com/boostorg/beast/issues/824
            ec = {};
        }
        if (ec) {
            spdlog::error("Error on request: {}", ec.message());
        }

        glz::json_t json{};
        auto string_response = beast::buffers_to_string(res.body().data());
        //        spdlog::info("String message: {}", string_response);
        auto result = glz::read_json(json, string_response);
        if (result) {
            spdlog::error("Unable to parse response: {}", string_response);
            return {};
        }
        return json;
    }
};

#endif // DYDX_CLIENT_REST_CLIENT_H
