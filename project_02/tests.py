from unittest import TestCase, main
import subprocess
import re
import sys
from os import path

NUM_PATTERN = re.compile(r'\w+\s*=\s*(?P<num>[10]+)')

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
	search = NUM_PATTERN.search(out)
	return search.group('num')


class TestStuff(TestCase):
	def test_two_positive_addd(self):
		num1 = '00000000000000000000000001011111'
		num2 = '00000000000000000000000000110110'
		operation = 'add'
		expect = '00000000000000000000000010010101'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_positive_sub_negative_result(self):
		num1 = '00000000000000000000000000110110'
		num2 = '00000000000000000000000001011111'
		operation = 'sub'
		expect = '11111111111111111111111111010111'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_positive_mul(self):
		num1 = '00000000000000000000000000110110'
		num2 = '00000000000000000000000001011111'
		operation = 'mul'
		expect = '00000000000000000001010000001010'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_positive_div(self):
		num1 = '00000000000000000000000100101100'
		num2 = '00000000000000000000000000000101'
		operation = 'div'
		expect = '00000000000000000000000000111100'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_negative_add(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'add'
		expect = '11111111111111111111111111111010'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_negative_sub(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'sub'
		expect = '00000000000000000000000000000010'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_negative_mul(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'mul'
		expect = '00000000000000000000000000001000'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)

	def test_two_negative_div(self):
		num1 = '11111111111111111111111111111110'
		num2 = '11111111111111111111111111111100'
		operation = 'div'
		expect = '00000000000000000000000000000001'

		actual = run(num1, num2, operation)
		self.assertEqual(actual, expect)


if __name__ == '__main__':
	main(argv=sys.argv[1:])
