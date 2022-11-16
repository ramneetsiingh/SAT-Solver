#!/bin/bash
make clean
make

./pa1 < test/$1.in >test/test_your.out
diff test/$1.out test/test_your.out
