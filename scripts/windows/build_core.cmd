cd %APPVEYOR_BUILD_FOLDER%\Duly
mkdir %APPVEYOR_BUILD_FOLDER%\Core
nuget restore CorePackage.sln
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" %APPVEYOR_BUILD_FOLDER%\Duly\CoreDaemon\CoreDaemon.csproj  /t:Rebuild /p:Configuration=ReleaseCoreDaemon;OutputPath=%APPVEYOR_BUILD_FOLDER%\Core