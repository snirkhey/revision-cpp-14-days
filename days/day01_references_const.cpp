// Day 1 — References & const
// Build: make day01_references_const && ./day01_references_const
// Set RUN_EXERCISES to 1 after implementing the exercise section below.

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <string>
#include <vector>

// --- Demos (read and run) ---

void bump(int& x) { ++x; }

int double_val(int x) { return x * 2; }

void print_message(const std::string& s) {
    (void)s;
}

void demo_references() {
    int a = 1;
    bump(a);
    check(a == 2, "bump should modify caller's int");

    const int& cref = a;
    check(cref == 2, "const ref sees updated value");

    int b = double_val(a);
    check(b == 4 && a == 2, "pass-by-value copies");

    std::string msg = "hello";
    print_message(msg);
}

#if RUN_EXERCISES

void swap_ints(int& a, int& b) {
    // TODO: exchange values without std::swap if you want the practice
}

int sum_vector(const std::vector<int>& v) {
    // TODO: return sum of elements
    return 0;
}

void run_exercises() {
    int x = 3, y = 7;
    swap_ints(x, y);
    check(x == 7 && y == 3, "swap_ints");

    check(sum_vector({1, 2, 3, 4}) == 10, "sum_vector");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1 in this file).\n";
}

#endif

int main() {
    demo_references();
    run_exercises();
    std::cout << "day01 OK\n";
    return 0;
}
