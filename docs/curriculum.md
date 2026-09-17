# 2-week curriculum (detail)

## Week 1 — Ownership on the stack and with `unique_ptr`

### Day 1 — References & `const`

- Pass-by-reference vs by-value; `const T&` for read-only inputs.
- Exercises: `swap_ints`, `sum_vector`.

### Day 2 — `const` with pointers & members

- `const int*` vs `int* const`; `const` member functions.
- Exercises: `Stack::empty() const`.

### Day 3 — RAII

- Acquire in ctor, release in dtor; compose with standard types.
- Exercises: `MutexGuard` pattern.

### Day 4 — Rule of three (awareness)

- Why raw owning pointers are dangerous to copy; delete copies or use move-only types.
- Exercises: move-only `Handle`.

### Day 5 — `unique_ptr`

- Exclusive ownership; `make_unique`; pass by value to transfer.
- Exercises: `set_owner(std::unique_ptr<Dog>)`.

### Day 6 — Move (part 1)

- `std::move`; moved-from state; return by value.
- Exercises: `take(Buffer)`.

### Day 7 — Move (part 2)

- Move-only classes wrapping resources.
- Exercises: `LogFile` (optional implementation).

## Week 2 — Shared ownership & callbacks

### Day 8 — `shared_ptr`

- `make_shared`; `use_count`; never two `shared_ptr` from same raw `new`.
- Exercises: vector of shared `Foo`.

### Day 9 — `weak_ptr`

- Break cycles; `lock()` / `expired()`.
- Exercises: `Node` with `weak_ptr` prev.

### Day 10 — `enable_shared_from_this`

- Only after `make_shared`; safe deferred `self` capture.
- Exercises: `Worker::schedule`.

### Day 11 — Lambdas (1)

- Captures; `make_adder`; algorithms.
- Exercises: ref vs value capture behavior.

### Day 12 — Lambdas (2)

- `mutable`; move capture; avoid `[this]` for deferred work.
- Exercises: mutable counter lambda.

### Day 13 — `std::function`

- Type-erased callbacks; `Button`; simple event bus.
- Exercises: `EventBus::publish`.

### Day 14 — Deferred queue

- `post` + `run_all`; `shared_from_this` vs `weak_ptr` on teardown.
- Bridge to real async I/O later (Asio, thread pools, coroutines).

## Self-check questions (end of each week)

**Week 1:** When to use `const&`? What does `std::move` do *not* do by itself? Who owns after `unique_ptr` move?

**Week 2:** `shared` vs `unique`? Why `weak_ptr`? Why not `shared_from_this` in ctor? Why capture `self` in deferred lambdas?
