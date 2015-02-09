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

	printf(" The starting memory address of the input is: %p\n", input);
	printf("The starting memory address of the output is: %p\n", output);
	printf("                    The results in octal are:__\n");

	free(buffer);
	return 0;
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
