# P1: Make the 212 stack grow

CS 313, Fall 2026. Introduced in lab Tue 10/6.

- **First step, in lab Tue 10/6:** fill in `stack_create` and `stack_destroy`, submit `stack.c` to Gradescope, and check that the `create_destroy` test passes. This makes sure your setup and submission work well before the deadline.
- **Due:** Fri 10/16, 11:59pm. Free extension to Sat 10/17, 11:59pm.
- **Language:** C. You may use AI tools as a tutor when you get stuck, but you need to understand your code: you will explain it in `REPORT.md`, and exams include questions about code like this.
- **Set up first:** follow `SETUP.md`. You do this once, and it covers all four programming assignments. Everything below assumes that setup.
- **New to C, or took 212 in another language?** Read `C_REFRESHER.md` and come to office hours.

## The idea

In CS 212 your stack used a fixed array: `int data[CAPACITY]` with `#define CAPACITY 100`. When it filled up, push failed. In P1 the stack grows instead.

A new stack has capacity 1. When you push onto a full stack (size == capacity), you:

1. `malloc` a **new** array of 2 × capacity ints,
2. copy every element into it with a `for` loop you write,
3. `free` the old array and point `data` at the new one,
4. add the **old** capacity to `copies`, then double `capacity`.

Then you write the new element. Do **not** use `realloc`. It may grow the block in place and hide the copies. The point of P1 is to count them.

## Files

| File | What to do |
|---|---|
| `stack.h` | The API and the rules. Read it. Do not edit it. |
| `stack.c` | Fill in every TODO. **Submit.** |
| `test_stack.c` | The autograder's own tests; run them with `make check`. |
| `test_student.c` | Write three tests (below). **Submit.** |
| `REPORT.md` | Fill in the blanks. **Submit.** |
| `measure.c` | Measurement driver. Do not edit. |
| `check.h` | Tiny test framework for `test_student.c`. Do not edit. |
| `SETUP.md` | How to set up gcc, make, and valgrind. Read it first. |
| `.devcontainer/` | Lets GitHub Codespaces set up everything for you (Option C in `SETUP.md`). |
| `Makefile` | `make`, `make run`, `make test`, `make check` (runs the autograder's tests on your stack.c), `make valgrind`, `make clean` |

## The API

The `Stack` struct has fields `data`, `size`, `capacity`, and `copies`. The functions are `stack_create`, `stack_destroy`, `stack_push`, `stack_pop`, `stack_peek`, `stack_size`, `stack_is_empty`, and `stack_copies`. See `stack.h` for each one.

**Empty-stack rule.** `stack_pop` and `stack_peek` return a `bool`. The value comes back through the pointer `out`. On an empty stack they return `false` and leave `*out` unchanged. They never print, exit, or crash. Example:

```c
int top;
if (stack_pop(s, &top)) {
    printf("popped %d\n", top);
} else {
    printf("stack was empty\n");
}
```

## Your three tests

In `test_student.c`, write three tests. Each one pushes (and maybe pops), then checks the copy count with `CHECK_COPIES(s, N)`. Work out `N` **by hand** first, and show the work in a comment. `N` must be a plain number such as `15`.

The autograder runs your tests against the instructor's stack. A test passes if all its checks pass there. So a wrong hand count fails. Run `make test` to try them on your own stack.

## The measurement

Run `make run`. It pushes n = 1000, 10000, and 100000 elements and prints copies, pushes, and copies / pushes. Put the three ratios in `REPORT.md`. Then write one or two sentences on why the ratio stays below 2.

## Grading

P1 is worth 10 points, the same as each of the other programming assignments.

- **8 points from the autograder.** The points are split evenly across all the tests, and each passing test earns its share. The tests check the basic operations, exact copy counts, 10^6 pushes with no memory leaks (under `valgrind`), mixed pushes and pops, that you did not use `realloc`, your three hand-traced tests, and that `REPORT.md` is filled in. Gradescope shows every test and its message, and you may resubmit as often as you like.
- **2 points graded by the course staff:** readable code (clear names, consistent indentation, comments where the logic is not obvious, no leftover debugging output), and a correct explanation in `REPORT.md` of why copies per push stays below 2.

Working code is expected: if you are stuck, office hours, the Canvas discussion, and AI tools can all help you get there.

The autograder also runs your code with AddressSanitizer. If a test says `heap-buffer-overflow`, you read or wrote past the end of an array. The lines below it name the function and line number.

## Tips

- Compile with `gcc -Wall -g`; the Makefile does this. Fix every warning.
- Draw the array before and after one growth. Check the loop bounds on paper.
- Run `make valgrind` before you submit. You want "All heap blocks were freed" and "ERROR SUMMARY: 0 errors". (valgrind does not run on recent Macs; see `SETUP.md`. The autograder checks for leaks either way.)
