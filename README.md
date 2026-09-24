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
