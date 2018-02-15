#!/bin/sh

rm -rf Application
rm -rf DNAI-Installer.dmg

/Users/victorgouet/Qt/5.9.4/clang_64/bin/qmake ../../DNAI/DNAI.pro
make
#make install in ./
cd app/DNAI.app/Contents/MacOS/
mkdir settings
cd -
cp -rf ../../DNAI/app/settings/ ./app/DNAI.app/Contents/MacOS/settings

/Users/victorgouet/Qt/5.9.4/clang_64/bin/qmake ../../Server/Server.pro
make
cp Server app/DNAI.app/Contents/MacOS/

cd app/DNAI.app/Contents/MacOS/
mkdir Core
cd -

cp -rf ~/Documents/Rendu/Core/Duly/CoreDaemon/bin/Release/ ./app/DNAI.app/Contents/MacOS/Core/

cp /Library/Frameworks/Mono.framework/Commands/mono ./app/DNAI.app/Contents/MacOS/Core/

rm *.o
rm *.cpp
rm -rf lib/
rm *.h
rm Server
cp -rf app/DNAI.app ./
rm -rf app
rm Makefile

echo "----- Create depandancy framework -----"
sleep 1
/Users/victorgouet/Qt/5.9.4/clang_64/bin/macdeployqt DNAI.app -qmldir=/Users/victorgouet/Documents/DulyGUI/Duly-GUI/DNAI/app/resources/ -verbose=2
sleep 3

rm -rf Application
mkdir Application
mv -f DNAI.app Application
cd Application/DNAI.app/Contents/MacOS

echo "----- Setting Server -----\n\n"
sleep 1
otool -L Server
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ./Server
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Server
otool -L Server
cd -

sleep 3

echo "----- Generate DMG file -----\n\n"
sleep 1
sudo ./dmg-generator.sh

echo "----- SUCCESS -----"