# Zyra - Syntactic Sugar for C++

Zyra is a toy compiler that provides some nice syntactic sugar over C++. It compiles into C++. Currently, the Zyra compiler just accepts Zyra code from `stdin` and outputs C++ code to `stdout`.

## Demonstration

Check out the [demo program](./demos/v0.0.1/sample.in.z) and it's [compiled C++ output](./demos/v0.0.1/sample.out.cpp), or check out the [side-by-side comparison](./demos/v0.0.1/diff.txt) to get an idea of the sorts of syntactic sugars supported by Zyra. 

## Getting Started - Building from Source

Currently, building from source is the only way to use Zyra. To build from source:

1. Ensure you have a Make and a C compiler installed, and edit the value of `CC` in the Makefile if you're using a compiler besides `gcc`.

2. Install [`flex`](https://github.com/westes/flex) and [`bison`](https://github.com/akimd/bison).

	- With `apt`
		```
		sudo apt install flex
		sudo apt install bison
		```

3. Run `make` from within the root directory of this repository.

You've now built the Zyra compiler from source. The executable file containing the Zyra compiler will be named `zc`. You can run `make clean-keepexe` to remove all the files generated during the compilation process besides the executable. You can also run `make clean` to remove all the files generated during the compilation process, including the executable.