mkdir %APPVEYOR_BUILD_FOLDER%\Downloads
cd %APPVEYOR_BUILD_FOLDER%\Downloads
ps: Start-FileDownload https://github.com/stedolan/jq/releases/download/jq-1.5/jq-win64.exe
set PATH=%APPVEYOR_BUILD_FOLDER%\Downloads;%PATH%