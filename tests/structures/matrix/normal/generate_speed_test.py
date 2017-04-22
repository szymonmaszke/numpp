#!usr/bin/python3
import random
import subprocess
import argparse
import logging
import time

def create_random_numbers(string, placement, size, range_low, range_high):
    for i in range(0, size-1):
        string[placement] += ','
        string[placement] += str(round(random.uniform(range_low, range_high), 4))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='''
        Runs matrix multiplication tests against Eigen
        ''')

    parser.add_argument('--cases', '-c', type=int, required=True,
            help='How many tests should be run')
    parser.add_argument('--size', '-s', type=int, required=True,
            help='Size of the matrix')

    parser.add_argument('--low', '-al', type=int, required=True,
            help='''Lower bound of generated numbers''')
    parser.add_argument('--high', '-ah', type=int, required=True,
            help='''Upper bound of generated numbers''')

    parser.add_argument('--template', '-t', required=True,
            help='Template from which the test should be instantiated')
    parser.add_argument('--log', '-l', required=True,
            help='''Location and name of the log file''')
    parser.add_argument('--depth', '-d', type=int, default=900,
            help='''Upper bound of generated numbers''')

    args = parser.parse_args()
    logging.basicConfig(filename=args.log,level=logging.DEBUG)

    for i in range(0, args.cases):
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
                "-ftemplate-depth=" + str(args.depth),
                "./temp_test.cpp",
                "-o", "./temp_test"])
            compilation_end = time.process_time()
            if compilation_status.returncode == 0:
                logging.info(compilation_end - compilation_start)
                test_status = subprocess.run(["./temp_test"])


