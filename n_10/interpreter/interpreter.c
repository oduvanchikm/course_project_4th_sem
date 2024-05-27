#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "interpreter.h"

int delete_sep(char **str) {
    int len_str = strlen(*str);

    if (len_str > 1) {
        char *temp = (char*)malloc(sizeof(char) * len_str);

        if (!temp) {
            return NO_MEMORY;
        }

        strncpy(temp, *str, len_str - 1);
        temp[len_str - 1] = 0;

        free(*str);
        *str = temp;
    } else {
        free(*str);
        *str = NULL;
    }

    return SUCCESS;
}

int interpreter(char *file_name, char *file_name_config, int *line_error, char **file_error, int base) {
    FILE *read_file = NULL;
    char *str = NULL;
    array_variables array = {NULL, 0, 0};
    configuration config = {0, 0, 0, NULL};
    int exit_code = 0;
    int result = 0;
    char *var_save = NULL;
    char *num_base = NULL;
    int have_var = 0;

    if ((exit_code = fill_instructions(file_name_config, &config, line_error)) != SUCCESS) {
        *file_error = file_name_config;

        return exit_code;
    }

    *file_error = file_name;
    *line_error = 0;

    if ((read_file = fopen(file_name, "r")) != NULL) {
        while (!feof(read_file)) {
            if ((exit_code = get_str_with_comments(&str, read_file, '#', '[', ']', line_error)) != SUCCESS) {
                if (str) {
                    free(str);
                }
                free_vars(&array);
                free_configuration(&config);
                fclose(read_file);

                return exit_code;
            }

            if (str) {
                if (!is_empty_str(str)) {
                    if ((exit_code = strip(&str)) != SUCCESS) {
                        free(str);
                        free_vars(&array);
                        free_configuration(&config);
                        fclose(read_file);

                        return exit_code;
                    }

                    if (str[strlen(str) - 1] != ';') {
                        if (str) {
                            free(str);
                        }
                        free_vars(&array);
                        free_configuration(&config);
                        fclose(read_file);

                        return INVALID_INSTRUCTION;
                    }

                    if ((exit_code = delete_sep(&str)) != SUCCESS) {
                        free(str);
                        free_vars(&array);
                        free_configuration(&config);
                        fclose(read_file);

                        return exit_code;
                    }

                    if (!is_empty_str(str)) {
                        if ((exit_code = strip(&str)) != SUCCESS) {
                            free(str);
                            free_vars(&array);
                            free_configuration(&config);
                            fclose(read_file);

                            return exit_code;
                        }

                        if (str[strlen(str) - 1] == ';') {
                            free(str);
                            free_vars(&array);
                            free_configuration(&config);
                            fclose(read_file);

                            return INVALID_INSTRUCTION;
                        }

                        if ((exit_code = check_instruction(str, config)) != SUCCESS) {
                            free(str);
                            free_vars(&array);
                            free_configuration(&config);
                            fclose(read_file);

                            return exit_code;
                        }

                        if ((exit_code = get_var_save_result(str, &var_save, config)) != SUCCESS) {
                            free(str);
                            free_vars(&array);
                            free_configuration(&config);
                            fclose(read_file);

                            return exit_code;
                        }

                        have_var = find_var(array, var_save);

                        exit_code = execute_instruction(str, &result, array, config);

                        if (exit_code == INPUT) {
                            printf("Input value of %s: ", var_save);

                            if ((exit_code = input(base, &result)) != SUCCESS) {
                                free(str);
                                free(var_save);
                                free_vars(&array);
                                free_configuration(&config);
                                fclose(read_file);

                                return exit_code;
                            }

                            if (have_var < 0) {
                                if ((exit_code = add_var(&array, var_save, result)) != SUCCESS) {
                                    free(str);
                                    free(var_save);
                                    free_vars(&array);
                                    free_configuration(&config);
                                    fclose(read_file);

                                    return exit_code;
                                }
                            } else {
                                if ((exit_code = update_var(&array, var_save, result)) != SUCCESS) {
                                    free(str);
                                    free(var_save);
                                    free_vars(&array);
                                    free_configuration(&config);
                                    fclose(read_file);

                                    return exit_code;
                                }
                            }
                        } else {
                            if (exit_code == OUTPUT) {
                                if ((exit_code = get_value_var(array, var_save, &result)) != SUCCESS) {
                                    free(str);
                                    free(var_save);
                                    free_vars(&array);
                                    free_configuration(&config);
                                    fclose(read_file);

                                    return exit_code;
                                }

                                if ((exit_code = to_base(result, base, &num_base)) != SUCCESS) {
                                    free(str);
                                    free(var_save);
                                    free_vars(&array);
                                    free_configuration(&config);
                                    fclose(read_file);

                                    return exit_code;
                                }

                                if (is_empty_str(num_base)) {
                                    printf("Value of %s: 0\n", var_save);
                                } else {
                                    printf("Value of %s: %s\n", var_save, num_base);
                                }

                                free(num_base);
                                num_base = NULL;
                            } else {
                                if (exit_code == SUCCESS) {
                                    if (have_var < 0) {
                                        if ((exit_code = add_var(&array, var_save, result)) != SUCCESS) {
                                            free(str);
                                            free(var_save);
                                            free_vars(&array);
                                            free_configuration(&config);
                                            fclose(read_file);

                                            return exit_code;
                                        }
                                    } else {
                                        if ((exit_code = update_var(&array, var_save, result)) != SUCCESS) {
                                            free(str);
                                            free(var_save);
                                            free_vars(&array);
                                            free_configuration(&config);
                                            fclose(read_file);

                                            return exit_code;
                                        }
                                    }
                                } else {
                                    free(str);
                                    free(var_save);
                                    free_vars(&array);
                                    free_configuration(&config);
                                    fclose(read_file);

                                    return exit_code;
                                }
                            }
                        }

                        free(var_save);
                        var_save = NULL;
                    }
                }

                free(str);
                str = NULL;
            }
        }

        fclose(read_file);
        free_vars(&array);
        free_configuration(&config);
    } else {
        return CANT_OPEN_FILE;
    }

    return SUCCESS;
}