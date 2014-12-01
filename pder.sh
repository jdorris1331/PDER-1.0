#!/bin/bash
cd lib
make clean
make all
cd ../example
make clean
make all
./example1
