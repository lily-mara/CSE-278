#include <stdio.h>

int array[10];

int main() {
	int i;
	for (i = 0; i < 10; i++) {
		array[i] = 5*(i+1);
	}

	int sum = 0;
	for (i = 0; i < 10; i++) {
		sum += array[i];
	}

	printf("The sum is %d.\n", sum);

	return 0;
}
