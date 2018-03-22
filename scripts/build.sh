#!/bin/bash
set -e
cd ./DNAI
$CMAKE_PREFIX_PATH/../../bin/qmake DNAI.pro;
make;
cd ../Server
$CMAKE_PREFIX_PATH/../../bin/qmake Server.pro;
make;
