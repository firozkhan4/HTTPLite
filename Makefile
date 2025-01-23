# Ensure all steps are well-organized
all: main

# Compile the main program
main: bin/httplite

bin/httplite: httplite.c
	@mkdir -p bin
	gcc -o bin/httplite httplite.c

# Run the compiled binary
run: main
	bin/httplite

# Push changes to Git
push:
	@if [ -z "$$(git status --porcelain)" ]; then \
		echo "No changes to commit."; \
	else \
		read -p "Commit message: " msg; \
		git add .; \
		git commit -m "$$msg"; \
		git push origin main; \
	fi

# Clean up build artifacts
clean:
	rm -rf bin

