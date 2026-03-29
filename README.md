
![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=black)

## Mantis: CLI edition
This program is a CLI version of the Mantis card game with a small twist - cards are assigned an additional property which is a value in points. Instead of cards being 1 point each, they all vary in points!

---
## How to play

---
## Usage
There are two ways to compile. Either with the makefile or through `gcc` directly. To start, clone the directory.

```sh
git clone https://github.com/rea-prince/mantis.git
```

### Makefile
1. Open the directory in your terminal.
2. Run `make` to compile, or `make run` to compile and run!

```sh
make
# or
make run
```

3. ... and you're done!



### `gcc`
1. Open the directory in your terminal.
2. Run the following commands:

On Windows:
```sh
gcc -Wall -std=c99 -Iinclude src\*.c -o build\mantis
```

On Linux/MacOS
```sh
gcc -Wall -std=c99 -Iinclude src/*.c -o build/mantis
```

3. Enter the build directory and run the program.

```sh
cd build
./mantis # .\mantis.exe on Windows
```
