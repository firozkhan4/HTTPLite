all: run


main: httplite.c
	gcc -o httplite httplite.c

run: main
	./httplite
