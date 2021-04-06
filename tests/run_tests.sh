#!/usr/bin/env bash

# Environment
CC="gcc"
VALGRIND="valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full \
          --error-exitcode=1 --errors-for-leak-kinds=all --error-limit=no"

TEST_DIR="."

ASMS="$TEST_DIR/asm"
INPUTS="$TEST_DIR/in"
OUTPUTS="$TEST_DIR/out"

BOOTSTRAP_SRC="$TEST_DIR/tm.c"

TISC_BIN=../bin/TISC
BOOTSTRAP_BIN="$TEST_DIR/tm"

TMP_OUT="_tisc_test_result_output.tmp"

DIFF_FAILED=false
VALGRIND_FAILED=false

trap 'rm -f $TMP_OUT; rm -f exit' 0 2 3 15

echo "Building project"
cd .. && make all && cd -
echo ""

if [ ! -f "$BOOTSTRAP_BIN" ]; then
    echo "Compiling TM test bootstrapper just in case..."
    eval $CC "$BOOTSTRAP_SRC" -o "$BOOTSTRAP_BIN" 2>/dev/null
fi

# Create test case output if not exists
for fname in "$ASMS"/*; do
    testcase=$(basename "$fname" .tm)
    if [ ! -f "$OUTPUTS"/"$testcase".out ]; then
        echo "$testcase's output doesn't exist. Bootstrapping output..."
        "$BOOTSTRAP_BIN" "$ASMS"/"$testcase".tm < "$INPUTS"/"$testcase".in > "$OUTPUTS"/"$testcase".out
    fi
done

echo "Running E2E tests"
for fname in "$ASMS"/*
do
    # Generate test case ID
    testcase=$(basename "$fname" .tm)
    echo "Testing $testcase.tm"

    # If valgrind is specified
    if [ "$1" == "-v" ]; then
        if ! eval "$VALGRIND" ./"$TISC_BIN" "$ASMS"/"$testcase".tm \
            < "$INPUTS"/"$testcase".in > "$TMP_OUT"; then
            VALGRIND_FAILED=true
        fi
    else
        ./"$TISC_BIN" "$ASMS"/"$testcase".tm < "$INPUTS"/"$testcase".in > "$TMP_OUT"
    fi

    # If the test fails, print both files alongside diff
    if ! diff "$TMP_OUT" "$OUTPUTS"/"$testcase".out; then
        echo ""
        echo "Failed"
        cat "$TMP_OUT"
        echo ""
        echo "Correct"
        cat "$OUTPUTS"/"$testcase".out
        echo ""
        DIFF_FAILED=true
    fi
done

if [ "$DIFF_FAILED" = true ]; then
    echo -e "\e[31mE2e tests failed!\n\e[0m"
    exit 1
fi

if [ "$VALGRIND_FAILED" = true ]; then
    echo -e "\n\e[31mValgrind errors detected!\e[0m"
    exit 1
fi

echo -e "\e[32mE2E tests succeeded!\n\e[0m"
