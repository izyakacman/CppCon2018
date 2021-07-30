//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

#ifndef CPPCON2018_WEBSOCKET_SESSION_HPP
#define CPPCON2018_WEBSOCKET_SESSION_HPP

#include "net.hpp"
#include "beast.hpp"
#include "shared_state.hpp"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

// Forward declaration
class shared_state;

/** Represents an active WebSocket connection to the server
*/
class websocket_session : public std::enable_shared_from_this<websocket_session>
{
    beast::flat_buffer buffer_;
    websocket::stream<tcp::socket> ws_;
    std::shared_ptr<shared_state> state_;
    std::vector<std::shared_ptr<std::string const>> queue_;

    void fail(error_code ec, char const* what);
    void on_accept(error_code ec);
    void on_read(error_code ec, std::size_t bytes_transferred);
    void on_write(error_code ec, std::size_t bytes_transferred);

public:
    websocket_session(
        tcp::socket socket,
        std::shared_ptr<shared_state> const& state);

    ~websocket_session();

    void run();

    // Send a message
    void
    send(std::shared_ptr<std::string const> const& ss);
};

#endif
