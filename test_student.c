/*
 * test_student.c -- CS 313 P1: your three hand-derived tests.
 *
 * Name: Hadi Almarzooq
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
    /* Hand-traced copy count for 5 pushes:
       Push 1: size 0 != cap 1  --> no growth. copies = 0, cap = 1
       Push 2: size 1 == cap 1  --> grow! copies += 1. Total copies = 1, cap = 2
       Push 3: size 2 == cap 2  --> grow! copies += 2. Total copies = 3, cap = 4
       Push 4: size 3 != cap 4  --> no growth. Total copies = 3, cap = 4
       Push 5: size 4 == cap 4  --> grow! copies += 4. Total copies = 7, cap = 8
    */
    Stack *s = stack_create();

    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_push(s, 40);
    stack_push(s, 50);

    CHECK_COPIES(s, 7);

    stack_destroy(s);

}  

void student_test_2(void){
    /* Hand-traced copy count with pops:
       Push 1: size 0 != cap 1  --> no growth. copies = 0, cap = 1
       Push 2: size 1 == cap 1  --> grow! copies += 1. Total copies = 1, cap = 2
       Pop:    size becomes 1. cap remains 2.
       Push 3: size 1 != cap 2  --> no growth. Total copies = 1, cap = 2
       Push 4: size 2 == cap 2  --> grow! copies += 2. Total copies = 3, cap = 4
    */
    
    Stack *s = stack_create();
    int popped_val;
    stack_push(s, 10);
    stack_push(s, 20);
    stack_pop(s, &popped_val);
    stack_push(s, 30);
    stack_push(s, 40);

    CHECK_COPIES(s, 3);

    stack_destroy(s);

}

void student_test_3(void) {
    /* Hand-traced copy count for 9 pushes:
       Push 1: size 0 != cap 1  --> no growth. copies = 0, cap = 1
       Push 2: size 1 == cap 1  --> grow! copies += 1. Total copies = 1, cap = 2
       Push 3: size 2 == cap 2  --> grow! copies += 2. Total copies = 3, cap = 4
       Push 4: size 3 != cap 4  --> no growth. Total copies = 3, cap = 4
       Push 5: size 4 == cap 4  --> grow! copies += 4. Total copies = 7, cap = 8
       Push 6-8: sizes 5,6,7 != cap 8 --> no growth. Total copies = 7, cap = 8
       Push 9: size 8 == cap 8  --> grow! copies += 8. Total copies = 15, cap = 16
    */
    Stack *s = stack_create();

    for (int i = 0; i < 9; i++) {
        stack_push(s, i);
    }

    CHECK_COPIES(s, 15);
    
    stack_destroy(s);
}