cd %APPVEYOR_BUILD_FOLDER%\Duly
mkdir %APPVEYOR_BUILD_FOLDER%\Core
dotnet restore
MSBuild.exe %APPVEYOR_BUILD_FOLDER%\Duly\CoreDaemon\CoreDaemon.csproj  /t:Rebuild /p:Configuration=Release;Platform=x64;OutputPath=%APPVEYOR_BUILD_FOLDER%\Core