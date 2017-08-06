import re
import argparse

pattern = re.compile('INFO:root:(.*)')

def parse_times(log, function):
    times = []
    with open(log) as text:
        for line in text:
            times.append(function(line))
    return times;

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('numpp')
    parser.add_argument('other')
    parser.add_argument('--message', '-m', required=True,
        help='''What kind of log is being measured, e.g. compilation, runtime''')
    args = parser.parse_args()

    function = lambda line: float(pattern.findall(line)[0]) if args.message.upper() == 'COMPILATION' else float(line)

    numpp = parse_times(args.numpp, function)
    other = parse_times(args.other, function)

    print("-------------------")
    print("       NUMPP       ")
    print("-------------------\n")
    print("{:s} average time in nanoseconds: {:f}".format(args.message, sum(numpp)/len(numpp)))
    print("Based on {:d} cases\n".format(len(numpp)))
    print("-------------------")
    print("       OTHER       ")
    print("-------------------\n")
    print("{:s} average time in nanoseconds: {:f}".format(args.message, sum(other)/len(other)))
    print("Based on {:d} cases\n".format(len(other)))
