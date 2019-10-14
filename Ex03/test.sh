#!/bin/sh

# Usage
# 1. COPY this script into Ex0X Dir.
# 2. RUN chmod a+x test.sh
# 3.

if test -e "tmp.txt"; then
  \rm tmp.txt
fi

alias RUN_EXERCISE_SCRIPT="./a.out < list3.txt"  # sample for ex03

g++ ex03.cc && RUN_EXERCISE_SCRIPT > tmp.txt && diff tmp.txt result3.txt