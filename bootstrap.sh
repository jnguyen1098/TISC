#!/usr/bin/env bash

TEST_DIR="test/asm"
IN_DIR="test/in"
OUT_DIR="test/out"

BIN=bin/a.out

DIFF_FAILED=false
VALGRIND_FAILED=false

trap 'rm -f test_output.tmp; exit' 0 2 3 15

echo "Building project"
make all

for fname in "$TEST_DIR"/*; do
    test=$(basename "$fname" .tm)
    echo "Testing $test.tm"
    if [ "$1" == "-v" ]; then
        valgrind \
            --show-leak-kinds=all --track-origins=yes --leak-check=full --error-exitcode=1 \
            --errors-for-leak-kinds=all --error-limit=no  \
            ./"$BIN" "$TEST_DIR"/"$test".tm < "$IN_DIR"/"$test".in > test_output.tmp
        if [ $? -ne 0 ]; then
            VALGRIND_FAILED=true
        fi
    else
        ./"$BIN" "$TEST_DIR"/"$test".tm < "$IN_DIR"/"$test".in > test_output.tmp
    fi
    diff test_output.tmp "$OUT_DIR"/"$test".out
    if [ $? -ne 0 ]; then
        DIFF_FAILED=true
    fi
    rm -rf "$test_output.tmp"
done

if [ "$DIFF_FAILED" = true ]; then
    echo -e "\e[31mTests failed!\e[0m"
    exit 1
fi

if [ "$VALGRIND_FAILED" = true ]; then
    echo -e "\e[31mValgrind errors detected!\e[0m"
    exit 1
fi

echo -e "\e[32mTests succeeded!\e[0m"
