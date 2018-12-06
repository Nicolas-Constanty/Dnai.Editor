echo y | DEL .\app\release\%INSTALL_FOLDER%\.moc /Q
echo y | DEL .\app\release\%INSTALL_FOLDER%\.obj /Q
echo y | DEL .\app\release\%INSTALL_FOLDER%\.rcc /Q
copy "%APPVEYOR_BUILD_FOLDER%\Gui\lib\quazip.dll" ".\app\"
windeployqt.exe "./app/release/DNAI.exe" -qmldir=%APPVEYOR_BUILD_FOLDER%\Gui\app\resources -verbose=2
dir /b "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Redist\MSVC" | tail.exe -1 > mredist.txt
set /p MREDIST=<mredist.txt
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Redist\MSVC\%MREDIST%\x64\Microsoft.VC141.CRT\*" "./app/release/"
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Redist\MSVC\%MREDIST%\x64\Microsoft.VC141.CXXAMP\*" "./app/release/"
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Redist\MSVC\%MREDIST%\x64\Microsoft.VC141.OpenMP\*" "./app/release/"
mkdir %APPVEYOR_BUILD_FOLDER%\Dnai
mkdir %APPVEYOR_BUILD_FOLDER%\Dnai\Editor
RENAME "app/release" %APPVEYOR_REPO_TAG_NAME%
move "app/%APPVEYOR_REPO_TAG_NAME%" %APPVEYOR_BUILD_FOLDER%\Dnai\Editor