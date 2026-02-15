CFLAGS = -Wall -std=c99
PROJECT_NAME = mantis

# files
INCLUDE = -Iinclude
SRCS = $(wildcard src/*.c)

# build
$(PROJECT_NAME): $(SRCS)
	@echo "Compiling binaries! ouo"
	gcc $(CFLAGS) $(INCLUDE) $^ -o build/$@
	@echo "Done building! ^-^"

clean:
	rm -rf ./build/$(PROJECT_NAME)

run: ./build/$(PROJECT_NAME)
	./build/mantis
