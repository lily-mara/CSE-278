#include<stdio.h>

int year = 2020;
int calc_age(int);

int main() {
	int birth_year;

	printf("Enter the year you were born: ");
	scanf("%d", &birth_year);

	printf("In %d, you will be %d years old\n", year, calc_age(birth_year));
}

int calc_age(int birth_year) {
	return year - birth_year;
}
