/*
 * test_student.c -- CS 313 P1: your three hand-derived tests.
 *
 * Name:
 *
 * Write three tests. Each one pushes (and maybe pops) some values, then
 * checks the copy count with CHECK_COPIES(s, N), where N is a number
 * YOU worked out by hand before running anything. Show your work in a
 * comment above the check. You may add CHECK(...) lines for anything else.
 *
 * The autograder runs your tests against the instructor's stack. A test
 * passes if all its checks pass there and it has at least one
 * CHECK_COPIES with N >= 1. So a wrong hand count fails the test.
 *
 * Suggested tests:
 *   1. Push a small number of values (at least 4) and trace every growth.
 *   2. Push a number of values just past a power of 2, such as 17 or 33.
 *   3. Mix pushes and pops so that the stack grows, shrinks in size (the
 *      capacity never shrinks), and grows again.
 *
 * Worked example (not one of your three):
 *
 *   Stack *s = stack_create();
 *   stack_push(s, 10);     // capacity 1, size 1, no growth
 *   stack_push(s, 20);     // full: grow 1 -> 2, copy 1 element
 *   CHECK_COPIES(s, 1);
 *   stack_destroy(s);
 *
 * Build and run against your own stack.c:  make test
 */
#include "check.h"

void student_test_1(void) {
    Stack *s = stack_create();
    /* TODO */
    stack_destroy(s);
}

void student_test_2(void) {
    Stack *s = stack_create();
    /* TODO */
    stack_destroy(s);
}

void student_test_3(void) {
    Stack *s = stack_create();
    /* TODO */
    stack_destroy(s);
}
