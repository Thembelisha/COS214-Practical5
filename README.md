# COS214 Practical 5 — CampusGuard

CampusGuard is a C++11 emergency-response coordination application built around
Command, Mediator, Adapter, Facade, State, and Decorator.

## Repository layout

```text
include/    All public header files
src/        All implementation files
tests/      Focused pattern and integration tests
build/      Generated object/dependency files (ignored)
bin/        Generated application/test executables (ignored)
```

The source and include trees are intentionally flat so every class is easy to
locate without navigating pattern-specific subdirectories.

## Developer commands

```bash
make check
make test
make
make run
make valgrind
make clean
```

`make check` and `make test` are available now. The application target will be
complete once the end-to-end `main.cpp` is integrated.


How to use the docker :
Build the docker image-docker build -t cpp-gdb .

Start the container interactively:

docker run -it cpp-gdb

The project files will be available inside the container at:

/app

Check the files with:

ls

Inside the Docker container, compile the project using the Makefile:

make test

To remove previous build files before compiling again:

make clean
make test

The project is compiled with debugging information using the -g compiler option.

Start GDB using:

gdb bin/tests/main

Inside GDB, set a breakpoint at a specific source-code line:

break tests/MainTest.cpp:181

Run the program:

run

exit the program:
exit 
For the final demonstration, the complete application must be built and launched through Docker Compose:

docker compose up --build
