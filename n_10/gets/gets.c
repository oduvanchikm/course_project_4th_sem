#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gets.h"

int get_equal(char *str, char **equal, configuration config) {
    int index = find_instruction("=", config.instructions);

    *equal = NULL;

    if (strchr(str, '=')) {
        *equal = (char*)malloc(sizeof(char) * 2);

        if (!*equal) {
            return NO_MEMORY;
        }

        strcpy(*equal, "=");
    } else {
        if (config.instructions[index].synonym_name && strstr(str, config.instructions[index].synonym_name)) {
            *equal = (char*)malloc(sizeof(char) * (strlen(config.instructions[index].synonym_name) + 1));

            if (!*equal) {
                return NO_MEMORY;
            }

            strcpy(*equal, config.instructions[index].synonym_name);
        }
    }

    return SUCCESS;
}

int get_operator(char *str, char **operator, int *is_binary, configuration config) {
    char *coincidences[COUNT_INSTRUCTIONS];
    int max_index = 0;
    int size = 0;

    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
        if (strstr(str, config.instructions[i].original_name)) {
            coincidences[size] = (char*)malloc(sizeof(char) * (strlen(config.instructions[i].original_name) + 1));

            if (!coincidences[size]) {
                return NO_MEMORY;
            }

            strcpy(coincidences[size], config.instructions[i].original_name);
            size++;
        } else {
            if ((config.instructions[i].synonym_name && strstr(str, config.instructions[i].synonym_name))) {
                coincidences[size]= (char*)malloc(sizeof(char) * (strlen(config.instructions[i].synonym_name) + 1));

                if (!coincidences[size]) {
                    return NO_MEMORY;
                }

                strcpy(coincidences[size], config.instructions[i].synonym_name);
                size++;
            }
        }
    }

    if (size != 0) {
        for (int i = 1; i < size; i++) {
            if (strlen(coincidences[i]) > strlen(coincidences[max_index])) {
                max_index = i;
            }
        }

        *operator = (char*)malloc(sizeof(char) * (strlen(coincidences[max_index]) + 1));

        if (!*operator) {
            for (int i = 0; i < size; i++) {
                free(coincidences[i]);
            }

            return NO_MEMORY;
        }

        strcpy(*operator, coincidences[max_index]);

        if (is_binary) {
            *is_binary = config.instructions[find_instruction(*operator, config.instructions)].is_binary;
        }

        for (int i = 0; i < size; i++) {
            free(coincidences[i]);
        }

        return SUCCESS;
    }

    return INVALID_INSTRUCTION;
}

int get_expression(char *str, char **expression, configuration config) {
    char *ptr = NULL;
    char *equal = NULL;
    int exit_code = 0;

    if ((exit_code = get_equal(str, &equal, config)) != SUCCESS) {
        return exit_code;
    }

    if (equal && strstr(str, equal)) {
        if (config.save_result == LEFT) {
            ptr = strstr(str, equal) + strlen(equal);

            while (isspace(*ptr)) {
                ptr++;
            }

            *expression = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

            if (!*expression) {
                if(equal) {
                    free(equal);
                }

                return NO_MEMORY;
            }

            strcpy(*expression, ptr);
        } else {
            ptr = strstr(str, equal) - 1;

            while (isspace(*ptr)) {
                ptr--;
            }

            ptr++;

            *expression = (char*)malloc(sizeof(char) * (ptr - str + 1));

            if (!*expression) {
                if(equal) {
                    free(equal);
                }

                return NO_MEMORY;
            }

            strncpy(*expression, str, ptr - str);
            (*expression)[ptr - str] = 0;
        }
    } else {
        *expression = (char*)malloc(sizeof(char) * (strlen(str) + 1));

        if (!*expression) {
            if(equal) {
                free(equal);
            }

            return NO_MEMORY;
        }

        strcpy(*expression, str);
    }

    if(equal) {
        free(equal);
    }

    return SUCCESS;
}

int get_var_binary_before(char *expression, char **var_1, char **var_2) {
    char *ptr = expression + 1;
    int tmp_size = 0;
    int exit_code = 0;
    char *tmp = NULL;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ',') {
        if ((exit_code = join_symb(*ptr, var_1, &tmp_size)) != SUCCESS) {
            if (*var_1) {
                free(*var_1);
                *var_1 = NULL;
            }

            return exit_code;
        }

        ptr++;
    }

    tmp_size = 0;

    while (*ptr != ',') {
        ptr++;
    }

    ptr ++;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ')') {
        if ((exit_code = join_symb(*ptr, var_2, &tmp_size)) != SUCCESS) {
            if (*var_2) {
                free(*var_2);
                *var_2 = NULL;
            }
            free(*var_1);
            *var_1 = NULL;

            return exit_code;
        }

        ptr++;
    }

    tmp = (char*)realloc(*var_1, sizeof(char) * (strlen(*var_1) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_1 = tmp;

    tmp = (char*)realloc(*var_2, sizeof(char) * (strlen(*var_2) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_2 = tmp;

    return SUCCESS;
}

int get_var_binary_middle(char *expression, char **var_1, char **var_2) {
    char *ptr = expression;
    int tmp_size = 0;
    int exit_code = 0;
    char *tmp = NULL;

    while (!isspace(*ptr)) {
        if ((exit_code = join_symb(*ptr, var_1, &tmp_size)) != SUCCESS) {
            if (*var_1) {
                free(*var_1);
                *var_1 = NULL;
            }

            return exit_code;
        }

        ptr++;
    }

    tmp_size = 0;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr)) {
        ptr++;
    }

    while (isspace(*ptr)) {
        ptr++;
    }

    while (*ptr && !isspace(*ptr)) {
        if ((exit_code = join_symb(*ptr, var_2, &tmp_size)) != SUCCESS) {
            if (*var_2) {
                free(*var_2);
                *var_2 = NULL;
            }
            free(*var_1);
            *var_1 = NULL;

            return exit_code;
        }

        ptr++;
    }

    tmp = (char*)realloc(*var_1, sizeof(char) * (strlen(*var_1) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_1 = tmp;

    tmp = (char*)realloc(*var_2, sizeof(char) * (strlen(*var_2) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_2 = tmp;

    return SUCCESS;
}

int get_var_binary_after(char *expression, char **var_1, char **var_2) {
    char *ptr = expression;
    int tmp_size = 0;
    int exit_code = 0;
    char *tmp = NULL;

    while (*ptr != '(') {
        ptr++;
    }

    ptr++;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ',') {
        if ((exit_code = join_symb(*ptr, var_1, &tmp_size)) != SUCCESS) {
            if (*var_1) {
                free(*var_1);
                *var_1 = NULL;
            }

            return exit_code;
        }

        ptr++;
    }

    tmp_size = 0;

    while (*ptr != ',') {
        ptr++;
    }

    ptr ++;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ')') {
        if ((exit_code = join_symb(*ptr, var_2, &tmp_size)) != SUCCESS) {
            if (*var_2) {
                free(*var_2);
                *var_2 = NULL;
            }
            free(*var_1);
            *var_1 = NULL;

            return exit_code;
        }

        ptr++;
    }

    tmp = (char*)realloc(*var_1, sizeof(char) * (strlen(*var_1) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_1 = tmp;

    tmp = (char*)realloc(*var_2, sizeof(char) * (strlen(*var_2) + 1));

    if (!tmp) {
        free(*var_1);
        free(*var_2);
        *var_1 = NULL;
        *var_2 = NULL;

        return NO_MEMORY;
    }

    *var_2 = tmp;

    return SUCCESS;
}

int get_var_binary(char *expression, char **var_1, char **var_2, int location) {
    switch(location) {
        case BEFORE_OPERATOR: return get_var_binary_before(expression, var_1, var_2);
        case IN_MIDDLE: return get_var_binary_middle(expression, var_1, var_2);
        case AFTER_OPERATOR: return get_var_binary_after(expression, var_1, var_2);
    }

    return SUCCESS;
}

int get_var_unary_before(char *expression, char **var) {
    char *ptr = expression + 1;
    int tmp_size = 0;
    int exit_code = 0;
    char *tmp = NULL;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ')') {
        if ((exit_code = join_symb(*ptr, var, &tmp_size)) != SUCCESS) {
            if (*var) {
                free(*var);
                *var = NULL;
            }

            return exit_code;
        }

        ptr++;
    }

    tmp_size = 0;

    tmp = (char*)realloc(*var, sizeof(char) * (strlen(*var) + 1));

    if (!tmp) {
        free(*var);
        *var = NULL;

        return NO_MEMORY;
    }

    *var = tmp;

    return SUCCESS;
}

int get_var_unary_after(char *expression, char **var) {
    char *ptr = expression;
    int tmp_size = 0;
    int exit_code = 0;
    char *tmp = NULL;

    while (*ptr != '(') {
        ptr++;
    }

    ptr++;

    while (isspace(*ptr)) {
        ptr++;
    }

    while (!isspace(*ptr) && *ptr != ')') {
        if ((exit_code = join_symb(*ptr, var, &tmp_size)) != SUCCESS) {
            if (*var) {
                free(*var);
                *var = NULL;
            }

            return exit_code;
        }

        ptr++;
    }

    tmp_size = 0;

    tmp = (char*)realloc(*var, sizeof(char) * (strlen(*var) + 1));

    if (!tmp) {
        free(*var);
        *var = NULL;

        return NO_MEMORY;
    }

    *var = tmp;

    return SUCCESS;
}

int get_var_unary(char *expression, char **var, int location) {
    switch(location) {
        case BEFORE_OPERATOR: return get_var_unary_before(expression, var);
        case AFTER_OPERATOR: return get_var_unary_after(expression, var);
    }

    return SUCCESS;
}

int get_var_save_result(char *str, char **var, configuration config) {
    char *equal = NULL;
    int exit_code = 0;
    char *pos_equal = NULL;
    char *ptr = NULL;

    if ((exit_code = get_equal(str, &equal, config)) != SUCCESS) {
        return exit_code;
    }

    if (equal) {
        pos_equal = strstr(str, equal);

        if (config.save_result == LEFT) {
            ptr = pos_equal - 1;

            while (isspace(*ptr)) {
                ptr--;
            }

            ptr++;

            *var = (char*)malloc(sizeof(char) * (ptr - str + 1));

            if (!*var) {
                free(equal);

                return exit_code;
            }

            strncpy(*var, str, ptr - str);
            (*var)[ptr - str] = 0;
        } else {
            ptr = pos_equal + strlen(equal);

            while (isspace(*ptr)) {
                ptr++;
            }

            *var = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

            if (!*var) {
                free(equal);

                return exit_code;
            }

            strcpy(*var, ptr);
        }

        free(equal);
    } else {
        if ((exit_code = get_var_unary(str, var, config.location_unary)) != SUCCESS) {
            return exit_code;
        }
    }

    return SUCCESS;
}