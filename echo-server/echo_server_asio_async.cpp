#include <asio.hpp>

#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { begin_chunk(); }

private:
    void begin_chunk() {
        read_len_ = 0;
        read_more();
    }

    void read_more() {
        auto self = shared_from_this();
        const std::size_t cap = buf_.size() - read_len_;
        if (cap == 0) {
            do_write(read_len_);
            return;
        }

        socket_.async_read_some(
            asio::buffer(buf_.data() + read_len_, cap),
            [this, self](asio::error_code ec, std::size_t n) {
                if (ec) {
                    return;
                }
                read_len_ += n;

                asio::error_code aec;
                const std::size_t avail = socket_.available(aec);
                if (!aec && avail > 0 && read_len_ < buf_.size()) {
                    read_more();
                } else {
                    do_write(read_len_);
                }
            });
    }

    void do_write(std::size_t n) {
        auto self = shared_from_this();
        asio::async_write(
            socket_, asio::buffer(buf_.data(), n),
            [this, self](asio::error_code ec, std::size_t /*written*/) {
                if (!ec) {
                    begin_chunk();
                }
            });
    }

    tcp::socket socket_;
    std::array<char, 4096> buf_{};
    std::size_t read_len_{0};
};

class Server {
public:
    Server(asio::io_context& io, unsigned short port)
        : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
            [this](asio::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket))->start();
                }
                do_accept();
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    const unsigned short port =
        (argc > 1) ? static_cast<unsigned short>(std::stoi(argv[1])) : 8080;

    asio::io_context io;
    Server server(io, port);
    std::cout << "Async echo on port " << port << '\n';
    io.run();
}
