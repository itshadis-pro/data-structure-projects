# CS 313 P1 Makefile
#   make           build measure and test_student
#   make run       build and run the measurement driver
#   make test      build and run your three tests against your stack.c
#   make check     build and run the autograder's tests on your stack.c
#   make valgrind  run measure under valgrind to check for leaks
#   make clean     remove built files

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

.PHONY: all run test check valgrind clean

all: measure test_student

measure: measure.c stack.c stack.h
	$(CC) $(CFLAGS) -o measure measure.c stack.c

test_student: test_student.c stack.c stack.h check.h
	$(CC) $(CFLAGS) -o test_student test_student.c stack.c

TESTS = create_destroy push_pop_lifo peek size empty_pop_peek growth_preserves copies_1 copies_2 copies_3 copies_5 copies_9 copies_1000 interleaved_boundaries interleaved_random large_1e6

test_stack: test_stack.c stack.c stack.h
	$(CC) $(CFLAGS) -o test_stack test_stack.c stack.c

check: test_stack
	@for t in $(TESTS); do printf '%-24s ' $$t; ./test_stack $$t >/dev/null 2>&1 && echo passed || echo FAILED; done

run: measure
	./measure

test: test_student
	./test_student

valgrind: measure
	valgrind --leak-check=full --error-exitcode=1 ./measure

clean:
	rm -rf measure test_student test_stack *.dSYM
