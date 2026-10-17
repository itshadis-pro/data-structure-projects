# C refresher for P1

This page covers the C you need for P1. It assumes you know Java or Python.

## Structs and typedef

A struct groups fields. `typedef` gives the type a short name.

```c
typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;
```

## Pointers

A pointer holds an address. `&x` is the address of `x`. `*p` is the value at `p`.

```c
int x = 5;
int *p = &x;   /* p points to x */
*p = 7;        /* now x == 7 */
```

A function can return a second value through a pointer argument. This is how `stack_pop` works:

```c
bool get_first(int *out) {
    *out = 42;     /* write into the caller's variable */
    return true;
}

int v;
if (get_first(&v)) { /* v is now 42 */ }
```

## malloc and free

`malloc(n)` returns `n` bytes from the heap, or `NULL` if it fails. Use `sizeof` to get sizes. Every `malloc` needs exactly one matching `free`. Never use memory after you free it.

```c
#include <stdlib.h>

int *a = malloc(10 * sizeof(int));   /* array of 10 ints */
if (a == NULL) { /* out of memory */ }
a[0] = 3;
free(a);
a = NULL;                            /* optional, avoids reuse */
```

## Pointers to structs

Allocate a struct on the heap and use `->` to reach its fields. `s->size` means `(*s).size`.

```c
Stack *s = malloc(sizeof(Stack));
s->data = malloc(1 * sizeof(int));
s->size = 0;
s->capacity = 1;
/* ... later, free the inside first, then the struct: */
free(s->data);
free(s);
```

## Copying an array

C has no array assignment. Copy element by element:

```c
for (int i = 0; i < n; i++) {
    new_data[i] = old_data[i];
}
```

## Compiling

```
gcc -std=c11 -Wall -g -o measure measure.c stack.c
./measure
```

- `-Wall` turns on warnings. Treat every warning as a bug.
- `-g` adds debug info, so valgrind and gdb show line numbers.
- In P1, `make` runs these commands for you.

## valgrind

valgrind runs your program and reports memory errors and leaks.

```
valgrind --leak-check=full ./measure
```

A clean run ends with "All heap blocks were freed -- no leaks are possible" and "ERROR SUMMARY: 0 errors". "Invalid write" or "Invalid read" means you went past the end of an array or used freed memory. "definitely lost" means a missing `free`.

valgrind runs on Linux (ix-dev and the Gradescope autograder). On a Mac, use ix-dev, or compile with `-fsanitize=address` to get similar error reports.
