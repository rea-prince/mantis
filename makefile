CFLAGS = -Wall -std=c99 -Iinclude
PROJECT_NAME = mantis

# files
INCLUDE = -Iinclude
SRCS = $(wildcard src/*.c) $(wildcard ./lib/*.c)

# build/link
$(PROJECT_NAME): $(SRCS) $(INCLUDE)
	echo "Building file!"
	gcc $(CFLAGS) $^ -o build/$@
	echo "Done building!"

clean:
	rm -rf ./build/$(PROJECT_NAME)

run: ./build/$(PROJECT_NAME)
	./build/mantis
