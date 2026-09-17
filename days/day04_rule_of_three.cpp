// Day 4 — Copy danger & deleting copies (rule of three awareness)

#define RUN_EXERCISES 0

#include "check.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

// Good: std::vector owns its memory with correct copy/destroy semantics.
class Blob {
    std::vector<int> data_;

public:
    explicit Blob(std::size_t n) : data_(n, 0) {}
    std::size_t size() const { return data_.size(); }
};

#if RUN_EXERCISES

// TODO: Implement a move-only Handle using unique_ptr<int> internally,
// or delete copy operations on a raw-pointer version you write yourself.
class Handle {
    int* p_{nullptr};

public:
    explicit Handle(int v) : p_(new int(v)) {}
    ~Handle() { delete p_; }

    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;

    Handle(Handle&& other) noexcept : p_(other.p_) { other.p_ = nullptr; }
    Handle& operator=(Handle&& other) noexcept {
        if (this != &other) {
            delete p_;
            p_ = other.p_;
            other.p_ = nullptr;
        }
        return *this;
    }

    int get() const { return p_ ? *p_ : 0; }
};

void run_exercises() {
    Handle a(10);
    Handle b = std::move(a);
    check(b.get() == 10, "moved-from handle");
    check(a.get() == 0, "moved-from empty");
}

#else

void run_exercises() {
    std::cout << "Exercises skipped (set RUN_EXERCISES to 1).\n";
}

#endif

void demo_blob_composes() {
    Blob a(3);
    Blob b = a;
    check(a.size() == 3 && b.size() == 3, "vector member copies safely");
}

int main() {
    demo_blob_composes();
    run_exercises();
    std::cout << "day04 OK\n";
    return 0;
}
