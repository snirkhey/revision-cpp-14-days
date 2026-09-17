#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

namespace {

class Fd {
public:
    Fd() : fd_(-1) {}
    explicit Fd(int fd) : fd_(fd) {}
    ~Fd() { reset(); }

    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;

    Fd(Fd&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
    Fd& operator=(Fd&& other) noexcept {
        if (this != &other) {
            reset();
            fd_ = other.fd_;
            other.fd_ = -1;
        }
        return *this;
    }

    int get() const { return fd_; }
    explicit operator bool() const { return fd_ >= 0; }

    void reset(int fd = -1) {
        if (fd_ >= 0) {
            ::close(fd_);
        }
        fd_ = fd;
    }

private:
    int fd_;
};

void check(int result, const char* what) {
    if (result < 0) {
        throw std::runtime_error(std::string(what) + ": " + std::strerror(errno));
    }
}

void echo_session(int client_fd) {
    std::vector<char> buf(4096);
    for (;;) {
        const ssize_t n = ::read(client_fd, buf.data(), buf.size());
        if (n == 0) {
            return;
        }
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            throw std::runtime_error(std::string("read: ") + std::strerror(errno));
        }
        ssize_t sent = 0;
        while (sent < n) {
            const ssize_t w = ::write(client_fd, buf.data() + sent,
                                      static_cast<size_t>(n - sent));
            if (w < 0) {
                if (errno == EINTR) {
                    continue;
                }
                throw std::runtime_error(std::string("write: ") + std::strerror(errno));
            }
            sent += w;
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    const uint16_t port =
        (argc > 1) ? static_cast<uint16_t>(std::stoi(argv[1])) : 8080;

    Fd listen_fd{::socket(AF_INET, SOCK_STREAM, 0)};
    if (!listen_fd) {
        std::cerr << "socket: " << std::strerror(errno) << '\n';
        return 1;
    }

    int yes = 1;
    check(::setsockopt(listen_fd.get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)),
          "setsockopt");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    check(::bind(listen_fd.get(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)), "bind");
    check(::listen(listen_fd.get(), SOMAXCONN), "listen");

    std::cout << "Echo server listening on port " << port << '\n';

    for (;;) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        const int client_fd = ::accept(listen_fd.get(),
                                       reinterpret_cast<sockaddr*>(&client_addr),
                                       &client_len);
        if (client_fd < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "accept: " << std::strerror(errno) << '\n';
            continue;
        }

        Fd client{client_fd};
        char ip[INET_ADDRSTRLEN]{};
        ::inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
        std::cout << "Client " << ip << ':' << ntohs(client_addr.sin_port) << '\n';

        try {
            echo_session(client.get());
        } catch (const std::exception& ex) {
            std::cerr << "session error: " << ex.what() << '\n';
        }

        std::cout << "Client disconnected\n";
    }
}
