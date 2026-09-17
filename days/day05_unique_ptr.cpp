// Day 5 — unique_ptr & exclusive ownership

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

std::unique_ptr<int> make_int(int v) {
    return std::make_unique<int>(v);
}

void consume(std::unique_ptr<int> p) {
    check(p && *p == 42, "consume receives ownership");
}

#if RUN_EXERCISES

struct Dog {
    std::string name;
    explicit Dog(std::string n) : name(std::move(n)) {}
};

void set_owner(std::unique_ptr<Dog> dog) {
    // TODO: store or use dog; prove ownership transferred (e.g. check name)
    check(dog->name == "Rex", "set_owner has the dog");
}

void run_exercises() {
    auto d = std::make_unique<Dog>("Rex");
    set_owner(std::move(d));
    check(!d, "caller's unique_ptr is empty after move");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto p = std::make_unique<int>(42);
    auto q = std::move(p);
    check(!p && *q == 42, "move transfers unique ownership");

    consume(std::move(q));
    check(!q, "moved into consume");

    run_exercises();
    std::cout << "day05 OK\n";
    return 0;
}
