set version= windows%APPVEYOR_REPO_TAG_NAME%

set actual_user= "%APPVEYOR_ACCOUNT_NAME%"
set project_path= "%APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data"
set windows_file= "%APPVEYOR_BUILD_FOLDER%\Deploiement\Windows\windows_files.updater"
set current_path="%APPVEYOR_BUILD_FOLDER%\Deploiement\Windows"

set repository_path= "%APPVEYOR_BUILD_FOLDER%\DNAI_updaters"
set repository_windows= "%APPVEYOR_BUILD_FOLDER%\DNAI_updaters\windows"

cd %project_path%
dir /a-d /b /s > %windows_file%
fart.exe --remove -C --c-style %windows_file% "%APPVEYOR_BUILD_FOLDER%\\Deploiement\\Windows\\DNAISetup\\packages\\com.vendor.product\\data\\\\"

cd %repository_path%

git tag %version%
git branch %version%-branch %version%
git checkout %version%-branch

rmdir /s windows
mkdir windows

cd %current_path%
start /wait robocopy %project_path% %repository_windows% /E
if %errorlevel% gtr 7 exit %errorlevel%
MOVE %windows_file% %repository_path%
cd %repository_path%

git add --all
git commit -m "new version %version% on windows"

git tag -d %version%
git tag %version%

git push origin %version%

cd %current_path%