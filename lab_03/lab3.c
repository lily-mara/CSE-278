#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char** split(char*, char);
bool valid_binary(const char*);

int main() {
	char *input;
	char **output;

	//printf("The starting memory address of the input is:__\n");
	//printf("The starting memory address of the output is:__\n");
	//printf("The results in octal are:__\n");

	char *test_string = "hello how are you doing today?";
	char **splitted = split(test_string, ' ');

	for (int i = 0; i < 6; i++) {
		printf("splitted[%d] = %s\n", i, splitted[i]);
		free(splitted[i]);
	}

	free(splitted);

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

char** split(char* input, char splitter) {
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

	return output;
}
