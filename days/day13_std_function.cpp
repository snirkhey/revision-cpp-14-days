// Day 13 — std::function & type-erased callbacks

#define RUN_EXERCISES 0

#include "check.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

using Callback = std::function<void(int)>;

void invoke_all(const std::vector<Callback>& cbs, int v) {
    for (const auto& cb : cbs) {
        cb(v);
    }
}

class Button {
    std::function<void()> on_click_;

public:
    void set_on_click(std::function<void()> fn) { on_click_ = std::move(fn); }

    void click() {
        if (on_click_) {
            on_click_();
        }
    }
};

#if RUN_EXERCISES

class EventBus {
    std::vector<std::function<void(const std::string&)>> handlers_;

public:
    void subscribe(std::function<void(const std::string&)> h) {
        handlers_.push_back(std::move(h));
    }

    void publish(const std::string& msg) {
        // TODO: invoke all handlers
        for (auto& h : handlers_) {
            h(msg);
        }
    }
};

void run_exercises() {
    EventBus bus;
    int count = 0;
    bus.subscribe([&count](const std::string& m) {
        if (m == "ping") {
            ++count;
        }
    });
    bus.publish("ping");
    bus.publish("pong");
    check(count == 1, "event bus filtering");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

int main() {
    std::vector<Callback> cbs;
    int last = 0;
    cbs.push_back([&last](int x) { last = x; });
    cbs.push_back([prefix = std::string("v=")](int x) {
        std::cout << prefix << x << ' ';
    });

    invoke_all(cbs, 42);
    check(last == 42, "callback stored state");

    Button btn;
    bool clicked = false;
    btn.set_on_click([&clicked]() { clicked = true; });
    btn.click();
    check(clicked, "button callback");

    run_exercises();
    std::cout << "\nday13 OK\n";
    return 0;
}
