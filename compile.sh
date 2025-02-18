#!/bin/bash

python3 prep.py

cd /media/nando/DATAS/Art/Math/Engine/c/cmake

cmake -DCMAKE_BUILD_TYPE=Debug ..
make

#./Engine

