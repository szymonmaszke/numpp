#!usr/bin/python3
import argparse
from test_templates.test import run_test

parser = argparse.ArgumentParser(
    description='''
    Runs derivative tests instantiated from template\n
    ''')

parser.add_argument('--cases', '-c', required=True,
        help='How many tests should be run')

parser.add_argument('--template', '-t', required=True,
        help='Template from which tests will be initialized')

parser.add_argument('--expressions', '-e', required=True,
        help='''How many expressions should the function generate?
        See create_function.py for better understanding
        ''')

parser.add_argument('--low', '-nl', required=True,
        help='''Lower bound of generated numbers''')
parser.add_argument('--high', '-nh', required=True,
        help='''Upper bound of generated numbers''')
parser.add_argument('--arglow', '-al', required=True,
        help='''Lower bound of function argument ''')
parser.add_argument('--arghigh', '-ah', required=True,
        help='''Upper bound of function argument''')

args = parser.parse_args()
run_test(
        args,
        '#include"../../differentiation/forward.hpp"\n', 5,
        'gsl_deriv_forward (&F, ', 29,
        '''constexpr auto result_numpp =
        numpp::derivative::forward(numpp_function{}, ''', 37,
        9, 16,
        "./differentiation/log/forward/compile.log"
        )
