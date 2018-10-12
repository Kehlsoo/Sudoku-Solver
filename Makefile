CC = clang++
CFLAGS = -std=c++11
INCLUDE_DIRS = -I./include
TARGET_SOURCES = ./src/sudoku.cpp
TEST_SOURCES = ./src/sudoku_test.cpp ./src/sudoku.cpp
EXECUTABLE = sudoku
TEST_EXECUTABLE = test_sudoku

.PHONY: all target tests

all: target tests

target: $(EXECUTABLE)

tests: $(TEST_EXECUTABLE)

$(EXECUTABLE): 
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(TARGET_SOURCES) -o $(EXECUTABLE)

$(TEST_EXECUTABLE): 
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -D CATCH_TEST $(TEST_SOURCES) -o $(TEST_EXECUTABLE)

clean:
	rm $(EXECUTABLE) $(TEST_EXECUTABLE)
