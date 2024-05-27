#ifndef N_10_STRING_H
#define N_10_STRING_H

#include "../types/types.h"
#include <stdio.h>

int join_symb(char, char**, int*);
int get_str(char**, FILE*);
int get_str_with_comments(char**, FILE*, char, char, char, int*);
int token_count(char*);
int strip(char**);
int reverse(char**);
int split_space(char*, char***);
int char_to_str(int, char**);
int add_str(char**, int, ...);
int add_chr(char**, int, ...);
int to_str(int, char**);
int to_int(char*);
int is_empty_str(char*);


#endif //N_10_STRING_H
