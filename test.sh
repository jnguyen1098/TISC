#!/usr/bin/env bash

SRC_DIR="test/src"
TEST_DIR="test/asm"
IN_DIR="test/in"
OUT_DIR="test/out"

BIN=bin/TISC

TESTS="gcd fac sort"

make all

for test in $TESTS; do
    echo "Testing $test.tm"
    ./"$BIN" "$TEST_DIR"/"$test".tm < "$IN_DIR"/"$test".in > "$test_output.tmp"
    # valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full ./"$BIN" "$TEST_DIR"/"$test".tm < "$IN_DIR"/"$test".in > "$test_output.tmp"
    diff "$test_output.tmp" "$OUT_DIR"/"$test".out
    rm -rf "$test_output.tmp"
done

echo -e "\e[32mDone!\e[0m"
