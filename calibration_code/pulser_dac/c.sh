#!/bin/bash

g++ -std=c++11 -o main dac_calibration.cpp -I${ROOTSYS}/include $(root-config --glibs)

