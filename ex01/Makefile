# C-Compiler
CC = gcc
CFLAGS = -Wall
LIBS = -lm

myFloat : myFloat.o ex01.o
	$(CC) $(LIBS) -o $@ $^

checkFloat : checkFloat.o ex01.o
	$(CC) -o $@ $^

# Suffix rule
.SUFFIXES:.c .o
.c.o:
	$(CC) $(CFLAGS) -c $<

# target for removing files
.PHONY: clean
clean:
	rm *.o
