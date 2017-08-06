import argparse
import sys

def parse_success(log, pattern_success, pattern_failure):
    success, failure = 0, 0
    with open(log) as text:
        for line in text:
            success += line.count(pattern_success)
            failure += line.count(pattern_failure)
    return success, failure;

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('target', type=float)
    parser.add_argument('--log', '-l', required=True,
        help='''Log from which the success rate will be measured''')
    parser.add_argument('--message', '-m', required=True,
        help='''What are we testing?''')
    args = parser.parse_args()

    success, failure = parse_success(args.log, 'passed', 'FAILED')

    print("---------------------")
    print("       SUMMARY       ")
    print("---------------------\n")
    print("Tests topic: {:s}".format(args.message))
    print("\nTests passed: {:d}/{:d}".format(success, success+failure))
    print("In percentage: {:.6%}".format(success/(success+failure)))
    if args.target < (success/(success+failure)):
        print("\nTarget {:f} reached, enough tests passed.\n".format(args.target))
        sys.exit(0)
    else:
        print("""\nERROR: Target {:f} not acquired, not enough tests
                passed.\n""".format(args.target))
        sys.exit(1)

