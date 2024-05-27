#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "variables.h"

int find_var(array_variables array, char *name_var) {
    int left = 0;
    int right = array.current_size - 1;
    int find_index = -1;

    if (array.current_size > 0) {
        while (left <= right) {
            int middle = (right + left) / 2;

            if (strcmp(array.vars[middle].name, name_var) == 0) {
                return middle;
            }

            if (strcmp(array.vars[middle].name, name_var) > 0) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
    }

    return find_index;
}

int get_value_var(array_variables array, char *name_var, int *res) {
    int find_index = find_var(array, name_var);

    if (find_index < 0) {
        *res = 0;

        return HAVENT_VAR;
    }

    *res = array.vars[find_index].value;

    return SUCCESS;
}

int add_var(array_variables *array, char *name_var, int value_var) {
    variable *temp = NULL;

    if (array->current_size == array->size) {
        array->size = array->size ? array->size * 2 : 1;
        temp = (variable*)realloc(array->vars, sizeof(variable) * array->size);

        if (!temp) {
            return NO_MEMORY;
        }

        array->vars = temp;
    }

    array->vars[array->current_size].name = (char*)malloc(sizeof(char) * (strlen(name_var) + 1));

    if (!array->vars[array->current_size].name) {
        return NO_MEMORY;
    }

    strcpy(array->vars[array->current_size].name, name_var);

    array->vars[array->current_size].value = value_var;
    array->current_size++;

    qsort(array->vars, array->current_size, sizeof(variable), compare);

    return SUCCESS;
}

int update_var(array_variables *array, char *name_var, int value_var) {
    int find_index = find_var(*array, name_var);

    if (find_index < 0) {
        return HAVENT_VAR;
    }

    array->vars[find_index].value = value_var;

    return SUCCESS;
}

int compare(const void *item_1, const void *item_2) {
    return strcmp(((variable*)item_1)->name, ((variable*)item_2)->name);
}

void free_vars(array_variables *array) {
    if (array->vars) {
        for (int i = 0; i < array->current_size; i++) {
            if (array->vars[i].name) {
                free(array->vars[i].name);
                array->vars[i].name = NULL;
            }
        }

        free(array->vars);
        array->vars = NULL;
        array->current_size = 0;
        array->size = 0;
    }
}

void output_vars(array_variables array) {
    printf("VARS:\n");
    for (int i = 0; i < array.current_size; i++) {
        printf("%s := %d\n", array.vars[i].name, array.vars[i].value);
    }
    printf("\n");
}