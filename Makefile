all: main

main: bin/httplite

bin/httplite: httplite.c
	@mkdir -p bin
	gcc -o bin/httplite httplite.c

run: main
	bin/httplite

push:
	@if [ -z "$$(git status --porcelain)" ]; then \
		echo "No changes to commit."; \
	else \
		read -p "Commit message: " msg; \
		git add .; \
		git commit -m "$$msg"; \
		git push origin main; \
	fi

clean:
	rm -rf bin

