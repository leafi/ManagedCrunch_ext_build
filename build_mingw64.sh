#!/bin/bash
set -e
pushd build

cp crunch/inc/crn_decomp.h crn_decomp.h
cp crunch/inc/crnlib.h crnlib.h
cp crunch/inc/crn_defs.h crn_defs.h

cp ../c_crunch_lib.cpp c_crunch_lib.cpp

x86_64-w64-mingw32-g++ c_crunch_lib.cpp -c -Os --std=gnu++0x -fomit-frame-pointer -ffast-math -fno-math-errno -fno-strict-aliasing -fPIC -g -Wall -Wno-unused-value -Wno-unused -shared -o libcrndecomp.dll

x86_64-w64-mingw32-g++ c_crunch_lib.cpp -c -Os --std=gnu++0x -fomit-frame-pointer -ffast-math -fno-math-errno -fno-strict-aliasing -g -Wall -Wno-unused-value -Wno-unused -o crndecomp-mingw64-static.o

cp libcrndecomp.dll ../

cp crndecomp-mingw64-static.o ../

popd
