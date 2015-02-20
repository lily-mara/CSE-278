#ifndef _MAIN_H_
#define _MAIN_H_

#include<stdbool.h>
#include<string.h>
#include<assert.h>

typedef enum { INT, FLOAT, TYPE_ERROR } type_t;
typedef enum { ADD, SUB, DIV, MULT, OP_ERROR } op_t;

int power(int, int);
char* get_str();
bool is_whitespace(char);
op_t parse_op_choice(const char*);
type_t parse_type_choice(const char*);
char* trim_whitespace(char*);
bool valid_binary(const char*);

char* get_binary(const char*);
type_t get_type();
op_t get_op();

void run_int(const char*, const char*, op_t);
void run_float(const char*, const char*, op_t);

int bin2int(const char*);
float bin2float(const char*);
char* int2bin(int);
char* float2bin(float);
char* bin2hex(const char*);
char* bin2oct(const char*);
char oct2ascii(const char*);

void test_bin2int();
void test_int2bin();
void test_float2bin();
void test_bin2float();

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

void test_int2bin() {
	assert(strcmp("00000000000000000000000000000000", int2bin(0)) == 0);
	assert(strcmp("00000000000000000000000001111111", int2bin(127)) == 0);
	assert(strcmp("00000000000000000000000001111110", int2bin(126)) == 0);
	assert(strcmp("00000000000000000000000000000010", int2bin(2)) == 0);
	assert(strcmp("00000000000000000000000000000001", int2bin(1)) == 0);
	assert(strcmp("11111111111111111111111111111111", int2bin(-1)) == 0);
	assert(strcmp("11111111111111111111111111111110", int2bin(-2)) == 0);
	assert(strcmp("11111111111111111111111110000010", int2bin(-126)) == 0);
	assert(strcmp("11111111111111111111111110000001", int2bin(-127)) == 0);
	assert(strcmp("11111111111111111111111110000000", int2bin(-128)) == 0);
}

void test_bin2float() {
	assert(bin2float("01000000001000000000000000000000") == 2.5);
	assert(bin2float("01000000010010001111010111000010") == 3.14);
}

void test_float2bin() {
	assert(strcmp(float2bin(2.5), "01000000001000000000000000000000") == 0);
	assert(strcmp(float2bin(3.14), "01000000010010001111010111000010") == 0);
}

#endif
