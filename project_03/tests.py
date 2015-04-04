# coding: utf-8
from unittest import TestCase, main
import subprocess
import re
import sys
from os import path
import struct
from collections import namedtuple

BIN_PATTERN = re.compile(r'\w+\s*=\s*(?P<bin>[10]+)')
OPERATION_PATTERN = re.compile(
	r"""
	result.*
	(?P<num1>-?[0-9]+\.[0-9]+)\s+
	(?P<op>[-/*+])\s+
	(?P<num2>-?[0-9]+\.[0-9]+)
	""",
	re.VERBOSE
)

FLT_MAX = 340282346638528859811704183484516925440.0
FLT_MIN = -340282346638528859811704183484516925440.0

Result = namedtuple('Result', 'bin op nums')


def to_bin(num):
	bin_num = str(bin(struct.unpack('L', struct.pack('f', num))[0]))[2:]
	for _ in range(0, 32 - len(bin_num)):
		bin_num = '0' + bin_num

	assert len(bin_num) == 32
	return bin_num


if len(sys.argv) < 2:
	print('You must provide an executable on as the first argument')
	sys.exit(1)

if not path.exists(sys.argv[1]):
	print('The executable provided as an argument must be a file that exists.')
	sys.exit(1)


def run(num1, num2, operation):
	p = subprocess.Popen(
		sys.argv[1],
		stdout=subprocess.PIPE,
		stderr=subprocess.STDOUT,
		stdin=subprocess.PIPE,
		bufsize=0
	)

	p.stdin.write('{}\n{}\n{}\n'.format(num1, num2, operation))

	out, err = p.communicate()
	bin_search = BIN_PATTERN.search(out)
	result_search = OPERATION_PATTERN.search(out)

	try:
		return Result(
			bin_search.group('bin'),
			result_search.group('op'),
			(
				float(result_search.group('num1')),
				float(result_search.group('num2')),
			),
		)
	except AttributeError:
		raise ValueError('Your output does not match requirements.')


class TestConversion(TestCase):
	def get_nums(self, num1, num2):
		num1 = to_bin(num1)
		num2 = to_bin(num2)
		operation = 'add'

		test_run = run(num1, num2, operation)

		return test_run.nums

	def test_convert_positive_whole(self):
		num1, num2 = self.get_nums(5, 5)

		self.assertEqual(num1, 5.0)
		self.assertEqual(num2, 5.0)

	def test_convert_negative_whole(self):
		num1, num2 = self.get_nums(-5, -5)

		self.assertEqual(num1, -5.0)
		self.assertEqual(num2, -5.0)

	def test_convert_positive_with_decimal(self):
		num1, num2 = self.get_nums(2.5, 2.5)

		self.assertEqual(num1, 2.5)
		self.assertEqual(num2, 2.5)

	def test_convert_negative_with_decimal(self):
		num1, num2 = self.get_nums(-2.5, -2.5)

		self.assertEqual(num1, -2.5)
		self.assertEqual(num2, -2.5)

	def test_convert_min(self):
		num = FLT_MIN
		num1, num2 = self.get_nums(num, num)

		self.assertEqual(num1, num)
		self.assertEqual(num2, num)

	def test_convert_max(self):
		num = FLT_MAX
		num1, num2 = self.get_nums(num, num)

		self.assertEqual(num1, num)
		self.assertEqual(num2, num)


class TestOperation(TestCase):
	def get_op(self, operation):
		num = to_bin(2.5)
		return run(num, num, operation).op

	def test_add(self):
		self.assertEqual(self.get_op('add'), '+')

	def test_sub(self):
		self.assertEqual(self.get_op('sub'), '-')

	def test_mul(self):
		self.assertEqual(self.get_op('mul'), '*')

	def test_div(self):
		self.assertEqual(self.get_op('div'), '/')


class TestResults(TestCase):
	def get_bin_result(self, num1, num2, op):
		num1 = to_bin(num1)
		num2 = to_bin(num2)

		result = run(num1, num2, op)
		return result.bin

	def test_two_positive_add(self):
		actual = self.get_bin_result(2.5, 2.5, 'add')
		expect = to_bin(5)

		self.assertEqual(actual, expect)

	def test_two_positive_sub_negative_result(self):
		actual = self.get_bin_result(2.5, 3.5, 'sub')
		expect = to_bin(-1)

		self.assertEqual(actual, expect)

	def test_two_positive_mul(self):
		actual = self.get_bin_result(2.5, 2.5, 'mul')
		expect = to_bin(6.25)

		self.assertEqual(actual, expect)

	def test_two_positive_div(self):
		actual = self.get_bin_result(2.5, 2.5, 'div')
		expect = to_bin(1)

		self.assertEqual(actual, expect)

	def test_two_negative_add(self):
		actual = self.get_bin_result(-2.5, -2.5, 'add')
		expect = to_bin(-5)

		self.assertEqual(actual, expect)

	def test_two_negative_sub(self):
		actual = self.get_bin_result(-2.5, -2.5, 'sub')
		expect = to_bin(0)

		self.assertEqual(actual, expect)

	def test_two_negative_mul(self):
		actual = self.get_bin_result(-2.5, -2.5, 'mul')
		expect = to_bin(6.25)

		self.assertEqual(actual, expect)

	def test_two_negative_div(self):
		actual = self.get_bin_result(-2.5, -2.5, 'div')
		expect = to_bin(1)

		self.assertEqual(actual, expect)

	def test_two_large_positive_add(self):
		actual = self.get_bin_result(10000, 10000, 'add')
		expect = to_bin(20000)

		self.assertEqual(actual, expect)

	def test_two_large_positive_sub(self):
		actual = self.get_bin_result(10000, 20, 'sub')
		expect = to_bin(9980)

		self.assertEqual(actual, expect)

	def test_two_large_positive_mul(self):
		actual = self.get_bin_result(10000, 20, 'mul')
		expect = to_bin(200000)

		self.assertEqual(actual, expect)

	def test_two_large_positive_div(self):
		actual = self.get_bin_result(10000, 20, 'div')
		expect = to_bin(500)

		self.assertEqual(actual, expect)

	def test_max_sub(self):
		actual = self.get_bin_result(FLT_MAX, FLT_MAX, 'sub')
		expect = to_bin(0)

		self.assertEqual(actual, expect)

	def test_max_min_add(self):
		actual = self.get_bin_result(FLT_MAX, FLT_MIN, 'add')
		expect = to_bin(0)

		self.assertEqual(actual, expect)

	def test_max_min_div(self):
		actual = self.get_bin_result(FLT_MAX, FLT_MIN, 'div')
		expect = to_bin(-1)

		self.assertEqual(actual, expect)


if __name__ == '__main__':
	main(argv=sys.argv[1:])
