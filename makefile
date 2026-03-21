CFLAGS = -Wall -std=c99
PROJECT_NAME = mantis

# files
INCLUDE = -Iinclude
SRCS = $(wildcard src/*.c)

# build
$(PROJECT_NAME): $(SRCS)
	@printf '\nCompiling binaries! o3o\n\n'
	gcc $(CFLAGS) $(INCLUDE) $^ -o build/$@
	@printf '\nDone building! ^-^\n'

clean:
	rm -rf ./build/$(PROJECT_NAME)

run: $(PROJECT_NAME)
	@cd build && printf '\nPROGRAM STARTING!! \n==================\n\n' && ./$(PROJECT_NAME)
