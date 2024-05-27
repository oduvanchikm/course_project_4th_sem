#ifndef N_10_CHECK_H
#define N_10_CHECK_H
#include "../types/types.h"
#include "../string/string.h"
#include "../gets/gets.h"
#include "../configuration/configuration.h"

int check_number_notation(char*, int);
int check_name_var(char*);
int check_binary_before(char*, char*);
int check_binary_middle(char*, char*);
int check_binary_after(char*, char*);
int check_unary_before(char*, char*);
int check_unary_after(char*, char*);
int check_binary(char*, char*, int);
int check_unary(char*, char*, int);
int check_save_result(char*, char*, configuration);
int check_instruction(char*, configuration);


#endif //N_10_CHECK_H
