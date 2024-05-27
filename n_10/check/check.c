#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "check.h"

int check_number_notation(char *number, int notation) {
	char *ptr = number - 1;
	int tmp = 0;

	while (*++ptr) {
		tmp = isdigit(*ptr) ? *ptr - '0' : toupper(*ptr) - 'A' + 10;

		if (tmp >= notation) {
			return 0;
		}
	}

	return 1;
}

int check_name_var(char *name) {
	int count_letters = 0;

	if (name) {
		if (isdigit(*name)) {
			return 0;
		}

		char *ptr = name - 1;

		while (*++ptr) {
			if (!isalnum(*ptr) && *ptr != '_') {
				return 0;
			}
			if (isalpha(*ptr)) {
				count_letters++;
			}
		}
	}

	return count_letters > 0;
}

int check_binary_before(char *expression, char *operator) {
	char *ptr = expression;
	char *token = NULL;
	int tmp_size = 0;
	int exit_code = 0;

	if (*ptr != '(' || !strstr(expression, operator)) {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ',') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr) && *ptr != ',') {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ')') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	if (*ptr != ')') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	return strcmp(ptr, operator) == 0 ? SUCCESS : INVALID_INSTRUCTION;
}

int check_binary_middle(char *expression, char *operator) {
	char *ptr = expression;
	char *token = NULL;
	int tmp_size = 0;
	int exit_code = 0;

	if (token_count(expression) != 3 || !strstr(expression, operator)) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr)) {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr)) {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (strcmp(token, operator) != 0) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr)) {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	return SUCCESS;
}

int check_binary_after(char *expression, char *operator) {
	char *ptr = expression;
	char *token = NULL;
	int tmp_size = 0;
	int exit_code = 0;

	if (!strstr(expression, operator)) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != '(') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (strcmp(token, operator) != 0) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	if (*ptr != '(') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ',') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && *ptr != ',') {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ')') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (*ptr != ')') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	return !*ptr ? SUCCESS : INVALID_INSTRUCTION;
}

int check_unary_before(char *expression, char *operator) {
	char *ptr = expression;
	char *token = NULL;
	int tmp_size = 0;
	int exit_code = 0;

	if (*ptr != '(' || !strstr(expression, operator)) {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ')') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	if (*ptr != ')') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	return strcmp(ptr, operator) == 0 ? SUCCESS : INVALID_INSTRUCTION;
}

int check_unary_after(char *expression, char *operator) {
	char *ptr = expression;
	char *token = NULL;
	int tmp_size = 0;
	int exit_code = 0;

	if (!strstr(expression, operator)) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != '(') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (strcmp(token, operator) != 0) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	if (*ptr != '(') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (!*ptr) {
		return INVALID_INSTRUCTION;
	}

	while (*ptr && !isspace(*ptr) && *ptr != ')') {
		if ((exit_code = join_symb(*ptr, &token, &tmp_size)) != SUCCESS) {
			if (token) {
				free(token);
			}

			return exit_code;
		}

		ptr++;
	}

	if (!token) {
		return INVALID_INSTRUCTION;
	}

	if (!*ptr) {
		if (token) {
			free(token);
		}

		return INVALID_INSTRUCTION;
	}

	if (!check_name_var(token)) {
		free(token);

		return INVALID_INSTRUCTION;
	}

	free(token);
	token = NULL;
	tmp_size = 0;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	if (*ptr != ')') {
		return INVALID_INSTRUCTION;
	}

	ptr++;

	while (*ptr && isspace(*ptr)) {
		ptr++;
	}

	return !*ptr ? SUCCESS : INVALID_INSTRUCTION;
}


int check_binary(char *expression, char *operator, int location) {
	switch (location) {
		case BEFORE_OPERATOR: return check_binary_before(expression, operator);
		case IN_MIDDLE: return check_binary_middle(expression, operator);
		case AFTER_OPERATOR: return check_binary_after(expression, operator);
		default: break;
	}

	return SUCCESS;
}

int check_unary(char *expression, char *operator, int location) {
	switch (location) {
		case BEFORE_OPERATOR: return check_unary_before(expression, operator);
		case AFTER_OPERATOR: return check_unary_after(expression, operator);
		default: break;
	}

	return SUCCESS;
}

int check_save_result(char *str, char *equal, configuration config) {
	char *pos_instruction = NULL;
	char *pos_equal = strstr(str, equal);

	for (int i = 0; i < COUNT_INSTRUCTIONS; i++) {
		if (!(pos_instruction = strstr(str, config.instructions[i].original_name))) {
			if (config.instructions[i].synonym_name) {
				pos_instruction = strstr(str, config.instructions[i].synonym_name);
			} else {
				pos_instruction = NULL;
			}
		}

		if (pos_instruction) {
			if (config.save_result == LEFT) {
				if (pos_instruction - pos_equal < 0) {
					return INVALID_INSTRUCTION;
				} else {
					return SUCCESS;
				}
			}
			if (config.save_result == RIGHT) {
				if (pos_instruction - pos_equal > 0) {
					return INVALID_INSTRUCTION;
				} else {
					return SUCCESS;
				}
			}
		}

		pos_instruction = NULL;
	}

	return INVALID_INSTRUCTION;
}

int check_instruction(char *str, configuration config) {
	char *operator = NULL;
	char *expression = NULL;
	int is_binary = 0;
	int location = 0;
	int exit_code = 0;
	char *equal = NULL;

	if ((exit_code = get_equal(str, &equal, config)) != SUCCESS) {
		return exit_code;
	}

	if (equal) {
		if ((exit_code = check_save_result(str, equal, config)) != SUCCESS) {
			if (equal) {
				free(equal);
			}

			return exit_code;
		}
	}

	if ((exit_code = get_expression(str, &expression, config)) != SUCCESS) {
		if (equal) {
			free(equal);
		}

		return exit_code;
	}

	if ((exit_code = get_operator(expression, &operator, &is_binary, config)) != SUCCESS) {
		if (equal) {
			free(equal);
		}
		free(expression);

		return exit_code;
	}

	if (!equal) {
		if (!(strcmp(operator, "input") == 0 ||
			  strcmp(operator, "output") == 0 ||
			  strcmp(operator, config.instructions[find_instruction("input", config.instructions)].synonym_name) == 0 ||
			  strcmp(operator, config.instructions[find_instruction("output", config.instructions)].synonym_name) == 0)) {
			free(expression);
			free(operator);

			return INVALID_INSTRUCTION;
		}
	}

	if (equal) {
		if (strcmp(operator, equal) == 0 ||
			strcmp(operator, "=") == 0 ||
			strcmp(operator, "input") == 0 ||
			strcmp(operator, "output") == 0 ||
			strcmp(operator, config.instructions[find_instruction("input", config.instructions)].synonym_name) == 0 ||
			strcmp(operator, config.instructions[find_instruction("output", config.instructions)].synonym_name) == 0) {
			free(equal);
			free(expression);
			free(operator);

			return INVALID_INSTRUCTION;
		}
	}

	location = is_binary ? config.location_binary : config.location_unary;

	switch (is_binary) {
		case 0:
			exit_code = check_unary(expression, operator, location);
			break;
		case 1:
			exit_code = check_binary(expression, operator, location);
			break;
		default:
			break;
	}

	if (equal) {
		free(equal);
	}
	free(operator);
	free(expression);

	return exit_code;
}