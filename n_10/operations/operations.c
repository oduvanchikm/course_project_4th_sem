#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"

int to_10(char *num_base, int base, int *res) {
    char *ptr = num_base - 1;
    int sign = 1;

    if (*num_base == '-') {
        ptr++;
        sign = -1;
    }

    while (*++ptr) {
        *res = *res * base + ((isdigit(*ptr)) ? (*ptr - '0') : (*ptr - 'A' + 10));
    }

    *res = sign * *res;

    return SUCCESS;
}

int to_base(int num, int base, char **res) {
    char buff[BUFSIZ];
    char *ptr = buff + BUFSIZ - 1;
    int sign = 1;
    *ptr = 0;
    ptr--;

    if (num < 0) {
        num = abs(num);
        sign = -1;
    }

    while (num) {
        *ptr-- = num % base < 10 ? num % base + '0' : num % base + 'A' - 10;
        num /= base;
    }

    if (sign < 0) {
        *ptr = '-';
    } else {
        ptr++;
    }

    *res = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

    if (!*res) {
        return NO_MEMORY;
    }

    strcpy(*res, ptr);

    return SUCCESS;
}

int input(int notation, int *res) {
    char *number = NULL;
    int exit_code = 0;

    *res = 0;

    if ((exit_code = get_str(&number, stdin)) != SUCCESS) {
        return exit_code;
    }

    if (!number || is_empty_str(number)) {
        if (number) {
            free(number);
        }

        return INVALID_NUMBER;
    }

    if (!check_number_notation(number, notation)) {
        free(number);

        return INVALID_NUMBER;
    }

    if ((exit_code = to_10(number, notation, res)) != SUCCESS) {
        free(number);

        return exit_code;
    }

    free(number);

    return SUCCESS;
}

int _add_(int val_1, int val_2) {
    return val_1 + val_2;
}

int _mult_(int val_1, int val_2) {
    return val_1 * val_2;
}

int _sub_(int val_1, int val_2) {
    return val_1 - val_2;
}

int _pow_(int val_1, int val_2) {
    return pow(val_1, val_2);
}

int _div_(int val_1, int val_2) {
    return val_1 / val_2;
}

int _rem_(int val_1, int val_2) {
    return val_1 % val_2;
}

int _xor_(int val_1, int val_2) {
    return val_1 ^ val_2;
}

int execute_operation(char *operator, int item_1, int item_2, int *res, configuration config) {
    operation func_operations[COUNT_OP] = {
            _add_,
            _mult_,
            _sub_,
            _pow_,
            _div_,
            _rem_,
            _xor_,
    };

    char *name_operations[COUNT_OP] = {
            "add",
            "mult",
            "sub",
            "pow",
            "div",
            "rem",
            "xor"
    };

    int index = find_instruction(operator, config.instructions);
    char *op_original = config.instructions[index].original_name;

    if (index < 0) {
        return HAVENT_OPERATOR;
    }

    if (strcmp(op_original, "div") == 0 && item_2 == 0) {
        return DIVISION_BY_ZERO;
    }

    for (int i = 0; i < COUNT_OP; i++) {
        if (strcmp(op_original, name_operations[i]) == 0) {
            *res = func_operations[i](item_1, item_2);
        }
    }

    return SUCCESS;
}

int execute_instruction(char *str, int *res, array_variables array, configuration config) {
    char *name_var_1 = NULL;
    char *name_var_2 = NULL;
    int value_var_1 = 0;
    int value_var_2 = 0;
    char *equal = NULL;
    char *operator = NULL;
    char *expression = NULL;
    int exit_code = 0;
    int index_input = 0;

    if ((exit_code = get_equal(str, &equal, config)) != SUCCESS) {
        return exit_code;
    }

    if (equal) {
        if ((exit_code = get_expression(str, &expression, config)) != SUCCESS) {
            free(equal);

            return exit_code;
        }

        if ((exit_code = get_operator(str, &operator, NULL, config)) != SUCCESS) {
            free(equal);
            free(expression);

            return exit_code;
        }

        //printf("operator: %s\n", operator);
        //printf("expression: %s\n", expression);

        if ((exit_code = get_var_binary(expression, &name_var_1, &name_var_2, config.location_binary)) != SUCCESS) {
            free(equal);
            free(expression);
            free(operator);

            return exit_code;
        }

        if ((exit_code = get_value_var(array, name_var_1, &value_var_1)) != SUCCESS) {
            free(name_var_1);
            free(name_var_2);
            free(equal);
            free(expression);
            free(operator);

            return exit_code;
        }

        if ((exit_code = get_value_var(array, name_var_2, &value_var_2)) != SUCCESS) {
            free(name_var_1);
            free(name_var_2);
            free(equal);
            free(expression);
            free(operator);

            return exit_code;
        }

        if ((exit_code = execute_operation(operator, value_var_1, value_var_2, res, config)) != SUCCESS) {
            free(name_var_1);
            free(name_var_2);
            free(equal);
            free(expression);
            free(operator);

            return exit_code;
        }

        free(name_var_1);
        free(name_var_2);
        free(equal);
        free(expression);
        free(operator);
    } else {
        if ((exit_code = get_operator(str, &operator, NULL, config)) != SUCCESS) {
            return exit_code;
        }

        index_input = find_instruction("input", config.instructions);

        if (strcmp(operator, "input") == 0 ||
            (config.instructions[index_input].synonym_name && strcmp(operator, config.instructions[index_input].synonym_name) == 0)) {
            free(operator);

            return INPUT;
        } else {
            free(operator);

            return OUTPUT;
        }
    }

    return SUCCESS;
}