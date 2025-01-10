#!/bin/bash

cd build

cmake .
cmake --build . --parallel 8
