/*
 * test_stack.c -- CS 313 P1 autograder tests.
 *
 * Usage: ./test_stack <test_name>
 * Runs one test. Exit code 0 = pass, nonzero = fail. Messages go to stdout.
 * The Python runner (run_tests.py) calls this once per test, so a crash
 * in one test cannot affect another.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define FAIL(...)                  \
    do {                           \
        printf(__VA_ARGS__);       \
        printf("\n");              \
        return 1;                  \
    } while (0)

#define REQUIRE(cond, ...)         \
    do {                           \
        if (!(cond)) FAIL(__VA_ARGS__); \
    } while (0)

/* Copies after n pushes onto a new stack: (smallest power of 2 >= n) - 1. */
static long expected_copies(long n) {
    long p = 1;
    while (p < n) p *= 2;
    return p - 1;
}

static long expected_capacity(long n) {
    long p = 1;
    while (p < n) p *= 2;
    return p;
}

static Stack *make(void) {
    Stack *s = stack_create();
    if (s == NULL) printf("stack_create returned NULL\n");
    return s;
}

/* Push 0..n-1, checking every push succeeds. */
static int push_range(Stack *s, int n) {
    for (int i = 0; i < n; i++) {
        REQUIRE(stack_push(s, i), "stack_push(s, %d) returned false", i);
    }
    return 0;
}

/* Pop everything, expecting n-1 down to 0. */
static int pop_range(Stack *s, int n) {
    for (int i = n - 1; i >= 0; i--) {
        int v = -12345;
        REQUIRE(stack_pop(s, &v), "stack_pop returned false with %d elements left", i + 1);
        REQUIRE(v == i, "after pushing 0..%d, pop #%d gave %d, expected %d",
                n - 1, n - i, v, i);
    }
    return 0;
}

/* ---------------- core tests ---------------- */

static int core_create_destroy(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    REQUIRE(s->data != NULL, "new stack has data == NULL");
    REQUIRE(s->size == 0, "new stack has size %d, expected 0", s->size);
    REQUIRE(s->capacity == 1, "new stack has capacity %d, expected 1", s->capacity);
    REQUIRE(s->copies == 0, "new stack has copies %ld, expected 0", s->copies);
    stack_destroy(s);
    stack_destroy(NULL);
    return 0;
}

static int core_push_pop_lifo(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int vals[] = {5, -3, 42, 0, 7};
    for (int i = 0; i < 5; i++) {
        REQUIRE(stack_push(s, vals[i]), "stack_push(s, %d) returned false", vals[i]);
    }
    for (int i = 4; i >= 0; i--) {
        int v = -12345;
        REQUIRE(stack_pop(s, &v), "stack_pop returned false on a nonempty stack");
        REQUIRE(v == vals[i], "pushed 5, -3, 42, 0, 7; pop #%d gave %d, expected %d",
                5 - i, v, vals[i]);
    }
    stack_destroy(s);
    return 0;
}

static int core_peek(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int v = 0;
    stack_push(s, 10);
    REQUIRE(stack_peek(s, &v) && v == 10, "after push 10, peek gave %d, expected 10", v);
    stack_push(s, 20);
    stack_push(s, 30);
    REQUIRE(stack_peek(s, &v) && v == 30, "after push 10, 20, 30, peek gave %d, expected 30", v);
    REQUIRE(stack_peek(s, &v) && v == 30, "a second peek gave %d, expected 30 (peek must not remove)", v);
    REQUIRE(stack_size(s) == 3, "peek changed the size to %d, expected 3", stack_size(s));
    stack_pop(s, &v);
    REQUIRE(stack_peek(s, &v) && v == 20, "after one pop, peek gave %d, expected 20", v);
    stack_destroy(s);
    return 0;
}

static int core_size(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int v;
    REQUIRE(stack_size(s) == 0, "new stack: size %d, expected 0", stack_size(s));
    REQUIRE(stack_is_empty(s), "new stack: stack_is_empty returned false");
    for (int i = 1; i <= 6; i++) {
        stack_push(s, i);
        REQUIRE(stack_size(s) == i, "after %d pushes: size %d", i, stack_size(s));
        REQUIRE(!stack_is_empty(s), "after %d pushes: stack_is_empty returned true", i);
    }
    for (int i = 5; i >= 0; i--) {
        stack_pop(s, &v);
        REQUIRE(stack_size(s) == i, "after a pop: size %d, expected %d", stack_size(s), i);
    }
    REQUIRE(stack_is_empty(s), "after popping everything: stack_is_empty returned false");
    stack_destroy(s);
    return 0;
}

static int core_empty_pop_peek(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int v = 777;
    REQUIRE(!stack_pop(s, &v), "stack_pop on a new empty stack returned true");
    REQUIRE(v == 777, "stack_pop on an empty stack changed *out to %d", v);
    REQUIRE(!stack_peek(s, &v), "stack_peek on a new empty stack returned true");
    REQUIRE(v == 777, "stack_peek on an empty stack changed *out to %d", v);
    REQUIRE(stack_size(s) == 0, "size is %d after failed pop/peek, expected 0", stack_size(s));
    stack_push(s, 1);
    stack_push(s, 2);
    stack_pop(s, &v);
    stack_pop(s, &v);
    v = 777;
    REQUIRE(!stack_pop(s, &v), "stack_pop returned true after the stack was emptied");
    REQUIRE(!stack_peek(s, &v), "stack_peek returned true after the stack was emptied");
    REQUIRE(v == 777, "pop/peek on an emptied stack changed *out to %d", v);
    REQUIRE(stack_size(s) == 0, "size is %d after failed pop, expected 0", stack_size(s));
    REQUIRE(stack_push(s, 3), "push after failed pops returned false");
    REQUIRE(stack_pop(s, &v) && v == 3, "push 3 after failed pops, then pop gave %d", v);
    stack_destroy(s);
    return 0;
}

static int core_growth_preserves(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int n = 100;   /* grows 1 -> 2 -> 4 -> ... -> 128: seven doublings */
    for (int i = 0; i < n; i++) {
        REQUIRE(stack_push(s, i), "stack_push(s, %d) returned false", i);
        long cap = expected_capacity(i + 1);
        REQUIRE(s->capacity == cap, "after %d pushes: capacity %d, expected %ld",
                i + 1, s->capacity, cap);
        for (int j = 0; j <= i; j++) {
            REQUIRE(s->data[j] == j, "after %d pushes: data[%d] = %d, expected %d",
                    i + 1, j, s->data[j], j);
        }
    }
    if (pop_range(s, n)) return 1;
    stack_destroy(s);
    return 0;
}

/* ---------------- additional tests ---------------- */

static int copies_after(int n) {
    Stack *s = make();
    if (s == NULL) return 1;
    if (push_range(s, n)) return 1;
    long want = expected_copies(n);
    REQUIRE(stack_copies(s) == want, "after %d pushes: stack_copies = %ld, expected %ld",
            n, stack_copies(s), want);
    REQUIRE(s->copies == want, "after %d pushes: s->copies = %ld, expected %ld",
            n, s->copies, want);
    stack_destroy(s);
    return 0;
}

static int interleaved_boundaries(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int v;
    /* push 1..4: capacity 4, copies 1 + 2 = 3 */
    for (int i = 1; i <= 4; i++) stack_push(s, i);
    REQUIRE(stack_copies(s) == 3, "after 4 pushes: copies %ld, expected 3", stack_copies(s));
    stack_pop(s, &v);                      /* size 3 */
    REQUIRE(v == 4, "pop gave %d, expected 4", v);
    stack_push(s, 5);                      /* size 4, no growth */
    REQUIRE(stack_copies(s) == 3, "push into a free slot: copies %ld, expected 3", stack_copies(s));
    REQUIRE(s->capacity == 4, "capacity %d, expected 4", s->capacity);
    stack_push(s, 6);                      /* grow 4 -> 8: copies 3 + 4 = 7 */
    REQUIRE(stack_copies(s) == 7, "after growth to 8: copies %ld, expected 7", stack_copies(s));
    REQUIRE(s->capacity == 8, "capacity %d, expected 8", s->capacity);
    int want[] = {6, 5, 3, 2, 1};
    for (int i = 0; i < 5; i++) {
        REQUIRE(stack_pop(s, &v) && v == want[i], "pop #%d gave %d, expected %d", i + 1, v, want[i]);
    }
    REQUIRE(!stack_pop(s, &v), "pop on emptied stack returned true");
    /* capacity never shrinks: 8 more pushes fit without copies */
    for (int i = 0; i < 8; i++) stack_push(s, i);
    REQUIRE(stack_copies(s) == 7, "refilling to capacity 8: copies %ld, expected 7", stack_copies(s));
    stack_destroy(s);
    return 0;
}

static int interleaved_random(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int model[20000];
    int msize = 0, maxsize = 0;
    unsigned int seed = 313;
    for (int step = 0; step < 20000; step++) {
        seed = seed * 1103515245u + 12345u;
        int r = (seed >> 16) % 10;
        if (r < 6 || msize == 0) {         /* push, 60 percent */
            int x = (int)(seed % 100000);
            REQUIRE(stack_push(s, x), "step %d: push returned false", step);
            model[msize++] = x;
            if (msize > maxsize) maxsize = msize;
        } else {
            int v = -1;
            REQUIRE(stack_pop(s, &v), "step %d: pop returned false with size %d", step, msize);
            msize--;
            REQUIRE(v == model[msize], "step %d: pop gave %d, expected %d", step, v, model[msize]);
        }
        REQUIRE(stack_size(s) == msize, "step %d: size %d, expected %d", step, stack_size(s), msize);
    }
    long want = expected_copies(maxsize);
    REQUIRE(stack_copies(s) == want, "max size reached %d: copies %ld, expected %ld",
            maxsize, stack_copies(s), want);
    stack_destroy(s);
    return 0;
}

static int large_1e6(void) {
    Stack *s = make();
    if (s == NULL) return 1;
    int n = 1000000;
    if (push_range(s, n)) return 1;
    REQUIRE(stack_copies(s) == 1048575, "after 10^6 pushes: copies %ld, expected 1048575",
            stack_copies(s));
    REQUIRE(s->capacity == 1048576, "after 10^6 pushes: capacity %d, expected 1048576",
            s->capacity);
    if (pop_range(s, n)) return 1;
    stack_destroy(s);
    return 0;
}

/* ---------------- dispatch ---------------- */

static int copies_1(void) { return copies_after(1); }
static int copies_2(void) { return copies_after(2); }
static int copies_3(void) { return copies_after(3); }
static int copies_5(void) { return copies_after(5); }
static int copies_9(void) { return copies_after(9); }
static int copies_1000(void) { return copies_after(1000); }

struct test { const char *name; int (*fn)(void); };

static const struct test TESTS[] = {
    {"create_destroy", core_create_destroy},
    {"push_pop_lifo", core_push_pop_lifo},
    {"peek", core_peek},
    {"size", core_size},
    {"empty_pop_peek", core_empty_pop_peek},
    {"growth_preserves", core_growth_preserves},
    {"copies_1", copies_1},
    {"copies_2", copies_2},
    {"copies_3", copies_3},
    {"copies_5", copies_5},
    {"copies_9", copies_9},
    {"copies_1000", copies_1000},
    {"interleaved_boundaries", interleaved_boundaries},
    {"interleaved_random", interleaved_random},
    {"large_1e6", large_1e6},
};

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    if (argc != 2) {
        fprintf(stderr, "usage: %s <test_name>\n", argv[0]);
        return 2;
    }
    for (size_t i = 0; i < sizeof TESTS / sizeof TESTS[0]; i++) {
        if (strcmp(argv[1], TESTS[i].name) == 0) {
            int rc = TESTS[i].fn();
            if (rc == 0) printf("passed\n");
            return rc;
        }
    }
    fprintf(stderr, "unknown test %s\n", argv[1]);
    return 2;
}
