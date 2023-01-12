#!/bin/bash

mkdir build
cd build
cmake ../
make

./SAT < ../test/$1.in >  ../test/test_your.out
diff ../test/$1.out ../test/test_your.out
