/**
 * @file    main.c
 * @brief   Mainline driver program.
 */
#include "TISC.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // TODO(jason) create better way to test program LMAOOO
    // TODO(jason) fix makefile so that it compiles tests/unit...
    // TODO(jason) perhaps maybe a separate driver. or run tests every startup
    if (!strcmp(argv[1], "test")) {
        run_all_tests(0);
        return 0;
    }

    struct TISC tisc = TISC_INIT;

    FILE *program_text = fopen(argv[1], "re");
    if (program_text == NULL) {
        perror("TISC");
        exit(EXIT_FAILURE);
    }

    /* read the program */
    if (!read_instructions(&tisc, program_text)) {
        fprintf(stderr, "Could not read read %s. Exiting\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* switch input file to terminal */
    /* reset( input ); */
    /* read-eval-print */
    printf("TM  simulation (enter h for help)...\n");

    while (do_command(&tisc)) {
    }

    printf("Simulation done.\n");

    if (fclose(program_text) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}
