mkdir %APPVEYOR_BUILD_FOLDER%-build
cd %APPVEYOR_BUILD_FOLDER%-build
qmake -o %APPVEYOR_BUILD_FOLDER%-build -r -Wall -spec win32-msvc CONFIG+=%CONFIGURATION% %APPVEYOR_BUILD_FOLDER%/Gui && jom qmake_all
jom
jom install