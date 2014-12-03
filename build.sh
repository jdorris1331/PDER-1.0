#!/bin/bash
cd lib
make clean
make all
cd ../PDER
make clean
make all
./PDER
