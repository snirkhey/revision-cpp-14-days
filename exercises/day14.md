# Day 14 — Deferred queue

**Implement in:** `days/day14_deferred_queue.cpp`

1. `start_with_weak` — destroy session before `run_all()`; no crash, weak handler no-ops.
2. Add checks that prove the handler did not run on a dead session.

See [all-exercises.md](all-exercises.md#day-14--deferred-queue).
