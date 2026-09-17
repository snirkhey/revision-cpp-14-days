// Day 2 — const with pointers & const member functions

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <vector>

void demo_const_pointer() {
    int n = 5;
    const int* p = &n;
    check(*p == 5, "read through const int*");
    // *p = 1;  // uncomment to see compile error
}

class Counter {
    int n_{0};

public:
    int get() const { return n_; }
    void inc() { ++n_; }
};

class Stack {
    std::vector<int> data_;

public:
    void push(int v) { data_.push_back(v); }

    // TODO (exercise): implement empty() const — return true if no elements
    bool empty() const { return data_.empty(); }
};

void demo_const_members() {
    const Counter c;
    check(c.get() == 0, "const object can call const methods");
    // c.inc();  // compile error — good

    Counter mutable_c;
    mutable_c.inc();
    check(mutable_c.get() == 1, "non-const can inc");
}

#if RUN_EXERCISES

void run_exercises() {
    Stack s;
    check(s.empty(), "new stack empty");
    s.push(42);
    check(!s.empty(), "after push");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    demo_const_pointer();
    demo_const_members();
    run_exercises();
    std::cout << "day02 OK\n";
    return 0;
}
