// Day 3 — RAII (constructors / destructors)

#define RUN_EXERCISES 0

#include "check.hpp"

#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>

class FileHolder {
    std::fstream f_;

public:
    explicit FileHolder(const char* path)
        : f_(path, std::ios::out | std::ios::trunc) {
        if (!f_) {
            throw std::runtime_error("open failed");
        }
    }

    void write_line(const std::string& line) { f_ << line << '\n'; }

    ~FileHolder() = default;
};

class MutexGuard {
    std::mutex& m_;

public:
    explicit MutexGuard(std::mutex& m) : m_(m) { m_.lock(); }
    ~MutexGuard() { m_.unlock(); }

    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator=(const MutexGuard&) = delete;
};

void demo_file_raii() {
    const char* path = "/tmp/cpp14days_day03.txt";
    FileHolder f(path);
    f.write_line("raii");
}

#if RUN_EXERCISES

void run_exercises() {
    std::mutex m;
    int counter = 0;
    {
        MutexGuard g(m);
        ++counter;
    }
    check(counter == 1, "mutex guard allowed critical section");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    demo_file_raii();
    run_exercises();
    std::cout << "day03 OK\n";
    return 0;
}
