CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
TARGET = mantis

# files
INCLUDE = -Iinclude
SRCS = $(wildcard src/*.c) $(wildcard ./lib/*.c)

# build
$(TARGET): $(SRCS) $(INCLUDE)
	@mkdir build/
	echo "Building file!"
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE) -o build/$(TARGET)
	echo "Done building!"

run:
	./build/mantis

clean:
	rm -rf ./build/
