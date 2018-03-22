C:\Qt\Tools\QtInstallerFramework\3.0\bin\binarycreator.exe -c config\config.xml -p packages DNAISetup.exe
sign.bat
"C:\Program Files (x86)\Windows Kits\10\bin\x64\signtool.exe" verify DNAISetup.exe
pause