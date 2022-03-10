#!/bin/bash

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}/dict/

# generate ROOT dictionary
echo "generating ROOT dictionaries..."
cd dict
# root 5
rootcint -f StlDict.cxx -c ../include/Stl.h ../include/LinkDef.h
# root 6
#rootcint -f StlDict.cxx -c ../include/Stl.h ../include/LinkDef.h

g++ -o libStlDict.so StlDict.cxx `root-config --cflags --libs` -shared -fPIC
cd ..
