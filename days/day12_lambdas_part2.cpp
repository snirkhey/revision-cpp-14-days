// Day 12 — Lambdas: mutable, this, move capture

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

auto make_buffer_processor(std::vector<char> buf) {
    return [b = std::move(buf)](std::ostream& out) {
        out.write(b.data(), static_cast<std::streamsize>(b.size()));
    };
}

#if RUN_EXERCISES

void run_exercises() {
    int n = 0;
    auto counter = [n](int x) mutable { return ++n + x; };
    check(counter(10) == 11, "first mutable call");
    check(counter(10) == 12, "second mutable call");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    std::vector<char> data{'h', 'i'};
    auto proc = make_buffer_processor(std::move(data));
    check(data.empty(), "source buffer moved into lambda");

    std::ostringstream oss;
    proc(oss);
    check(oss.str() == "hi", "processor writes moved buffer");

    run_exercises();
    std::cout << "day12 OK\n";
    return 0;
}
