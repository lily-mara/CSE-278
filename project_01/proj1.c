#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef enum { INT, FLOAT, TYPE_ERROR } type_t;
typedef enum { ADD, SUB, DIV, MULT, OP_ERROR } op_t;

bool valid_binary(const char*);
type_t parse_type_choice(const char*);
op_t parse_op_choice(const char*);
int power(int, int);
int bin_to_dec(char*);
bool is_whitespace(char);
char* trim_whitespace(char*);
char* get_str();
char* get_binary(char*);
type_t get_type();
op_t get_op();
void run_int(char*, char*, op_t);
void run_float(char*, char*, op_t);
int bin2int(char*);
float bin2float(char*);
void test_bin2int();

int main() {
	char *num1 = get_binary("first");
	char *num2 = get_binary("second");

	type_t number_format = get_type();
	op_t op = get_op();

	switch (number_format) {
		case INT:
			run_int(num1, num2, op);
			break;
		case FLOAT:
			run_float(num1, num2, op);
			break;
		case TYPE_ERROR:
			break;
	}

	free(num1);
	free(num2);

	printf("Goodbye!\n");
}


void test_bin2int() {
	assert(bin2int("00000000") == 0);
	assert(bin2int("01111111") == 127);
	assert(bin2int("01111110") == 126);
	assert(bin2int("00000010") == 2);
	assert(bin2int("00000001") == 1);
	assert(bin2int("00000000") == 0);
	assert(bin2int("11111111") == -1);
	assert(bin2int("11111110") == -2);
	assert(bin2int("10000010") == -126);
	assert(bin2int("10000001") == -127);
	assert(bin2int("10000000") == -128);
	assert(bin2int("11111111111111111111111111111111") == -1);
	assert(bin2int("11111111111111111111111111110100") == -12);
}

void run_int(char* str1, char* str2, op_t op) {
	int num1 = bin2int(str1);
	int num2 = bin2int(str2);

	float result;

	switch (op) {
		case ADD:
			result = num1 + num2;
			break;
		case SUB:
			result = num1 - num2;
			break;
		case MULT:
			result = num1 * num2;
			break;
		case DIV:
			result = num1 / num2;
			break;
		case OP_ERROR:
			break;
	}
}

void run_float(char* str1, char* str2, op_t op) {
}

int bin2int(char* input) {
	size_t bits = strlen(input);
	int result = 0;

	bool negative = input[0] == '1';
	char one = '1';
	if (negative) {
		one = '0';
	}

	for (int i = 0; i < bits; i++) {
		if (input[i] == one) {
			result += power(2, bits - i - 1);
		}
	}

	if (negative) {
		result *= -1;
		result -= 1;
	}

	return result;
}

float bin2float(char* input) {
	assert(strlen(input) == 32);
	return 0;
}

op_t get_op() {
	printf("Enter the calculation to perform (add, sub, mul, div):\n");
	char *op_str;

	op_str = get_str();
	op_t op;

	while ((op = parse_op_choice(op_str)) == OP_ERROR) {
		printf("Input <%s> is not a valid operator name\n", op_str);
		printf("Enter the calculation to perform (add, sub, mul, div):\n");

		free(op_str);
		op_str = get_str();
	}

	free(op_str);
	return op;
}

type_t get_type() {
	printf("Enter the binary numeric format (int or float)\n");
	char* type;

	type = get_str();

	while (parse_type_choice(type) == TYPE_ERROR) {
		printf("Input <%s> is not a valid numeric format\n", type);
		printf("Enter the binary numeric format (int or float)\n");
		free(type);
		type = get_str();
	}

	type_t return_type = parse_type_choice(type);
	free(type);

	return return_type;
}

char* get_binary(char *number) {
	printf("Enter the %s number in binary format:\n", number);
	char* num;

	num = get_str();

	while (!valid_binary(num)) {
		printf("Input <%s> is not a valid binary literal\n", num);
		printf("Enter the %s number in binary format:\n", number);
		free(num);
		num = get_str();
	}

	return num;
}

char* get_str() {
	char *buffer = NULL;
	char *output;
	size_t len;

	int read_status = getline(&buffer, &len, stdin);
	char *input = trim_whitespace(buffer);

	output = calloc(strlen(input) + 1, sizeof(char));
	strcpy(output, input);

	free(buffer);
	return output;
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

int power(int base, int power) {
	int total = 1;

	for (int i = 0; i < power; i++) {
		total *= base;
	}

	return total;
}

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trim_whitespace(char *str)
{
	char *end;

	// Trim leading space
	while(is_whitespace(*str)) {
		str++;
	}

	if(*str == 0) {  // All spaces?
		return str;
	}

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && is_whitespace(*end)) {
		end--;
	}

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

inline bool is_whitespace(char x) {
	return x == ' ' || x == '\n' || x == '\t';
}
