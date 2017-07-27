#!usr/bin/python3
import sys
import random
import subprocess
import argparse
import logging
import time

def create_random_numbers(string, placement, size, range_low, range_high):
    for i in range(0, size-1):
        string[placement] += ','
        string[placement] += str(round(random.uniform(range_low, range_high), 4))

def create_rows(rows, string, placement, size, range_low, rnage_high):
    for i in range(0, rows):
        string[placement] += '{'
        string[placement] += '}'


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='''
        Runs sparse matrix multiplication tests
        ''')

    parser.add_argument('--cases', '-c', type=int, required=True,
            help='How many tests should be run')
    parser.add_argument('--size', '-s', type=int, required=True,
            help='Size of the matrix')

    parser.add_argument('--block', '-b', type=int, required=True,
            help='Minimal size of every generated values block')

    parser.add_argument('--density', '-d', type=float, required=True,
            help='Density of the created matrix in percentage (e.g. 0.1 for 10%)')

    parser.add_argument('--low', '-al', type=int, required=True,
            help='''Lower bound of generated numbers''')

    parser.add_argument('--high', '-ah', type=int, required=True,
            help='''Upper bound of generated numbers''')

    parser.add_argument('--template', '-t', required=True,
            help='Template from which the test should be instantiated')

    parser.add_argument('--log', '-l', required=True,
            help='''Location and name of the log file''')

    args = parser.parse_args()
    logging.basicConfig(filename=args.log,level=logging.DEBUG)

    non_zero_elements = int(args.size*args.size*args.density)
    block_count = int(non_zero_elements/args.block)

    if block_count < 1:
        print('Number of created blocks less than zero')
        print('At least one block has to be created for the test to run')
    if block_count < sqrt(args.size)

    for i in range(0, args.cases):
        print('Running test: ' + str(i) + '/' + str(args.cases), end='\r', file=sys.stderr)
        with open(args.template, "r") as template:
            template_content=template.readlines()

            create_random_numbers(template_content, 9, args.size, args.low,
                args.high)
            create_random_numbers(template_content, 14, args.size, args.low,
                args.high)

            with open("./temp_test.cpp", "w+") as test:
                test.writelines(template_content)
            compilation_start = time.process_time()
            compilation_status = subprocess.run([
                "g++", "-std=c++17", "-O3", "-march=native",
                "./temp_test.cpp",
                "-o", "./temp_test"])
            compilation_end = time.process_time()
            if compilation_status.returncode == 0:
                logging.info(compilation_end - compilation_start)
                test_status = subprocess.run(["./temp_test"])
