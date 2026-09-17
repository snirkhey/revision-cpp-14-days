// Day 8 — shared_ptr & make_shared

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <memory>
#include <vector>

struct Foo {
    int value{0};
    explicit Foo(int v) : value(v) {}
};

void observe(std::shared_ptr<Foo> p) {
    check(p && p->value == 10, "observe sees Foo");
}

#if RUN_EXERCISES

void run_exercises() {
    auto a = std::make_shared<Foo>(1);
    std::vector<std::shared_ptr<Foo>> bag;
    bag.push_back(a);
    bag.push_back(a);
    check(a.use_count() == 3, "two vector slots + a");
    bag.clear();
    check(a.use_count() == 1, "Foo still alive via a");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto a = std::make_shared<int>(10);
    auto b = a;
    check(a.use_count() == 2, "shared ownership");

    auto foo = std::make_shared<Foo>(10);
    observe(foo);
    check(foo.use_count() == 1, "temporary copy in observe released");

    run_exercises();
    std::cout << "day08 OK\n";
    return 0;
}
