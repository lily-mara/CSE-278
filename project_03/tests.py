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
			'num1': result_search.group('num1'),
			'num2': result_search.group('num2'),
		}
	except AttributeError:
		raise ValueError('Your output does not match requirements.\n' + out)


class TestConversion(TestCase):
	def test_positive_whole(self):
		num1 = '01000000001000000000000000000000'
		num2 = '01000000001000000000000000000000'
		operation = 'add'

		num1_expect = '2.5'
		num2_expect = '2.5'

		test_run = run(num1, num2, operation)
		num1_actual = test_run['num1']
		num2_actual = test_run['num2']

		self.assertEqual(num1_expect, num1_actual)
		self.assertEqual(num2_expect, num2_actual)


class TestOperation(TestCase):
	def get_op(self, operation):
		num = '01000000001000000000000000000000'
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
	def test_two_positive_addd(self):
		num1 = '00000000000000000000000001011111'
		num2 = '00000000000000000000000000110110'
		operation = 'add'
		expect = '00000000000000000000000010010101'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_positive_sub_negative_result(self):
		num1 = '00000000000000000000000000110110'
		num2 = '00000000000000000000000001011111'
		operation = 'sub'
		expect = '11111111111111111111111111010111'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_positive_mul(self):
		num1 = '00000000000000000000000000110110'
		num2 = '00000000000000000000000001011111'
		operation = 'mul'
		expect = '00000000000000000001010000001010'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_positive_div(self):
		num1 = '00000000000000000000000100101100'
		num2 = '00000000000000000000000000000101'
		operation = 'div'
		expect = '00000000000000000000000000111100'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_negative_add(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'add'
		expect = '11111111111111111111111111111010'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_negative_sub(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'sub'
		expect = '00000000000000000000000000000010'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_negative_mul(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'mul'
		expect = '00000000000000000000000000001000'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)

	def test_two_negative_div(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'div'
		expect = '00000000000000000000000000000001'

		actual = run(num1, num2, operation)['bin_result']
		self.assertEqual(actual, expect)


if __name__ == '__main__':
	main(argv=sys.argv[1:])
