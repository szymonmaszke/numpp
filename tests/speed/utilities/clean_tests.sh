#/bin/env bash

find ../ -type f -name 'temp*' -delete
find ../ -type f -name '*log*' -delete
find ../ -depth -type d -name 'log*' -exec rm -r {} +
find ../ -type f -name '*.o' -delete
