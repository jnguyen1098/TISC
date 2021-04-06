#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "TISC.h"
#include "TISC_defs.h"

#define INDENT_INCREMENT 2
#define INDENT_LEVEL_START 0

// TODO(jason) header?
void run_all_tests(int level);

void run_all_tests(int level)
{
    if (level) {}
}

#ifdef main
# undef main
#endif

int main(void)
{
    run_all_tests(INDENT_LEVEL_START);
}
