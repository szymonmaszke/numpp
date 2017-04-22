#!/bin/env bash

TESTS_FAILED=$(grep '.*FAILED.*' $1 | wc -l)
TESTS_PASSED=$(grep '.*passed.*' $1 | wc -l)
if (($(bc -l <<< "$TESTS_FAILED/$TESTS_PASSED > $2")))
then
  exit 1
fi
