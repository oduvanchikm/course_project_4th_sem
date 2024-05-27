#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "../string/string.h"

int join_symb(char symb, char **str, int *size) {
    if (*size == 0) {
        *size = 2;
        *str = (char*)malloc(sizeof(char) * *size);

        if (!*str) {
            return NO_MEMORY;
        }

        (*str)[0] = symb;
        (*str)[1] = 0;

        return SUCCESS;
    }

    int len = strlen(*str);

    if (len == *size - 1) {
        *size *= 2;
        char *temp = (char*)realloc(*str, sizeof(char) * *size);

        if (!temp) {
            return NO_MEMORY;
        }

        *str = temp;
    }

    (*str)[len + 1] = 0;
    (*str)[len] = symb;

    return SUCCESS;
}

int get_str(char **str, FILE *read_file) {
    int size = 0;
    char symb = 0;
    int exit_code = 0;

    if (*str) {
        free(*str);
        *str = NULL;
    }

    while ((symb = fgetc(read_file)) != EOF && symb != '\n') {
        exit_code = join_symb(symb, str, &size);

        if (exit_code != SUCCESS) {
            if (*str) {
                free(*str);
                *str = NULL;
            }

            return exit_code;
        }
    }

    if (*str) {
        char *temp = (char*)realloc(*str, sizeof(char) * (strlen(*str) + 1));

        if (!temp) {
            return NO_MEMORY;
        }

        *str = temp;
    }

    return SUCCESS;
}

int get_str_with_comments(char **str, FILE *read_file, char one_liner_comment, char open_multiline_comment, char close_multiline_comment, int *line) {
    char c = 0;
    char *temp_line = NULL;
    int in_comment = 0;
    int read_line = 0;
    int exit_code = 0;
    int size = 0;

    while (!feof(read_file) && !read_line) {
        c = fgetc(read_file);

        if (c == one_liner_comment && !in_comment) {
            while ((c = fgetc(read_file)) != '\n' && c != EOF) {
                ;
            }
        } else {
            if (c == open_multiline_comment) {
                in_comment++;

                while (in_comment && (c = fgetc(read_file)) != EOF) {
                    if (c == '\n') {
                        (*line)++;
                    }

                    if (c == close_multiline_comment) {
                        in_comment--;
                    } else {
                        if (c == open_multiline_comment) {
                            in_comment++;
                        }
                    }
                }

                if (in_comment != 0) {
                    (*line)++;

                    return INVALID_MULTILINE_COMMENT;
                }
            }
        }

        if (c != open_multiline_comment &&
            c != one_liner_comment &&
            c != close_multiline_comment &&
            c != '\n' &&
            c != EOF) {
            if ((exit_code = join_symb(c, str, &size)) != SUCCESS) {
                return exit_code;
            }
        }

        if (c == '\n' || c == EOF) {
            (*line)++;

            if (*str) {
                temp_line = (char*)realloc(*str, sizeof(char) * (strlen(*str) + 1)); // утечка?

                if (!temp_line) {
                    return NO_MEMORY;
                }

                *str = temp_line;
                read_line++;
            }
        }
    }

    return SUCCESS;
}

int token_count(char *str) {
    char _c = ' ';
    char *ptr = str - 1;
    int count = 0;

    while (*++ptr) {
        if (isspace(_c) && !isspace(*ptr)) {
            count++;
        }
        _c = *ptr;
    }

    return count;
}

int strip(char **str) {
    char *res_str = NULL;
    char *ptr_left = *str;
    char *ptr_right = *str + strlen(*str) - 1;

    while (isspace(*ptr_left)) {
        ptr_left++;
    }

    while (isspace(*ptr_right)) {
        ptr_right--;
    }

    res_str = (char*)malloc(sizeof(char) * (ptr_right - ptr_left + 2));

    if (!res_str) {
        return NO_MEMORY;
    }

    strncpy(res_str, ptr_left, ptr_right - ptr_left + 1);
    res_str[ptr_right - ptr_left + 1] = 0;
    free(*str);
    *str = res_str;

    return SUCCESS;
}

int reverse(char **str) {
    int len_str = strlen(*str);
    char *tmp = (char*)malloc(sizeof(char) * (len_str + 1));

    if (!tmp) {
        return NO_MEMORY;
    }

    for (int i = 0; i < len_str; i++) {
        tmp[i] = (*str)[len_str - i - 1];
    }
    tmp[len_str] = 0;

    free(*str);
    *str = tmp;

    return SUCCESS;
}

int split_space(char *str, char ***tokens) {
    char *ptr = str - 1;
    int exit_code = 0;
    int tmp_size = 0;
    int index = 0;
    char _c = ' ';

    *tokens = (char**)malloc(sizeof(char*) * token_count(str));

    if (!*tokens) {
        return NO_MEMORY;
    }

    while (*++ptr) {
        if (!isspace(*ptr)) {
            exit_code = join_symb(*ptr, &((*tokens)[index]), &tmp_size);

            if (exit_code != SUCCESS) {
                return exit_code;
            }
        }
        if (isspace(*ptr) && !isspace(_c)) {
            char *temp = (char*)realloc((*tokens)[index], sizeof(char) * (strlen((*tokens)[index]) + 1));

            if (!temp) {
                return NO_MEMORY;
            }

            (*tokens)[index++] = temp;
            tmp_size = 0;
        }
        _c = *ptr;
    }

    return SUCCESS;
}

int char_to_str(int symb, char **str) {
    if (*str) {
        free(*str);
        *str = NULL;
    }

    *str = (char*)malloc(sizeof(char) * 2);

    if (!*str) {
        return NO_MEMORY;
    }

    (*str)[0] = (char)symb;
    (*str)[1] = 0;

    return SUCCESS;
}

int add_str(char **str, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char *source = va_arg(args, char*);
        if (!*str) {
            *str = (char*)malloc(sizeof(char) * (strlen(source) + 1));

            if (!*str) {
                va_end(args);
                return NO_MEMORY;
            }

            strcpy(*str, source);
        } else {
            *str = (char*)realloc(*str, sizeof(char) * (strlen(*str) + strlen(source) + 1));

            if (!*str) {
                va_end(args);
                return NO_MEMORY;
            }

            strcpy(*str + strlen(*str), source);
        }
    }

    va_end(args);

    return SUCCESS;
}

int add_chr(char **str, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char symb = va_arg(args, int);
        char *temp = NULL;
        int exit_code = char_to_str(symb, &temp);

        if (exit_code != SUCCESS) {
            va_end(args);
            return exit_code;
        }

        exit_code = add_str(str, 1, temp);

        if (exit_code != SUCCESS) {
            va_end(args);
            return exit_code;
        }

        free(temp);
    }

    va_end(args);

    return SUCCESS;
}

int to_str(int num, char **str) {
    int size = 0;
    int exit_code = 0;
    int abs_num = abs(num);

    while (abs_num) {
        exit_code = join_symb(abs_num % 10 + '0', str, &size);

        if (exit_code != SUCCESS) {
            return exit_code;
        }

        abs_num /= 10;
    }

    if (num < 0) {
        if ((exit_code = join_symb('-', str, &size)) != SUCCESS) {
            return exit_code;
        }
    }

    exit_code = reverse(str);

    if (exit_code != SUCCESS) {
        return exit_code;
    }

    return SUCCESS;
}

int to_int(char *str) {
    int sign = 1;
    char *ptr = str - 1;
    int res = 0;

    if (*str == '-') {
        ptr++;
        sign = -1;
    }

    while (*++ptr) {
        res = res * 10 + (*ptr - '0');
    }

    return sign * res;
}

int is_empty_str(char *str) {
    if (!str) {
        return 1;
    }

    char *ptr = str - 1;

    while (*++ptr) {
        if (!isspace(*ptr)) {
            return 0;
        }
    }

    return 1;
}