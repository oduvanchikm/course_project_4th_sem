#ifndef N_10_CONFIGURATION_H
#define N_10_CONFIGURATION_H

#include "../types/types.h"
#include "../string/string.h"

int find_instruction(char*, instruction*);
int check_config(configuration);
int fill_instructions(char*, configuration*, int*);
void free_configuration(configuration*);
void output_instructions(instruction*);


#endif //N_10_CONFIGURATION_H
