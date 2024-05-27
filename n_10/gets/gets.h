#ifndef N_10_GETS_H
#define N_10_GETS_H
#include "../types/types.h"
#include "../string/string.h"
#include "../configuration/configuration.h"

int get_equal(char*, char**, configuration);
int get_operator(char*, char**, int*, configuration);
int get_expression(char*, char**, configuration);
int get_var_binary_before(char*, char**, char**);
int get_var_binary_middle(char*, char**, char**);
int get_var_binary_after(char*, char**, char**);
int get_var_binary(char*, char**, char**, int);
int get_var_unary_before(char*, char**);
int get_var_unary_after(char*, char**);
int get_var_unary(char*, char**, int);
int get_var_save_result(char*, char**, configuration);

#endif // GETS_H


#endif //N_10_GETS_H
