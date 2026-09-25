CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS := -Iinclude

TARGET := bin/campusguard
SRC := $(wildcard src/*.cpp)
APP_SRC := Main.cpp
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC)) build/Main.o
DEP := $(OBJ:.o=.d)

TEST_SRC := tests/MainTest.cpp
TEST_BIN := bin/tests/main

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

build/Main.o: Main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

bin/tests/main: $(TEST_SRC) $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TEST_SRC) $(SRC) -o $@

check:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -fsyntax-only $(SRC)

test: $(TEST_BIN)
	@for test_binary in $(TEST_BIN); do \
		echo "Running $$test_binary"; \
		$$test_binary; \
	done

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

clean:
	$(RM) -r build bin

-include $(DEP)

.PHONY: all check test run valgrind clean
