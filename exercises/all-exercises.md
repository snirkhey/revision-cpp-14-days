# All exercises — revision-cpp-14-days

Source files: `days/dayNN_*.cpp` — enable with `#define RUN_EXERCISES 1`.

---

## Week 1

### Day 1 — References & `const`  
**File:** `days/day01_references_const.cpp`

1. Implement `void swap_ints(int& a, int& b)` — exchange two integers (you may avoid `std::swap` for practice).
2. Implement `int sum_vector(const std::vector<int>& v)` — return the sum of all elements.

**Think about:**
- When is `const T&` a better parameter type than `T`?
- `void store(const std::string& s) { member_ = s; }` — is that OK? When would you take `std::string` by value instead?

---

### Day 2 — `const` pointers & member functions  
**File:** `days/day02_const_pointers_members.cpp`

1. Implement `bool Stack::empty() const` — return `true` when the stack has no elements.

**Think about:**
- `void fill(std::vector<int>& out, int value)` vs taking `const vector&` — which for input vs output?
- Why does `const Counter c; c.inc();` fail to compile?

---

### Day 3 — RAII  
**File:** `days/day03_raii.cpp`

1. Complete the `MutexGuard` pattern (lock in constructor, unlock in destructor). The demo `run_exercises()` expects a guard that protects a critical section.

**Think about:**
- What happens if an exception is thrown inside a constructor?
- Why is manual `delete` / `close()` in the middle of a function worse than RAII?

---

### Day 4 — Rule of three (awareness)  
**File:** `days/day04_rule_of_three.cpp`

1. Implement a **move-only** `Handle` that owns an `int` on the heap — either with deleted copies + move operations on a raw pointer, or by wrapping `std::unique_ptr<int>` internally (delete copy, allow move).

**Think about:**
- Build a **broken** `Handle` with a raw pointer and **no** copy constructor — observe double-free when you copy. Then fix by deleting copies.
- Why is a copyable raw owning pointer a design smell?

---

### Day 5 — `unique_ptr`  
**File:** `days/day05_unique_ptr.cpp`

1. Implement `void set_owner(std::unique_ptr<Dog> dog)` — take ownership of the dog; tests expect name `"Rex"` and an empty `unique_ptr` in the caller after `std::move`.

**Think about:**
- Why is `std::unique_ptr<FILE, decltype(&fclose)>` useful?
- Why is returning `unique_ptr` by `const&` wrong?

---

### Day 6 — Move semantics (part 1)  
**File:** `days/day06_move_part1.cpp`

1. Complete `Buffer take(Buffer b)` — return the buffer by value (move / NRVO).

**Think about:**
- After `std::string b = std::move(a);`, what is safe to do with `a`?
- `std::move(x)` does not move by itself — what does it actually do?

---

### Day 7 — Move semantics (part 2)  
**File:** `days/day07_move_part2.cpp`

1. Implement **`LogFile`** (optional but recommended):
   - Open a path in the constructor (`std::fstream` or similar).
   - `void write_line(const std::string& line)`.
   - **Move-only** — delete copy ctor/assignment; default or implement move.

**Think about:**
- How does `Connection` transfer a `unique_ptr<int>` in its constructor?

---

### Week 1 review (no single file)

- When should you pass by `const&`?
- What does `std::move` *not* do by itself?
- After `unique_ptr` is moved into a function, who owns the object?

---

## Week 2

### Day 8 — `shared_ptr`  
**File:** `days/day08_shared_ptr.cpp`

1. Create `std::shared_ptr<Foo>`, store the **same** instance twice in a `std::vector<std::shared_ptr<Foo>>`, clear the vector, and verify the object is still alive via the original `shared_ptr` (`use_count` checks).

**Think about:**
- Why is `Foo* raw = new Foo; shared_ptr p1(raw); shared_ptr p2(raw);` catastrophic?
- When is `shared_ptr` overkill vs `unique_ptr`?

---

### Day 9 — `weak_ptr`  
**File:** `days/day09_weak_ptr.cpp`

1. Wire `Node::next` as `shared_ptr` and `Node::prev` as **`weak_ptr`** so two nodes reference each other without a leak. Verify counts and `weak_ptr::expired()` after `reset()`.

**Think about:**
- Sketch `A <-> B` with two `shared_ptr` — why does refcount never hit zero?
- `weak_ptr::expired()` vs `lock()` — when to use which?

---

### Day 10 — `enable_shared_from_this`  
**File:** `days/day10_enable_shared_from_this.cpp`

1. Finish **`Worker::schedule`**: queue two `std::function<void()>` jobs that each increment `value`, capturing **`self`** via `shared_from_this()` safely.

**Think about:**
- What happens if you call `shared_from_this()` on a stack-allocated `Worker`?
- Why must `shared_from_this()` not be used in the constructor?

---

### Day 11 — Lambdas (part 1)  
**File:** `days/day11_lambdas_part1.cpp`

1. Run the provided checks for **reference capture** (`[&x]`) vs **copy capture** (`[x]`) — explain why `by_val(1)` still sees `x == 10` after `by_ref` changed `x` to 15.

**Stretch:**
- Implement `auto make_adder(int k)` without a lambda (hand-written struct with `operator()`).

---

### Day 12 — Lambdas (part 2)  
**File:** `days/day12_lambdas_part2.cpp`

1. Implement a **`mutable`** lambda: `[n](int x) mutable { return ++n + x; }` — verify `n` persists across calls (`11` then `12` for input `10`).

**Think about:**
- Why is `[this]` alone unsafe for work posted to a queue that runs later?
- What does `[buf = std::move(buf)]` achieve?

---

### Day 13 — `std::function`  
**File:** `days/day13_std_function.cpp`

1. Complete **`EventBus::publish`** — call every subscribed handler with the message (subscribe is provided).

**Stretch:**
- Sketch a type-erased handler that can hold **move-only** captures (C++14: virtual `IHandler` + `unique_ptr`; C++23: `std::move_only_function`).

---

### Day 14 — Deferred queue  
**File:** `days/day14_deferred_queue.cpp`

1. Run **`start_with_weak`**: destroy the `Session` (`shared_ptr::reset`) before `run_all()`. Ensure no crash and the weak handler does not resurrect the session.
2. **Extend:** add assertions or flags proving the weak handler no-ops when the session is gone.

**Think about:**
- Map `DeferredQueue::post` → async I/O “completion handler”.
- Map `shared_ptr` capture → keeping a connection alive until I/O finishes.

---

### Week 2 review (no single file)

- `shared_ptr` vs `unique_ptr` — when which?
- Why `weak_ptr`?
- Why capture `self` (or `weak_ptr`) in deferred lambdas?
