#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "main.h"

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

float bin2float(const char *s) {
	int v;
	float f;
	unsigned i;
	char *p1 = (char*)&v, *p2 = (char*)&f;

	// Collect binary digits into an integer variable
	v = 0;
	for (i = 0; i < 32; i++) {
		v = (v << 1) + (s[i] - '0');
	}

	// Copy the bits from the integer variable to a float variable
	for (i = 0; i < sizeof(f); i++) {
		*p2++ = *p1++;
	}

	return f;
}

void run_int(const char* str1, const char* str2, op_t op) {
	int num1 = bin2int(str1);
	int num2 = bin2int(str2);

	int result;
	char op_char;

	switch (op) {
		case ADD:
			result = num1 + num2;
			op_char = '+';
			break;
		case SUB:
			result = num1 - num2;
			op_char = '-';
			break;
		case MULT:
			result = num1 * num2;
			op_char = '*';
			break;
		case DIV:
			result = num1 / num2;
			op_char = '/';
			break;
		case OP_ERROR:
			break;
			op_char = '#';
	}

	char *bin_result = int2bin(result);
	char *oct_result = bin2oct(bin_result);
	char *hex_result = bin2hex(bin_result);

	printf("The result for %d %c %d is:\n", num1, op_char, num2);
	printf("Binary = %s\n", bin_result);
	printf("Octal = %s\n", oct_result);
	printf("Decimal = %+d\n", result);
	printf("Hex = %s\n", hex_result);

	free(bin_result);
	free(hex_result);
	free(oct_result);
}

void run_float(const char* str1, const char* str2, op_t op) {
	float num1 = bin2float(str1);
	float num2 = bin2float(str2);

	float result;
	char op_char;

	switch (op) {
		case ADD:
			result = num1 + num2;
			op_char = '+';
			break;
		case SUB:
			result = num1 - num2;
			op_char = '-';
			break;
		case MULT:
			result = num1 * num2;
			op_char = '*';
			break;
		case DIV:
			result = num1 / num2;
			op_char = '/';
			break;
		case OP_ERROR:
			break;
			op_char = '#';
	}

	char *bin_result = float2bin(result);
	char *oct_result = bin2oct(bin_result);
	char *hex_result = bin2hex(bin_result);

	printf("The result for %f %c %f is:\n", num1, op_char, num2);
	printf("Binary = %s\n", bin_result);
	printf("Octal = %s\n", oct_result);
	printf("Decimal = %+f\n", result);
	printf("Hex = %s\n", hex_result);

	free(bin_result);
	free(hex_result);
	free(oct_result);
}

char *float2bin(float input) {
	char* bin = calloc(33, sizeof(char));
	bin[32] = '\0';

	int cheater = *((int*)((char*)&input));

	for (int i = 0; i < 32; i++) {
		int bit = (cheater >> (31-i)) & 1;
		if (bit) {
			bin[i] = '1';
		} else {
			bin[i] = '0';
		}
	}

	return bin;
}

char *int2bin(int input) {
	input = input >> (32 - sizeof(int)*8);
	char* result = calloc(33, sizeof(char));
	result[32] = 0;

	for (int i = 0; i < 32; i++) {
		int bit = (input >> (31-i)) & 1;
		if (bit) {
			result[i] = '1';
		} else {
			result[i] = '0';
		}
	}

	return result;
}

char *bin2hex(const char *input) {
	char *output = calloc(9, sizeof(char));
	output[8] = 0;
	unsigned int hexnum;
	char temp[4];

	for(int i = 0;i < 8;++i) {
		hexnum = 0;

		strncpy(temp, input + (i * 4), 4);
		for(int j = 0;j < 4;++j) {
			hexnum += (temp[j] - '0') << (3 - j);
		}

		sprintf(output + i, "%X", hexnum);
	}

	return output;
}

int bin2int(const char* input) {
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

char* get_binary(const char *number) {
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
	char *buffer = calloc(100, sizeof(char));
	char *output;

	scanf("%s", buffer);
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
char *trim_whitespace(char *str) {
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

char* bin2oct(const char *input) {
	size_t in_length = strlen(input);

	int extra_zeroes = 3-in_length%3;
	if (extra_zeroes == 3) {
		extra_zeroes = 0;
	}

	size_t bin_length = in_length + extra_zeroes;

	int out_length = bin_length/3;

	char* binary = calloc(bin_length+1, sizeof(char));
	char* out = calloc(out_length+1, sizeof(char));

	for (int i = 0; i < bin_length; i++) {
		if (i < extra_zeroes) {
			binary[i] = '0';
		} else {
			binary[i] = input[i-extra_zeroes];
		}
	}

	char* temp = calloc(4, sizeof(char));
	temp[3] = '\0';

	for (int i = 0; i < out_length; i++) {
		strncpy(temp, binary+i*3, 3);
		out[i] = oct2ascii(temp);
	}

	free(temp);
	free(binary);
	return out;
}

char oct2ascii(const char *binary) {
	if (!strcmp("000", binary))
		return '0';
	if (!strcmp("001", binary))
		return '1';
	if (!strcmp("010", binary))
		return '2';
	if (!strcmp("011", binary))
		return '3';
	if (!strcmp("100", binary))
		return '4';
	if (!strcmp("101", binary))
		return '5';
	if (!strcmp("110", binary))
		return '6';
	if (!strcmp("111", binary))
		return '7';
	return '-';
}
