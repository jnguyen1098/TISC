#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TISC.h"
#include "TISC_defs.h"

#include "seethe.h"

#ifdef LOG_LEVEL
# undef LOG_LEVEL
#endif

#define LOG_LEVEL DEBUG

#define INDENT_INCREMENT 2
#define INDENT_LEVEL_START 0

// TODO(jason) header?
void run_all_tests(int level);
void run_init_tests(int level);

int assert_TISC_equal(struct TISC *a, struct TISC *b);

int assert_TISC_equal(struct TISC *a, struct TISC *b)
{
    if (a->inst_itr != b->inst_tr) return 0;
    if (a->data_itr != b->data_itr) return 0;
    // compare equality in instruction_memory
    // compare equality in data_memory
    // compare equality in registers
    // compare line_buf
    // compare inCol
    // compare curr_char
    // compare curr word
    // compare num
}

void run_init_tests(int level)
{
    info(level, "\n");
    info(level, "Running init tests\n");

    info(level + 1, "Init test 1\n");
    assert(init_TISC(NULL) == false);

    info(level + 1, "Initialized values testing\n");
    struct TISC tmp;
    memset(&tmp, 0xFF, sizeof(struct TISC));

    info(level, "Done running init tests\n");
}

void run_all_tests(int level)
{
    info(level, "\n");
    info(level, "Running all tests\n");

    run_init_tests(level + 1);

    info(level, "Done running all tests\n");
}

#ifdef main
# undef main
#endif

int main(void)
{
    run_all_tests(INDENT_LEVEL_START);
}
