set version= windows0.0.25

set accesschk= "C:\Users\Victor\Downloads\accesschk.exe"
set actual_user= "Victor"
set project_path= "C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows\DNAISetup\packages\com.vendor.product\data"
set windows_file= "windows_files.updater"
set current_path="C:\Users\Victor\Documents\EIP\Duly-GUI\Deploiement\Windows"

set repository_path= "C:\Users\Victor\Documents\EIP\DNAI_updaters"
set repository_windows= "C:\Users\Victor\Documents\EIP\DNAI_updaters\windows"

set git= "C:\Program Files\Git\bin\git.exe"

%accesschk% -s %actual_user% %project_path% > %windows_file%
fart.exe --remove -C --c-style %windows_file% "C:\\Users\\Victor\\Documents\\EIP\\Duly-GUI\\Deploiement\\Windows\\DNAISetup\\packages\\com.vendor.product\\data\\\\"

pause

cd %repository_path%

%git% checkout -f master
%git% tag %version%
%git% branch %version%-branch %version%
%git% checkout %version%-branch

rmdir /s windows
mkdir windows

cd %current_path%
robocopy %project_path% %repository_windows% /E
MOVE %windows_file% %repository_path%
cd %repository_path%

%git% add --all
%git% commit -m "new version %version% on windows"

%git% tag -d %version%
%git% tag %version%

%git% push origin %version%

cd %current_path%

pause