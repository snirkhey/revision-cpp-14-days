// Day 9 — weak_ptr & breaking cycles

#define RUN_EXERCISES 0

#include "check.hpp"

#include <iostream>
#include <memory>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    int id{0};
};

void maybe_use(std::weak_ptr<int> w) {
    if (auto sp = w.lock()) {
        check(*sp == 42, "weak_ptr locked to live object");
    }
}

#if RUN_EXERCISES

void run_exercises() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->prev = a;
    check(a.use_count() == 1 && b.use_count() == 2, "prev is weak — no cycle on a");

    std::weak_ptr<Node> w = b;
    b.reset();
    check(w.expired(), "b gone, weak observes");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> w = sp;
    maybe_use(w);

    sp.reset();
    check(w.expired(), "object destroyed");

    run_exercises();
    std::cout << "day09 OK\n";
    return 0;
}
