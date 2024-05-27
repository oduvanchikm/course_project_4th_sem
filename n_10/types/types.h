#ifndef N_10_TYPES_H
#define N_10_TYPES_H
#define COUNT_INSTRUCTIONS 10

enum ERRORS {
    SUCCESS 					= -1,
    NO_MEMORY 					= -2,
    INVALID_MULTILINE_COMMENT 	= -3,
    CANT_OPEN_FILE 				= -4,
    INVALID_INSTRUCTION 		= -5,
    HAVENT_VAR					= -6,
    HAVENT_OPERATOR				= -7,
    DIVISION_BY_ZERO			= -8,
    INVALID_NUMBER 				= -9,
    INVALID_NOTATION			= -10,
    INVALID_COUNT_ARGS			= -11
};

enum SAVE_RESULTS {
    LEFT,		// Var = add(Smth,OtheR);
    RIGHT 		// add(Smth,OtheR) = Var;
};

enum MUTUAL_LOCATION {
    BEFORE_OPERATOR, 	// ()op
    IN_MIDDLE,			// (op)
    AFTER_OPERATOR 		// op()
};

enum CODE_EXECUTE {
    INPUT,
    OUTPUT
};

typedef struct {
    char *original_name;
    char *synonym_name;
    int is_binary;
} instruction;

typedef struct {
    int save_result;
    int location_unary;
    int location_binary;
    instruction *instructions;
} configuration;

typedef struct {
    char *name;
    int value;
} variable;

typedef struct {
    variable *vars;
    int current_size;
    int size;
} array_variables;

#endif //N_10_TYPES_H
