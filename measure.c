/*
 * measure.c -- CS 313 P1 measurement driver. Do not edit.
 *
 * For n = 10^3, 10^4, 10^5, push n elements onto a new stack and print
 * the number of element copies, the number of pushes, and their ratio.
 * Copy the three ratios into REPORT.md.
 */
#include <stdio.h>
#include "stack.h"

int main(void) {
    int ns[] = {1000, 10000, 100000};

    printf("%10s %10s %14s\n", "pushes", "copies", "copies/pushes");
    for (int k = 0; k < 3; k++) {
        int n = ns[k];
        Stack *s = stack_create();
        if (s == NULL) {
            printf("stack_create returned NULL\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            if (!stack_push(s, i)) {
                printf("stack_push failed at i = %d\n", i);
                stack_destroy(s);
                return 1;
            }
        }
        long copies = stack_copies(s);
        printf("%10d %10ld %14.3f\n", n, copies, (double)copies / n);
        stack_destroy(s);
    }
    return 0;
}
