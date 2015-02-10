#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
	int num_splits;
	char** array;
} split_t;

split_t *split(char*, char);
bool valid_binary(const char*);
char* trim_whitespace(char*);
bool is_whitespace(char);
void convert_to_octal(char**, char**);
char* to_octal(const char*);
char to_decimal(char*);

int main() {
	char **output;

	printf("Enter two binary strings to convert:\n");

	char *buffer = NULL;
	int read_status;
	size_t len;

	read_status = getline(&buffer, &len, stdin);
	char *input = trim_whitespace(buffer);

	split_t *binary_nums = split(input, ' ');

	for (int i = 0; i < binary_nums->num_splits; i++) {
		if (!valid_binary(binary_nums->array[i])) {
			printf("Input <%s> is not a valid binary literal\n", binary_nums->array[i]);
			return 1;
		}
	}

	convert_to_octal(binary_nums->array, output);

	//printf(" The starting memory address of the input is: %p\n", buffer);
	//printf("The starting memory address of the output is: %p\n", output);
	printf("                    The results in octal are: %s\n", *output);

	for (int i = 0; i < binary_nums->num_splits; i++) {
		free(output[i]);
		free(binary_nums->array[i]);
	}

	free(buffer);
	free(binary_nums->array);
	free(binary_nums);

	return 0;
}

void convert_to_octal(char *input[2], char** output) {
	for (int i = 0; i < 2; i++) {
		output[i] = to_octal(input[i]);
	}
}

char* to_octal(const char *input) {
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
		out[i] = to_decimal(temp);
	}

	free(temp);
	free(binary);
	return out;
}

char to_decimal(char *binary) {
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

bool valid_binary(const char *to_check) {
	for (int i = 0; i < strlen(to_check); i++) {
		if (to_check[i] != '0' && to_check[i] != '1') {
			return false;
		}
	}
	return true;
}

split_t* split(char* input, char splitter) {
	int count = 0;
	int input_size = strlen(input);

	for (int i = 0; i < input_size; i++) {
		if (input[i] == splitter) {
			count++;
		}
	}

	int output_size = count + 1;
	char **output = calloc(output_size, sizeof(char*));

	for (int i = 0; i < output_size; i++) {
		output[i] = calloc(input_size, sizeof(char));
	}

	int outer_index = 0;
	int inner_index = 0;

	for (int i = 0; i < input_size; i++) {

		if (input[i] == splitter) {
			output[outer_index][inner_index] = '\0';
			outer_index++;
			inner_index = 0;
		} else {
			output[outer_index][inner_index] = input[i];
			inner_index++;
		}
	}

	split_t *output_split = (split_t*) calloc(1, sizeof(split_t));
	output_split->num_splits = output_size;
	output_split->array = output;

	return output_split;
}

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
