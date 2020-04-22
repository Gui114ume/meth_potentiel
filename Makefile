CC=gcc
CFLAGS=-g -Wall -O0
LDFLAGS=

all: meth_pot

meth_pot: potentiel.c
	$(CC) $< -o $@

clean:
	rm meth_pot
