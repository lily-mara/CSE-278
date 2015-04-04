# coding: utf-8
from unittest import TestCase, main
import subprocess
import re
import sys
from os import path

BIN_PATTERN = re.compile(r'\w+\s*=\s*(?P<bin>[10]+)')
OPERATION_PATTERN = re.compile(
	r"""
	result.*
	(?P<num1>-?[0-9]+)\s+
	(?P<op>[-/*+])\s+
	(?P<num2>-?[0-9]+)
	""",
	re.VERBOSE
)

FLT_MAX = 340282346638528859811704183484516925440.0
FLT_MIN = -340282346638528859811704183484516925440.0

NUMS = {
	FLT_MIN: '11111111011111111111111111111111',
	-6.25: '11000000110010000000000000000000',
	-5: '11000000101000000000000000000000',
	-3.5: '11000000011000000000000000000000',
	-2.5: '11000000001000000000000000000000',
	-1: '10111111100000000000000000000000',
	0: '00000000000000000000000000000000',
	1: '00111111100000000000000000000000',
	2.5: '01000000001000000000000000000000',
	3.5: '01000000011000000000000000000000',
	5: '01000000101000000000000000000000',
	6.25: '01000000110010000000000000000000',
	FLT_MAX: '01111111011111111111111111111111',
}

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
		return {
			'bin_result': bin_search.group('bin'),
			'operation': result_search.group('op'),
			'num1': float(result_search.group('num1')),
			'num2': float(result_search.group('num2')),
		}
	except AttributeError:
		raise ValueError('Your output does not match requirements.')


class TestConversion(TestCase):
	def get_nums(self, num1, num2):
		num1 = NUMS[num1]
		num2 = NUMS[num2]
		operation = 'add'

		test_run = run(num1, num2, operation)
		num1_actual = test_run['num1']
		num2_actual = test_run['num2']

		return num1_actual, num2_actual

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
		num = NUMS[2.5]
		return run(num, num, operation)['operation']

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
		num1 = NUMS[num1]
		num2 = NUMS[num2]

		result = run(num1, num2, op)
		return result['bin_result']

	def test_two_positive_add(self):
		actual = self.get_bin_result(2.5, 2.5, 'add')
		expect = NUMS[5]

		self.assertEqual(actual, expect)

	def test_two_positive_sub_negative_result(self):
		actual = self.get_bin_result(2.5, 3.5, 'sub')
		expect = NUMS[-1]

		self.assertEqual(actual, expect)

	def test_two_positive_mul(self):
		actual = self.get_bin_result(2.5, 2.5, 'mul')
		expect = NUMS[6.25]

		self.assertEqual(actual, expect)

	def test_two_positive_div(self):
		actual = self.get_bin_result(2.5, 2.5, 'div')
		expect = NUMS[1]

		self.assertEqual(actual, expect)

	def test_two_negative_add(self):
		actual = self.get_bin_result(-2.5, -2.5, 'add')
		expect = NUMS[-5]

		self.assertEqual(actual, expect)

	def test_two_negative_sub(self):
		actual = self.get_bin_result(-2.5, -2.5, 'sub')
		expect = NUMS[0]

		self.assertEqual(actual, expect)

	def test_two_negative_mul(self):
		actual = self.get_bin_result(-2.5, -2.5, 'mul')
		expect = NUMS[6.25]

		self.assertEqual(actual, expect)

	def test_two_negative_div(self):
		actual = self.get_bin_result(-2.5, -2.5, 'div')
		expect = NUMS[1]

		self.assertEqual(actual, expect)


if __name__ == '__main__':
	main(argv=sys.argv[1:])
