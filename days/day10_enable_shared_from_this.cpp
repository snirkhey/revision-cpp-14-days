// Day 10 — enable_shared_from_this

#define RUN_EXERCISES 0

#include "check.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

struct Job : std::enable_shared_from_this<Job> {
    int step_count{0};

    void start(std::vector<std::function<void()>>& queue) {
        auto self = shared_from_this();
        queue.push_back([self]() { self->step(); });
    }

    void step() { ++step_count; }
};

#if RUN_EXERCISES

struct Worker : std::enable_shared_from_this<Worker> {
    int value{0};

    void schedule(std::vector<std::function<void()>>& q) {
        // TODO: post two lambdas that each increment value, capturing self safely
        auto self = shared_from_this();
        q.push_back([self]() { ++self->value; });
        q.push_back([self]() { ++self->value; });
    }
};

void run_exercises() {
    std::vector<std::function<void()>> q;
    auto w = std::make_shared<Worker>();
    w->schedule(q);
    for (auto& fn : q) {
        fn();
    }
    check(w->value == 2, "both deferred jobs ran");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    auto job = std::make_shared<Job>();
    std::vector<std::function<void()>> queue;
    job->start(queue);
    check(queue.size() == 1, "one posted step");
    queue.front()();
    check(job->step_count == 1, "step ran while job alive");

    run_exercises();
    std::cout << "day10 OK\n";
    return 0;
}
