mkdir %APPVEYOR_BUILD_FOLDER%\Software-updater\build
cd %APPVEYOR_BUILD_FOLDER%\Software-updater\build
qmake -o %APPVEYOR_BUILD_FOLDER%\Software-updater\build -r -Wall -spec win32-msvc CONFIG+=%CONFIGURATION% %APPVEYOR_BUILD_FOLDER%\Software-updater\SoftwareUpdater && jom qmake_all
jom