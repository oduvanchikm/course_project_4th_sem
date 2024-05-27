#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "configuration.h"

int find_instruction(char *name_instruction, instruction *instructions) {
    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
        if (strcmp(instructions[i].original_name, name_instruction) == 0) {
            return i;
        } else {
            if (instructions[i].synonym_name && strcmp(instructions[i].synonym_name, name_instruction) == 0) {
                return i;
            }
        }
    }

    return -1;
}

int check_config(configuration config) {
    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
        if (config.instructions[i].synonym_name) {
            for (int j = 0; j < COUNT_INSTRUCTIONS; j++) {
                if (i != j) {
                    if (strcmp(config.instructions[i].synonym_name, config.instructions[j].original_name) == 0) {
                        return INVALID_INSTRUCTION;
                    } else {
                        if (config.instructions[j].synonym_name) {
                            if (strcmp(config.instructions[i].synonym_name, config.instructions[j].synonym_name) == 0) {
                                return INVALID_INSTRUCTION;
                            }
                        }
                    }
                }
            }
        }
    }

    return SUCCESS;
}

int fill_instructions(char *filename, configuration *config, int *line_error) {
    FILE *read_file = NULL;
    int exit_code = 0;
    int good_string = 0;
    int index = 0;
    char *str = NULL;
    char *ptr = NULL;
    char *name_instruction = NULL;
    char *name_instructions[COUNT_INSTRUCTIONS] = {
            "add",
            "mult",
            "sub",
            "pow",
            "div",
            "rem",
            "xor",
            "input",
            "output",
            "="
    };
    int binary_instructions[COUNT_INSTRUCTIONS] = {
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            0,
            0,
            1
    };

    config->instructions = (instruction*)malloc(sizeof(instruction) * COUNT_INSTRUCTIONS);

    if (!config->instructions) {
        *line_error = 0;

        return NO_MEMORY;
    }

    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
        config->instructions[i].original_name = (char*)malloc(sizeof(char) * (strlen(name_instructions[i]) + 1));
        config->instructions[i].synonym_name = NULL;

        if (!config->instructions[i].original_name) {
            for (int j = 0; j < i; j++) {
                free(config->instructions[j].original_name);
            }
            free(config->instructions);
            config->instructions = NULL;

            return NO_MEMORY;
        }

        strcpy(config->instructions[i].original_name, name_instructions[i]);
        config->instructions[i].is_binary = binary_instructions[i];
    }

    config->save_result = LEFT;
    config->location_unary = AFTER_OPERATOR;
    config->location_binary = AFTER_OPERATOR;

    if ((read_file = fopen(filename, "r")) != NULL) {
        while (!feof(read_file)) {
            if ((exit_code = get_str_with_comments(&str, read_file, '#', '[', ']', line_error)) != SUCCESS) {
                for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                    free(config->instructions[i].original_name);
                    if (config->instructions[i].synonym_name) {
                        free(config->instructions[i].synonym_name);
                    }
                }
                fclose(read_file);
                free(config->instructions);
                config->instructions = NULL;

                return exit_code;
            }

            if (str) {
                if ((exit_code = strip(&str)) != SUCCESS) {
                    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                        free(config->instructions[i].original_name);
                        if (config->instructions[i].synonym_name) {
                            free(config->instructions[i].synonym_name);
                        }
                    }
                    free(str);
                    fclose(read_file);
                    free(config->instructions);
                    config->instructions = NULL;

                    return exit_code;
                }

                if (!is_empty_str(str)) {
                    if (token_count(str) == 2) {
                        ptr = str;

                        while (!isspace(*ptr)) {
                            ptr++;
                        }

                        name_instruction = (char*)malloc(sizeof(char) * (ptr - str + 1));

                        if (!name_instruction) {
                            for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                                free(config->instructions[i].original_name);
                                if (config->instructions[i].synonym_name) {
                                    free(config->instructions[i].synonym_name);
                                }
                            }
                            free(str);
                            fclose(read_file);
                            free(config->instructions);
                            config->instructions = NULL;

                            return NO_MEMORY;
                        }

                        strncpy(name_instruction, str, ptr - str);
                        name_instruction[ptr - str] = 0;

                        if ((index = find_instruction(name_instruction, config->instructions)) < 0) {
                            for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                                free(config->instructions[i].original_name);
                                if (config->instructions[i].synonym_name) {
                                    free(config->instructions[i].synonym_name);
                                }
                            }
                            free(str);
                            free(name_instruction);
                            fclose(read_file);
                            free(config->instructions);
                            config->instructions = NULL;

                            return INVALID_INSTRUCTION;
                        }

                        if (config->instructions[index].synonym_name) {
                            free(config->instructions[index].synonym_name);
                            config->instructions[index].synonym_name = NULL;
                        }

                        while (isspace(*ptr)) {
                            ptr++;
                        }

                        config->instructions[index].synonym_name = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

                        if (!config->instructions[index].synonym_name) {
                            for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                                free(config->instructions[i].original_name);
                                if (config->instructions[i].synonym_name) {
                                    free(config->instructions[i].synonym_name);
                                }
                            }
                            free(str);
                            free(name_instruction);
                            fclose(read_file);
                            free(config->instructions);
                            config->instructions = NULL;

                            return NO_MEMORY;
                        }

                        strcpy(config->instructions[index].synonym_name, ptr);
                        free(name_instruction);
                        name_instruction = NULL;

                        if ((exit_code = check_config(*config)) != SUCCESS) {
                            for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                                free(config->instructions[i].original_name);
                                if (config->instructions[i].synonym_name) {
                                    free(config->instructions[i].synonym_name);
                                }
                            }
                            free(str);
                            fclose(read_file);
                            free(config->instructions);
                            config->instructions = NULL;

                            return exit_code;
                        }
                    } else {
                        if (strcmp(str, "left=") == 0) {
                            config->save_result = LEFT;
                            good_string++;
                        }
                        if (strcmp(str, "right=") == 0) {
                            config->save_result = RIGHT;
                            good_string++;
                        }
                        if (strcmp(str, "()op") == 0) {
                            config->location_unary = BEFORE_OPERATOR;
                            config->location_binary = BEFORE_OPERATOR;
                            good_string++;
                        }
                        if (strcmp(str, "op()") == 0) {
                            config->location_unary = AFTER_OPERATOR;
                            config->location_binary = AFTER_OPERATOR;
                            good_string++;
                        }
                        if (strcmp(str, "(op)") == 0) {
                            config->location_binary = IN_MIDDLE;
                            good_string++;
                        }

                        if (good_string == 0) {
                            for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
                                free(config->instructions[i].original_name);
                                if (config->instructions[i].synonym_name) {
                                    free(config->instructions[i].synonym_name);
                                }
                            }
                            free(str);
                            free(name_instruction);
                            fclose(read_file);
                            free(config->instructions);
                            config->instructions = NULL;

                            return INVALID_INSTRUCTION;
                        }

                        good_string = 0;
                    }
                }

                free(str);
                str = NULL;
            }
        }

        fclose(read_file);
    } else {
        return CANT_OPEN_FILE;
    }

    return SUCCESS;
}

void free_configuration(configuration *config) {
    if (config->instructions) {
        for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
            if (config->instructions[i].original_name) {
                free(config->instructions[i].original_name);
                config->instructions[i].original_name = NULL;
            }
            if (config->instructions[i].synonym_name) {
                free(config->instructions[i].synonym_name);
                config->instructions[i].synonym_name = NULL;
            }
        }

        free(config->instructions);
        config->instructions = NULL;
    }
}

void output_instructions(instruction *instructions) {
    for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
        printf("%s ", instructions[i].original_name);
        if (instructions[i].synonym_name) {
            printf("(%s) ", instructions[i].synonym_name);
        }
        if (instructions[i].is_binary) {
            printf("BINARY\n");
        } else {
            printf("UNARY\n");
        }
    }

    printf("\n");
}