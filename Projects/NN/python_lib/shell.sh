#!/bin/bash

set -e

source .venv/bin/activate

cd python_lib

rm -rf build

mkdir build
cd build

cmake .. -DPython3_EXECUTABLE=$(which python3)
make -j$(nproc)

cd ..

pip install .

cd ..

pip install pybind11-stubgen
pybind11-stubgen NN

mv stubs/NN.pyi .venv/lib/python3.14/site-packages/
rm -rf stubs/