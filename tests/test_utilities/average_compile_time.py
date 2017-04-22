import re
import argparse

pattern = re.compile('INFO:root:(.*)')

def find_compilation_times(log):
    times = []
    for line in open(log):
        times.append(float(pattern.findall(line)[0]))
    return times;

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('numpp')
    parser.add_argument('other')
    args = parser.parse_args()

    numpp = find_compilation_times(args.numpp)
    other = find_compilation_times(args.other)
    print(sum(numpp)/len(numpp))
    print(sum(other)/len(other))
