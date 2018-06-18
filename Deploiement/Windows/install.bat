set QT_DIR=C:\Qt\5.10.1\msvc2017_64
set PATH=%QT_DIR%\bin;%PATH%
set PATH=C:\Qt\Tools\QtCreator\bin;%PATH%

rmdir /s DNAI
rmdir /s "C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data"
md "C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data"

qmake.exe C:\Users\Victor\Documents\EIP\Duly-GUI\Gui\DNAI.pro -spec win32-msvc && C:/Qt/Tools/QtCreator/bin/jom.exe qmake_all
jom.exe
jom.exe install

# MOVE "app/settings" "app/release"

windeployqt.exe "./app/release/DNAI.exe" -qmldir=C:\Users\Victor\Documents\EIP\Duly-GUI\Gui\app\resources -verbose=2

copy "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Redist\MSVC\14.13.26020\x64\Microsoft.VC141.CRT\*" "./app/release/"
copy "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Redist\MSVC\14.13.26020\x64\Microsoft.VC141.CXXAMP\*" "./app/release/"
copy "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Redist\MSVC\14.13.26020\x64\Microsoft.VC141.OpenMP\*" "./app/release/"

RENAME "app/release" "DNAI"
move "app/DNAI" "./"

rmdir /s app
rmdir /s lib
DEL Makefile
DEL ".qmake.stash"

cd DNAI
rmdir /s Users
rmdir /s src
DEL *.cpp
DEL *.h


cd ..

qmake.exe C:\Users\Victor\Documents\EIP\Duly-GUI\Server\Server.pro -spec win32-msvc && C:/Qt/Tools/QtCreator/bin/jom.exe qmake_all
jom.exe
move "release\Server.exe" DNAI

cd DNAI
md DNAI_UPDATER
cd ..

rmdir /s debug
rmdir /s release
DEL "Makefile*"
DEL ".qmake.stash"

qmake.exe C:\Users\Victor\Documents\EIP\Software-updater\SoftwareUpdater\SoftwareUpdater.pro -spec win32-msvc && C:/Qt/Tools/QtCreator/bin/jom.exe qmake_all
jom.exe
pause
move "release\DNAI Updater.exe" "DNAI\DNAI_UPDATER"
windeployqt.exe "./DNAI/DNAI_UPDATER/DNAI Updater.exe" -qmldir=C:\Users\Victor\Documents\EIP\Software-updater\SoftwareUpdater\qml -verbose=2

copy "C:\Users\Victor\Documents\EIP\Software-updater\SoftwareUpdater\lib\libeay32.dll" "./DNAI/DNAI_UPDATER/"
copy "C:\Users\Victor\Documents\EIP\Software-updater\SoftwareUpdater\lib\ssleay32.dll" "./DNAI/DNAI_UPDATER/"

rmdir /s debug
rmdir /s release
DEL "Makefile*"
DEL ".qmake.stash"

cd DNAI
md Core
cd ..
copy "C:\Users\Victor\Documents\EIP\Duly\CoreDaemon\bin\Release\*" "./DNAI/Core"

rmdir /Y /s repos

robocopy "libs" "DNAI" /E

mkdir "C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data\DNAI"
robocopy "DNAI" "C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data\DNAI" /E
