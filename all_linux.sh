#!/bin/bash
set -e

mkdir -p build && pushd build

git clone https://github.com/DaemonEngine/crunch.git

# 98c7429 2019-02-27
git checkout 98c7429

popd

./build_linux.sh

