#!/usr/bin/env bash
for value in {1..100}
do
    /usr/bin/time --format "%e" -o tests.txt -a build/ml
done
echo "all tests completed"