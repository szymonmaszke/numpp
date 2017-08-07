#!/usr/bin/env bash

find ../ -type f -name 'temp*' -delete
find ../ -depth -type d -name 'log*' -exec rm -r {} +
find ../ -type f -name '*.o' -delete
find ../ -type f -name '*.out' -delete
