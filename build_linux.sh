#!/bin/bash
set -e
pushd build

cp crunch/inc/crn_decomp.h crn_decomp.h
cp crunch/inc/crnlib.h crnlib.h
cp crunch/inc/crn_defs.h crn_defs.h

cp ../c_crunch_lib.cpp c_crunch_lib.cpp

g++ c_crunch_lib.cpp -c -Os --std=gnu++0x -fomit-frame-pointer -ffast-math -fno-math-errno -fno-strict-aliasing -fPIC -g -Wall -Wno-unused-value -Wno-unused -march=core2 -shared -o libcrndecomp-linux.so

g++ c_crunch_lib.cpp -c -Os --std=gnu++0x -fomit-frame-pointer -ffast-math -fno-math-errno -fno-strict-aliasing -g -Wall -Wno-unused-value -Wno-unused -march=core2 -o libcrndecomp-linux-static.o

ar rcs libcrndecomp-linux-static.a libcrndecomp-linux-static.o

cp libcrndecomp-linux.so ../

cp libcrndecomp-linux-static.a ../

popd
