// Day 14 — Deferred work queue (async-style preview, no Asio)

#define RUN_EXERCISES 0

#include "check.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class DeferredQueue {
    std::vector<std::function<void()>> q_;

public:
    void post(std::function<void()> fn) { q_.push_back(std::move(fn)); }

    void run_all() {
        for (auto& fn : q_) {
            fn();
        }
        q_.clear();
    }
};

struct Session : std::enable_shared_from_this<Session> {
    int value_{0};

    void start(DeferredQueue& dq) {
        auto self = shared_from_this();
        dq.post([self]() { self->value_ = 1; });
        dq.post([self]() { ++self->value_; });
    }

    void start_with_weak(DeferredQueue& dq) {
        std::weak_ptr<Session> weak = shared_from_this();
        dq.post([weak]() {
            if (auto self = weak.lock()) {
                self->value_ = 100;
            }
        });
    }
};

#if RUN_EXERCISES

void run_exercises() {
    DeferredQueue dq;
    auto s = std::make_shared<Session>();
    s->start_with_weak(dq);
    s.reset();
    dq.run_all();
    // Session destroyed — weak job should not resurrect it
    std::cout << "Exercise: assert no crash; extend with shared state checks.\n";
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    DeferredQueue dq;
    auto s = std::make_shared<Session>();
    s->start(dq);
    check(s->value_ == 0, "not run yet");
    dq.run_all();
    check(s->value_ == 2, "two posted jobs");

    run_exercises();
    std::cout << "day14 OK\n";
    return 0;
}
