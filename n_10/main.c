#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types/types.h"
#include "string/string.h"
#include "check/check.h"
#include "gets/gets.h"
#include "configuration/configuration.h"
#include "interpreter/interpreter.h"

void print_error(int, int, char*);

int main(int argc, char *argv[]) {
    int exit_code = 0;
    int line_error = 0;
    char *file_error = NULL;

    if (argc >= 3) {
        if (argc == 4) {
            if (check_number_notation(argv[3], 10)) {
                if ((exit_code = interpreter(argv[1], argv[2], &line_error, &file_error, atoi(argv[3]))) != SUCCESS) {
                    print_error(exit_code, line_error, file_error);

                    return exit_code;
                }
            } else {
                print_error(INVALID_NOTATION, 0, NULL);
            }
        } else {
            if (argc == 3) {
                if ((exit_code = interpreter(argv[1], argv[2], &line_error, &file_error, 10)) != SUCCESS) {
                    print_error(exit_code, line_error, file_error);

                    return exit_code;
                }
            } else {
                print_error(INVALID_COUNT_ARGS, 0, NULL);
            }
        }
    } else {
        print_error(INVALID_COUNT_ARGS, 0, NULL);
    }

    return 0;
}

void print_error(int exit_code, int line_error, char *file_error) {
    char *errors[10] = {
            "NO_MEMORY - The system is out of memory\n",
            "INVALID_MULTILINE_COMMENT - You must close multiline comment\n",
            "CANT_OPEN_FILE - Can't open file\n",
            "INVALID_INSTRUCTION - You put an invalid instruction\n",
            "HAVENT_VAR - There is an undeclared variable\n",
            "HAVENT_OPERATOR - There is an invalid operator\n",
            "DIVISION_BY_ZERO - Division by zero\n",
            "INVALID_NUMBER - You put an invalid number\n",
            "INVALID_NOTATION - You put an invalid notation number\n",
            "INVALID_COUNT_ARGS - You put an invalid count of arguments\n"
    };

    if (file_error) {
        fprintf(stderr, "(%s) %d: %s", file_error, line_error, errors[abs(exit_code) - 2]);
    } else {
        fprintf(stderr, "%d: %s", line_error, errors[abs(exit_code) - 2]);
    }
}