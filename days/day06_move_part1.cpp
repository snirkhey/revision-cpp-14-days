// Day 6 — Move semantics (part 1)

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<int> build_large() {
    return std::vector<int>(1000, 7);
}

#if RUN_EXERCISES

struct Buffer {
    std::vector<char> data;
    explicit Buffer(std::size_t n) : data(n, 'x') {}
};

Buffer take(Buffer b) {
    // TODO: return b by value (move happens automatically)
    return b;
}

void run_exercises() {
    Buffer in(100);
    Buffer out = take(std::move(in));
    check(out.data.size() == 100, "take returned buffer");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    std::vector<int> a = build_large();
    check(a.size() == 1000, "returned vector");

    std::vector<int> b = std::move(a);
    check(b.size() == 1000, "moved-to vector");

    std::string s = "hello";
    std::string t = std::move(s);
    check(t == "hello", "moved string content");

    run_exercises();
    std::cout << "day06 OK\n";
    return 0;
}
