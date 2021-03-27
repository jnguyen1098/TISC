#!/usr/bin/env bash

CC="gcc"
VALGRIND="valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full \
          --error-exitcode=1 --errors-for-leak-kinds=all --error-limit=no "

TEST_DIR="test"

ASMS="$TEST_DIR/asm"
INPUTS="$TEST_DIR/in"
OUTPUTS="$TEST_DIR/out"

BOOTSTRAP_SRC="$TEST_DIR/tm.c"

TISC_BIN=bin/TISC
BOOTSTRAP_BIN="$TEST_DIR/tm"

TMP_OUT="_tisc_test_result_output.tmp"

DIFF_FAILED=false
VALGRIND_FAILED=false

trap 'rm -f $TMP_OUT; rm -f exit' 0 2 3 15

echo "Building project"
make all

if [ ! -f "$BOOTSTRAP_BIN" ]; then
    echo "Compiling TM test bootstrapper just in case..."
    "$CC" "$BOOTSTRAP_SRC" -o "$BOOTSTRAP_BIN"
fi

for fname in "$ASMS"/*; do
    testname=$(basename "$fname" .tm)
    if [ ! -f "$OUTPUTS"/"$testname".out ]; then
        echo "$testname's output doesn't exist. Bootstrapping output..."
        "$BOOTSTRAP_BIN" "$ASMS"/"$testname".tm < "$INPUTS"/"$testname".in > "$OUTPUTS"/"$testname".out
    fi
done

for fname in "$ASMS"/*; do
    testname=$(basename "$fname" .tm)
    echo "Testing $testname.tm"
    if [ "$1" == "-v" ]; then
            "$VALGRIND" ./"$TISC_BIN" "$ASMS"/"$testname".tm < "$INPUTS"/"$testname".in > "$TMP_OUT"
        if [ $? -ne 0 ]; then
            VALGRIND_FAILED=true
        fi
    else
        ./"$TISC_BIN" "$ASMS"/"$testname".tm < "$INPUTS"/"$testname".in > "$TMP_OUT"
    fi
    diff "$TMP_OUT" "$OUTPUTS"/"$testname".out
    if [ $? -ne 0 ]; then
        echo "Failed"
        cat "$TMP_OUT"
        echo ""
        echo "Correct"
        cat "$OUTPUTS"/"$testname".out
        echo ""
        DIFF_FAILED=true
    fi
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
