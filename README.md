# COS214 Practical 5 — CampusGuard

CampusGuard is a C++11 emergency-response coordination application built around
Command, Mediator, Adapter, Facade, State, and Decorator.

## Repository layout

```text
include/campusguard/
  access/         Access-control Adapter participants
  command/        Commands, invoker, and command decorators
  coordination/   Mediator and colleague base classes
  facade/         High-level emergency facade
  incident/       Incident context and State participants
  response/       Response services and responder decorators
src/              Implementations matching the include layout
tests/            Focused pattern and integration tests
build/            Generated object/dependency files (ignored)
bin/              Generated application/test executables (ignored)
```

The folders are organised by domain responsibility instead of strictly by
design pattern because several classes participate in more than one pattern.

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
