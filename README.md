# revision-cpp-14-days

A **2-week, C++14** study track: references → RAII → `unique_ptr` → move → `shared_ptr` / `weak_ptr` → `enable_shared_from_this` → lambdas → `std::function` → a tiny deferred queue (preview of “run later” async style, **without** Asio).

Each day is one `.cpp` file with **runnable demos** and optional **exercises** (flip `RUN_EXERCISES` to `1` in that file).

## Requirements

- C++14 compiler (`g++`, `clang++`)
- Optional: CMake 3.10+

## Build & run

**Make (simplest):**

```bash
cd ~/programming/revision-cpp-14-days
make day01_references_const
./day01_references_const
make all    # build every day
```

**CMake:**

```bash
cmake -B build -S .
cmake --build build
./build/day01_references_const
```

## Curriculum

| Day | File | Topic |
|-----|------|--------|
| 1 | `days/day01_references_const.cpp` | References & `const` |
| 2 | `days/day02_const_pointers_members.cpp` | `const` pointers & member functions |
| 3 | `days/day03_raii.cpp` | RAII |
| 4 | `days/day04_rule_of_three.cpp` | Copy danger / deleted copies |
| 5 | `days/day05_unique_ptr.cpp` | `unique_ptr` |
| 6 | `days/day06_move_part1.cpp` | Move semantics (1) |
| 7 | `days/day07_move_part2.cpp` | Move-only types |
| 8 | `days/day08_shared_ptr.cpp` | `shared_ptr` / `make_shared` |
| 9 | `days/day09_weak_ptr.cpp` | `weak_ptr` & cycles |
| 10 | `days/day10_enable_shared_from_this.cpp` | `enable_shared_from_this` |
| 11 | `days/day11_lambdas_part1.cpp` | Lambdas (captures) |
| 12 | `days/day12_lambdas_part2.cpp` | `mutable`, move capture |
| 13 | `days/day13_std_function.cpp` | `std::function` |
| 14 | `days/day14_deferred_queue.cpp` | Deferred callbacks bridge |

Full day-by-day notes and goals: [docs/curriculum.md](docs/curriculum.md).

**All exercise questions:** [exercises/all-exercises.md](exercises/all-exercises.md) (or [exercises/](exercises/) per day).

Exercise reference implementations (spoilers): [solutions/](solutions/).

## echo-server

Separate practice project: [echo-server/](echo-server/) (POSIX + Asio echo servers). Related to the async / `shared_from_this` topics in the later days.

## How to study

1. Read the file header and `demo_*` / `main` flow.
2. Build and run — demos should print `dayNN OK`.
3. Set `#define RUN_EXERCISES 1`, implement `TODO`s, rebuild.
4. Compare with `solutions/` if stuck.

~45–60 minutes per weekday; review on weekends.

## Publish on GitHub

**Prerequisites:** `git` and [GitHub CLI](https://cli.github.com/) (`gh auth login` once).

```bash
cd ~/programming/revision-cpp-14-days
./scripts/publish-to-github.sh
```

Use `--private` instead of `--public` in the script if you prefer.

Manual steps (equivalent):

```bash
git init -b main
git add -A
git commit -m "Initial commit: 14-day modern C++14 exercise track"
gh repo create revision-cpp-14-days --public --source=. --remote=origin --push
```

Without `gh`:

```bash
git remote add origin git@github.com:YOUR_USER/revision-cpp-14-days.git
git push -u origin main
```

## License

MIT — see [LICENSE](LICENSE).
