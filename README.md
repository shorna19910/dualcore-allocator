# dualcore-allocator

A custom memory allocator in C: our own `my_malloc` and `my_free`, built on top of `sbrk()`.
OS Lab Project, Team Dual core.

## Features
- Gets memory from the OS with `sbrk()`
- Every block has a 24-byte header (size, free flag, next pointer) and blocks are kept in a linked list
- Three allocation strategies, chosen with `set_strategy()`: First-Fit, Best-Fit, Worst-Fit
- Splits big free blocks and merges neighbouring free blocks (coalescing)
- 8-byte alignment; `my_malloc(0)` returns `NULL`
- Memory map and fragmentation statistics printed with `write()` (no `printf` inside the allocator)

## Requirements
Linux (Ubuntu or WSL2) with `gcc`, `make` and `git`:
```
sudo apt install build-essential git
```

## Build and run
```
git clone https://github.com/shorna19910/dualcore-allocator
cd dualcore-allocator
make run
```
`make run` builds and runs the demo (`tests/test_frag.c`).

## Run the tests
```
gcc -Wall -Wextra tests/test.c -o test.out
./test.out
```
Expected last line: `10 passed, 0 failed`

## Sample output
```
--- Memory map ---
Block 0: addr=0x55fdda221000 size=136 bytes FREE
Block 1: addr=0x55fdda2210a0 size=56 bytes USED

Now asking for 100 bytes:
--- Memory map ---
Block 0: addr=0x55fdda221000 size=104 bytes USED
Block 1: addr=0x55fdda221080 size=8 bytes FREE
Block 2: addr=0x55fdda2210a0 size=56 bytes USED
```
(Addresses are different on every run.)

## Project structure
```
dualcore-allocator/
├── src/allocator.c        # the allocator
├── tests/test_frag.c      # demo: split and coalesce
├── tests/test.c           # 10 automatic tests
├── docs/                  # explanations and logs
├── Makefile
├── LICENSE
└── README.md
```

## Known limitations
- Not thread-safe
- Double-free and memory-leak detection are not implemented yet
- Freed memory is reused by the allocator but is not returned to the OS

## Documents
- [Code explanations](docs/CODE_EXPLANATIONS.md)
- [AI usage log](docs/AI_USAGE_LOG.md)

## Team
- Shorna Nandi (242-115-202), GitHub: shorna19910
- Mashura Khatun Mashu (242-115-237), GitHub: mashura112
