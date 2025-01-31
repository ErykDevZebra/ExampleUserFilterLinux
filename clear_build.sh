#!/bin/bash

cd build

if [ -e Makefile ]
then
    make clear
fi
