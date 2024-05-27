#ifndef N_10_VARIABLES_H
#define N_10_VARIABLES_H

#include "../types/types.h"
#include "../check/check.h"
#include "../string/string.h"

int find_var(array_variables, char*);
int get_value_var(array_variables, char*, int*);
int add_var(array_variables*, char*, int);
int update_var(array_variables*, char*, int);
int compare(const void*, const void*);
void free_vars(array_variables*);
void output_vars(array_variables);

#endif //N_10_VARIABLES_H
