// Day 11 — Lambdas (syntax & captures)

#define RUN_EXERCISES 0

#include "check.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

auto make_adder(int k) {
    return [k](int x) { return x + k; };
}

#if RUN_EXERCISES

void run_exercises() {
    int x = 10;
    auto by_ref = [&x](int d) { x += d; };
    by_ref(5);
    check(x == 15, "mutable state through reference capture");

    auto by_val = [x](int d) { return x + d; };
    check(by_val(1) == 16, "copy capture frozen at creation time");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto add3 = make_adder(3);
    check(add3(4) == 7, "closure over k");

    std::vector<int> v{1, 2, 3};
    int sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
    check(sum == 6, "for_each with lambda");

    run_exercises();
    std::cout << "day11 OK\n";
    return 0;
}
