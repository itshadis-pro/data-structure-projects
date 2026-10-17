/*
 * stack.c -- CS 313 P1: a growable int stack.
 *
 * Name: Hadi Almarzooq
 *
 * Fill in every TODO. The rules are in stack.h and README.md.
 * This skeleton compiles, but it fails the tests until you finish it.
 */
#include <stdlib.h>
#include "stack.h"

Stack *stack_create(void) {
    /* TODO: malloc a Stack, then malloc its data array with room for
     - 1 int. Set size 0, capacity 1, copies 0. Return NULL if either
     - malloc fails (free anything you already allocated).
     - Comments added by gemini */
    
    // 1. Allocate memory on the heap for the Stack struct itself.
    Stack *s = malloc(sizeof(Stack));

    // 2. If malloc fails (e.g., system is out of memory), it returns NULL. We catch this immediately.
    if (s == NULL){
        return NULL;
    }

    // 3. Allocate memory for the actual array that will hold the stack's integers.
    // We start with a capacity of 1, so we need space for 1 integer.
    s->data = malloc(1 * sizeof(int));

    // 4. If the array allocation fails, we must clean up the struct we successfully 
    // allocated in step 1 before bailing out. Otherwise, that struct memory is lost forever (a leak).
    if (s->data == NULL){
        free(s);
        return NULL;
    }

    // 5. Initialize the tracking variables for a brand new, empty stack.
    s->capacity = 1; // The array has room for exactly 1 item right now
    s->size = 0;     // There are currently 0 items actually pushed onto the stack
    s->copies = 0;   // We haven't had to grow the array and copy items yet

    // 6. Return the pointer to our fully constructed stack.
    return s;
}

void stack_destroy(Stack *s) {
    /* TODO: if s is not NULL, free the data array, then free s. */

    if (s != NULL) {

    free(s->data);
    free(s);

    }
}

bool stack_push(Stack *s, int x) {
    /* TODO: if the stack is full (size == capacity), grow it:
     *   1. malloc a new array of 2 * capacity ints
     *   2. copy the size elements over with a for loop (no realloc!)
     *   3. free the old array and point data at the new one
     *   4. add the OLD capacity to copies, then double capacity
     * Then store x at data[size] and increase size.
     * Return false only if malloc fails. */
    if (s == NULL){
        return false;
    }
    
    if (s->size == s->capacity){

        int *new_data = malloc(2 * s->capacity * sizeof(int));

        if (new_data == NULL){
            return false;
        }
    
    for (int i = 0; i < s->size; i++){
        new_data[i] = s->data[i];
    }
    
    free(s->data);
    s->data = new_data;

    s->copies = s->copies + s->capacity;
    s->capacity = s->capacity * 2;
    }


    return false;
}

bool stack_pop(Stack *s, int *out) {
    /* TODO: if empty, return false without touching *out.
     * Otherwise store the top element in *out, remove it, return true. */
    (void)s;
    (void)out;
    return false;
}

bool stack_peek(const Stack *s, int *out) {
    /* TODO: like stack_pop, but leave the element on the stack. */
    (void)s;
    (void)out;
    return false;
}

int stack_size(const Stack *s) {
    /* TODO */
    (void)s;
    return -1;
}

bool stack_is_empty(const Stack *s) {
    /* TODO */
    (void)s;
    return false;
}

long stack_copies(const Stack *s) {
    /* TODO */
    (void)s;
    return -1;
}
