#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum { INT, FLOAT, TYPE_ERROR } type_t;
typedef enum { ADD, SUB, DIV, MULT, OP_ERROR } op_t;

bool valid_binary(const char*);
type_t parse_type_choice(const char*);
op_t parse_op_choice(const char*);
unsigned int power(int, int);
int bin_to_dec(char*);

int main() {
	char *input = "101000010010010";
	if (valid_binary(input)) {
		printf("Input <%s> is valid binary literal\n", input);
	} else {
		printf("Input <%s> is not a valid binary literal\n", input);
		return 1;
	}
}

/*
 * Ensures that the given string is a valid binary literal containing only the
 * characters '0' and '1'. Returns `true' if the string is a valid binary
 * literal, `false' otherwise.
 */
bool valid_binary(const char *to_check) {
	for (int i = 0; i < strlen(to_check); i++) {
		if (to_check[i] != '0' && to_check[i] != '1') {
			return false;
		}
	}
	return true;
}

/*
 * Parses a string and returns an enum variant of type ``type_t'' (INT, FLOAT,
 * TYPE_ERROR) depending on the contents.
 *
 * INT:
 * 		the string was the word `int'
 * FLOAT:
 * 		the string was the word `float'
 * TYPE_ERROR:
 * 		the string was not an expected type name
 */
type_t parse_type_choice(const char *to_check) {
	if (strcmp(to_check, "int") == 0) {
		return INT;
	} else if (strcmp(to_check, "float") == 0) {
		return FLOAT;
	}

	return TYPE_ERROR;
}

/*
 * Parses a string and returns an enum variant of type ``op_t'' (ADD, SUB, MULT,
 * DIV, OP_ERROR) depending on the contents.
 *
 * ADD:
 * 		the string was the word `add'
 * SUB:
 * 		the string was the word `sub'
 * MULT:
 * 		the string was the word `mul'
 * DIV:
 * 		the string was the word `div'
 * OP_ERROR:
 * 		the string was not an expected operator name
 */
op_t parse_op_choice(const char *to_check) {
	if (strcmp(to_check, "add") == 0) {
		return ADD;
	} else if (strcmp(to_check, "sub") == 0) {
		return SUB;
	} else if (strcmp(to_check, "mul") == 0) {
		return MULT;
	} else if (strcmp(to_check, "div") == 0) {
		return DIV;
	}

	return OP_ERROR;
}

int bin_to_dec(char *binary) {
	int sum = 0;

	for (int i = strlen(binary) - 1; i >= 0; i--) {
		if (binary[i] == '1') {
			sum += power(2, i);
		}
	}

	return sum;
}

unsigned int power(int base, int power) {
	int total = 1;

	for (int i = 0; i < power; i++) {
		total *= base;
	}

	return total;
}