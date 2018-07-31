#!/bin/bash
set -e
cd ./Gui
$CMAKE_PREFIX_PATH/../../bin/qmake DNAI.pro;
make -j 8;
cd ../Server
$CMAKE_PREFIX_PATH/../../bin/qmake Server.pro;
make -j 8;
