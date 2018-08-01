cd %APPVEYOR_BUILD_FOLDER%\Dnai
mkdir %APPVEYOR_BUILD_FOLDER%-server
cd %APPVEYOR_BUILD_FOLDER%-server
qmake.exe -o %APPVEYOR_BUILD_FOLDER%-server -r -Wall -spec win32-msvc CONFIG+=%CONFIGURATION% %APPVEYOR_BUILD_FOLDER%/Server && jom qmake_all
jom