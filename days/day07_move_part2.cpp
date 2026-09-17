// Day 7 — Move-only types & transferring unique_ptr

#define RUN_EXERCISES 0

#include "check.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Connection {
    std::unique_ptr<int> id_;

public:
    explicit Connection(std::unique_ptr<int> id) : id_(std::move(id)) {}

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&&) = default;
    Connection& operator=(Connection&&) = default;

    int id() const { return id_ ? *id_ : -1; }
};

#if RUN_EXERCISES

class LogFile {
    std::unique_ptr<std::fstream> file_;

public:
    // TODO: open path in ctor, expose write_line; move-only
    explicit LogFile(const char* path);
    void write_line(const std::string& line);
    LogFile(const LogFile&) = delete;
    LogFile& operator=(const LogFile&) = delete;
    LogFile(LogFile&&) = default;
    LogFile& operator=(LogFile&&) = default;
};

// Stub — implement in exercise section
LogFile::LogFile(const char*) {}
void LogFile::write_line(const std::string&) {}

void run_exercises() {
    (void)sizeof(LogFile);
    std::cout << "Implement LogFile for full exercise check.\n";
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto id = std::make_unique<int>(99);
    Connection c(std::move(id));
    check(!id && c.id() == 99, "connection owns id");

    Connection c2 = std::move(c);
    check(c.id() == -1 && c2.id() == 99, "moved connection");

    run_exercises();
    std::cout << "day07 OK\n";
    return 0;
}
