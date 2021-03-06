/**
 * @file    main.c
 * @brief   Mainline driver program.
 */
#include <string.h>
#include "TISC.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct TISC tisc;
    if (!init_TISC(&tisc)) {
        fprintf(stderr, "Could not initialize TISC. Existing\n");
        exit(EXIT_FAILURE);
    }

    FILE *program_text = fopen(argv[1], "re");
    if (program_text == NULL) {
        perror("TISC");
        exit(EXIT_FAILURE);
    }

    /* read the program */
    if (!read_program(&tisc, program_text)) {
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
