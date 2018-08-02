DEL %INSTALL_FOLDER%\.moc
DEL %INSTALL_FOLDER%\.obj
DEL %INSTALL_FOLDER%\.rcc
start /wait robocopy %APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\libs %INSTALL_FOLDER% /E
if %errorlevel% gtr 7 exit %errorlevel%
mkdir "%APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data\Dnai"
start /wait robocopy %APPVEYOR_BUILD_FOLDER%\Dnai "%APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data\Dnai" /E
if %errorlevel% gtr 7 exit %errorlevel%
cd %APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\DNAISetup
C:\Qt\Tools\QtInstallerFramework\3.0\bin\binarycreator.exe -c config\config.xml -p packages %PACKAGE_NAME%.exe
signtool.exe sign -v -f MySPC.pfx -t http://timestamp.verisign.com/scripts/timstamp.dll %PACKAGE_NAME%.exe
start /wait signtool.exe verify %PACKAGE_NAME%.exe