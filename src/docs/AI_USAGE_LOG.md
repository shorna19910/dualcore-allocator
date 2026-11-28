# AI Usage Log

**Project:** Custom Memory Allocator (`my_malloc` / `my_free`) in C
**Team:** Dual core (Shorna Nandi, Mashura Khatun Mashu)
**AI tools used:** Claude, ChatGPT

## How we used AI
- We used AI as a tutor and coding assistant, one small piece at a time.
- We typed and ran the code on our own machines (Ubuntu).
- We checked results against our own hand calculations.
- We did not hide AI use. Every AI-assisted file is listed below.

## Log

### src/allocator.c
- **AI tool:** Claude
- **What the AI did:** Wrote the code step by step: block header, `my_malloc`, `my_free`, `align8`, First-Fit, `split_block`, `coalesce`, Best-Fit, Worst-Fit, `write()`-based map, `dump_stats`.
- **What we did:** Typed and ran each step, compared the output with hand calculations, changed the map output to show "bytes", ran it on a second machine.

### tests/test_frag.c
- **AI tool:** Claude
- **What the AI did:** Wrote the demo for splitting and coalescing.
- **What we did:** Ran it and checked the sizes by hand (56 + 24 + 56 = 136).

### tests/test.c
- **AI tool:** Claude
- **What the AI did:** Suggested 10 tests with expected values.
- **What we did:** Typed them into the file and ran them (10 passed, 0 failed).

### Makefile
- **AI tool:** Claude
- **What the AI did:** Wrote it.
- **What we did:** Ran `make run`.

### README.md
- **AI tool:** Claude
- **What the AI did:** Drafted it.
- **What we did:** Reviewed and published it.

### Git and GitHub steps
- **AI tools:** Claude, ChatGPT
- **What the AI did:** Explained commands, branches and pull requests.
- **What we did:** Created the repository, made commits, merged a pull request, cloned it on a second machine.

### docs/CODE_EXPLANATIONS.md
- **AI tool:** none
- **What we did:** Mashura wrote explanations in her own words.

### Study guide (not in the repository)
- **AI tool:** Claude
- **What the AI did:** Wrote a long explanation document.
- **What we did:** Read it to prepare for the viva.

## Our checks
- All 10 tests pass on two machines.
- We traced the main example by hand: two free blocks of 56 bytes merge into 136, then a 100-byte request splits it into 104 and 8.

## Still in progress
- More explanations in `CODE_EXPLANATIONS.md` (written by us)
- Double-free detection (planned)
