#ifndef N_10_OPERATIONS_H
#define N_10_OPERATIONS_H

#include "../types/types.h"
#include "../gets/gets.h"
#include "../variables/variables.h"
#include "../configuration/configuration.h"

#define COUNT_OP 7

typedef int (*operation)(int, int);

int to_10(char*, int, int*); // (str_num, base_str_num, res)
int to_base(int, int, char**); // (num, base, res)
int input(int, int*);
int _add_(int, int);
int _mult_(int, int);
int _sub_(int, int);
int _pow_(int, int);
int _div_(int, int);
int _rem_(int, int);
int _xor_(int, int);
int execute_operation(char*, int, int, int*, configuration);
int execute_instruction(char*, int*, array_variables, configuration);

#endif //N_10_OPERATIONS_H
