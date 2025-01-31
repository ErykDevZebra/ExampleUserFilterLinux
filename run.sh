#!/bin/bash

Executor_Path='/etc/avexecutor/bin/Console'

./build.sh

sleep 5 && firefox http://localhost:9090/ &

$Executor_Path ./avs/Program.avproj
