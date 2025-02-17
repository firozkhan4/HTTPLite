.SILENT:

all: run

SRC=.
BIN=bin/

http: main.c
	gcc main.c -o bin/main

run: http
	bin/main
