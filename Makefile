# Makefile for JavaScript Parser
# 使用 re2c 和 bison 构建 JavaScript 语法分析器

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
RE2C = re2c
BISON = bison
BISON_FLAGS = -d -y

TARGET = js-parser

LEXER_SRC = lexer.re
PARSER_SRC = parser.y
MAIN_SRC = main.c
AST_SRC = ast.c

LEXER_C = lexer.c
PARSER_C = parser.c
PARSER_H = parser.h

OBJS = $(LEXER_C:.c=.o) $(PARSER_C:.c=.o) $(AST_SRC:.c=.o) $(MAIN_SRC:.c=.o)

TEST_DIR = test
TEST_FILES = $(wildcard $(TEST_DIR)/*.js)
NEGATIVE_TESTS = $(wildcard $(TEST_DIR)/error*.js)
POSITIVE_TESTS = $(filter-out $(NEGATIVE_TESTS),$(TEST_FILES))

.PHONY: all clean test help

all: $(TARGET)

$(LEXER_C): $(LEXER_SRC) $(PARSER_H)
	@echo "Generating lexer..."
	$(RE2C) -o $(LEXER_C) $(LEXER_SRC)

$(PARSER_C) $(PARSER_H): $(PARSER_SRC)
	@echo "Generating parser..."
	$(BISON) $(BISON_FLAGS) -o $(PARSER_C) $(PARSER_SRC)
	@if [ -f y.tab.h ]; then mv y.tab.h $(PARSER_H); fi

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

lexer.o: parser.h lexer.h
parser.o: ast.h parser_api.h lexer.h
main.o: ast.h parser_api.h lexer.h parser.h
ast.o: ast.h lexer.h parser.h

$(TARGET): $(LEXER_C) $(PARSER_C) $(PARSER_H) $(OBJS)
	@echo "Linking executable..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	@echo "Build complete."

test: $(TARGET)
	@echo "=========================================="
	@echo "Running tests..."
	@echo "=========================================="
	@status=0; \
	for test_file in $(POSITIVE_TESTS); do \
		echo ""; \
		echo "Test file: $$test_file"; \
		echo "----------------------------------------"; \
		if ./$(TARGET) $$test_file; then \
			echo "PASS $$test_file"; \
		else \
			echo "FAIL $$test_file"; \
			status=1; \
		fi; \
		echo ""; \
	done; \
	for test_file in $(NEGATIVE_TESTS); do \
		echo ""; \
		echo "Negative test: $$test_file"; \
		echo "----------------------------------------"; \
		if ./$(TARGET) $$test_file; then \
			echo "FAIL $$test_file unexpectedly passed"; \
			status=1; \
		else \
			echo "PASS $$test_file expected failure"; \
		fi; \
	done; \
	echo "=========================================="; \
	echo "Tests complete."; \
	echo "=========================================="; \
	exit $$status

clean:
	@echo "Cleaning generated files..."
	rm -f $(TARGET) $(LEXER_C) $(PARSER_C) $(PARSER_H) *.o y.tab.c y.tab.h $(TEST_DIR)/*.ast.dot $(TEST_DIR)/*.ast.html
	@echo "Clean complete."

help:
	@echo "JavaScript Parser Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - build parser (default)"
	@echo "  test    - run positive tests and expected-failure test"
	@echo "  clean   - remove generated files and AST visualizations"
	@echo "  help    - show this help"
	@echo ""
	@echo "Examples:"
	@echo "  mingw32-make"
	@echo "  mingw32-make test"
	@echo "  mingw32-make clean"
	@echo "  ./js-parser test/basic.js"
