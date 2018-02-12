cd ./Duly
$CMAKE_PREFIX_PATH/../../bin/qmake Duly.pro;
make;
cd ../Server
$CMAKE_PREFIX_PATH/../../bin/qmake Server.pro;
make;
