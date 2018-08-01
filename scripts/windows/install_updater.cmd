mkdir %INSTALL_FOLDER%\DNAI_UPDATER
move "release\DNAI Updater.exe" "%INSTALL_FOLDER%\DNAI_UPDATER"
windeployqt.exe "%INSTALL_FOLDER%\DNAI_UPDATER\DNAI Updater.exe" -qmldir=%APPVEYOR_BUILD_FOLDER%\Software-updater\SoftwareUpdater\qml -verbose=2
copy "%APPVEYOR_BUILD_FOLDER%\Software-updater\SoftwareUpdater\lib\libeay32.dll" "%INSTALL_FOLDER%\DNAI_UPDATER"
copy "%APPVEYOR_BUILD_FOLDER%\Software-updater\SoftwareUpdater\lib\ssleay32.dll" "%INSTALL_FOLDER%\DNAI_UPDATER"