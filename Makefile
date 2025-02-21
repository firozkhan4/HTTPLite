.SILENT:

all: build

build:
	gcc -o bin/main.c example/main.c src/http.c

run:
	./bin/main.c
