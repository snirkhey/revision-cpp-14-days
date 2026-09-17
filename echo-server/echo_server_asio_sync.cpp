#include <asio.hpp>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

using asio::ip::tcp;

// Block until at least one byte arrives, then read any further bytes already
// buffered in the kernel (read_some may return fewer than offered).
static std::size_t read_chunk(tcp::socket& socket, std::array<char, 4096>& buf,
                              asio::error_code& ec) {
    std::size_t n =
        asio::read(socket, asio::buffer(buf), asio::transfer_at_least(1), ec);
    if (ec) {
        return 0;
    }

    while (n < buf.size()) {
        const std::size_t avail = socket.available(ec);
        if (ec || avail == 0) {
            break;
        }
        const std::size_t cap = std::min(avail, buf.size() - n);
        const std::size_t m =
            socket.read_some(asio::buffer(buf.data() + n, cap), ec);
        if (ec == asio::error::eof) {
            n += m;
            return n;
        }
        if (ec) {
            break;
        }
        n += m;
    }
    return n;
}

static void echo_session(tcp::socket socket) {
    try {
        std::array<char, 4096> buf{};
        asio::error_code ec;

        for (;;) {
            ec.clear();
            const std::size_t n = read_chunk(socket, buf, ec);
            if (ec == asio::error::eof) {
                break;
            }
            if (ec) {
                throw std::system_error(ec);
            }
            if (n == 0) {
                break;
            }

            asio::write(socket, asio::buffer(buf.data(), n), ec);
            if (ec) {
                throw std::system_error(ec);
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "session: " << ex.what() << '\n';
    }
}

int main(int argc, char* argv[]) {
    try {
        const unsigned short port =
            (argc > 1) ? static_cast<unsigned short>(std::stoi(argv[1])) : 8080;

        asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));

        std::cout << "Echo server listening on port " << port << '\n';

        for (;;) {
            tcp::socket socket(io);
            acceptor.accept(socket);

            std::thread(echo_session, std::move(socket)).detach();
        }
    } catch (const std::exception& ex) {
        std::cerr << "fatal: " << ex.what() << '\n';
        return 1;
    }
}
