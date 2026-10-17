/*
 * check.h -- tiny test framework for test_student.c. Do not edit.
 * The autograder uses its own copy.
 *
 *   CHECK(condition)          fails the test if condition is false.
 *   CHECK_COPIES(s, N)        fails the test unless stack_copies(s) == N.
 *                             N must be an integer literal you computed
 *                             by hand, such as 7 (not a variable or
 *                             an expression).
 *
 * A test passes if every check passes AND it contains at least one
 * CHECK_COPIES with N >= 1.
 *
 * Run all three tests:  ./test_student
 * Run one test:         ./test_student 2
 */
#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

static int check_count = 0;
static int check_failures = 0;
static int check_copies_nonzero = 0;

#define CHECK(cond)                                                     \
    do {                                                                \
        check_count++;                                                  \
        if (!(cond)) {                                                  \
            printf("    FAIL line %d: CHECK(%s)\n", __LINE__, #cond);   \
            check_failures++;                                           \
        }                                                               \
    } while (0)

#define CHECK_COPIES(s, expected) \
    check_copies_impl((s), (expected), #expected, __LINE__)

static inline void check_copies_impl(const Stack *s, long expected,
                                     const char *text, int line) {
    check_count++;
    for (const char *p = text; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p)) {
            printf("    FAIL line %d: CHECK_COPIES needs an integer literal"
                   " you computed by hand, not \"%s\"\n", line, text);
            check_failures++;
            return;
        }
    }
    if (s == NULL) {
        printf("    FAIL line %d: stack is NULL\n", line);
        check_failures++;
        return;
    }
    long actual = stack_copies(s);
    if (actual != expected) {
        printf("    FAIL line %d: you expected %ld copies, the stack"
               " reports %ld\n", line, expected, actual);
        check_failures++;
        return;
    }
    if (expected >= 1) {
        check_copies_nonzero++;
    }
}

void student_test_1(void);
void student_test_2(void);
void student_test_3(void);

int main(int argc, char **argv) {
    void (*tests[3])(void) = {student_test_1, student_test_2, student_test_3};
    int first = 1, last = 3, all_pass = 1;

    if (argc > 1) {
        first = last = atoi(argv[1]);
        if (first < 1 || first > 3) {
            printf("usage: %s [1|2|3]\n", argv[0]);
            return 2;
        }
    }
    for (int t = first; t <= last; t++) {
        check_count = check_failures = check_copies_nonzero = 0;
        printf("student_test_%d:\n", t);
        tests[t - 1]();
        int pass = check_failures == 0 && check_copies_nonzero >= 1;
        if (check_failures == 0 && check_copies_nonzero == 0) {
            printf("    FAIL: no CHECK_COPIES(s, N) with N >= 1 passed\n");
        }
        printf("    %s (%d checks)\n", pass ? "PASS" : "FAIL", check_count);
        fflush(stdout);
        all_pass = all_pass && pass;
    }
    return all_pass ? 0 : 1;
}

#endif
