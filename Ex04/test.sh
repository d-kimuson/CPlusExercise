#!/bin/sh

# Usage
# 1. COPY this script into Ex0X Dir.
# 2. RUN chmod a+x test.sh
# 3. INPUT RUN script into RUN_EXERCISE_SCRIPT like "./a.out"
# 4. ./test.sh: if there is no outputs => Success!!

alias COMPILE="make"
alias RUN="./ex04 < list4.txt"
RESULT_SCRIPT="result4.txt"

# RUN TEST
if test -e "tmp.txt"; then
  \rm tmp.txt
fi

COMPILE && RUN > tmp.txt && diff -y --suppress-common-lines tmp.txt ${RESULT_SCRIPT}