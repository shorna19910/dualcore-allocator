# dualcore-allocator

A custom memory allocator in C: `my_malloc` and `my_free` built on top of `sbrk()`.
OS Lab Project, Team Dual core.

## What it does
- Gets memory from the OS with `sbrk()`
- Every block has a 24-byte header (size, free flag, next pointer)
- First-Fit, Best-Fit and Worst-Fit, chosen with `set_strategy()`
- Splits big free blocks and merges neighbouring free blocks (coalescing)
- 8-byte alignment; `my_malloc(0)` returns NULL
- Memory map and fragmentation statistics are printed with `write()`

## Files
- `src/allocator.c`: the allocator
- `tests/test_frag.c`: demo of splitting and coalescing
- `tests/test.c`: 10 automatic tests
- `docs/`: explanations

## Build and run (Linux, needs gcc)
```
gcc -Wall -Wextra tests/test_frag.c -o test_frag.out
./test_frag.out
gcc -Wall -Wextra tests/test.c -o test.out
./test.out
```
Expected result of the tests: `10 passed, 0 failed`.

## Team
- Shorna Nandi
- Mashura Khatun Mashu

## Planned
- Double-free and leak detection
