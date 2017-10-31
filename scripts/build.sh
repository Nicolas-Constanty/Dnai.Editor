cd ./Duly-GUI/Duly/;
$CMAKE_PREFIX_PATH/../../bin/qmake Duly.pro;
make;
cd ./lib/EventClient
$CMAKE_PREFIX_PATH/../../bin/qmake EventClient.pro;
make;
cd ../../Server;
$CMAKE_PREFIX_PATH/../../bin/qmake Server.pro;
make;
