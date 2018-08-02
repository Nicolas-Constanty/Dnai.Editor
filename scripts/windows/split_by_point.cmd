@echo off

FOR /f "tokens=1,2,3 delims=." %%a IN ("%APPVEYOR_REPO_TAG_NAME%") do set VERSION_MAJOR=%%a&set VERSION_MINOR=%%b&set VERSION_BUILD=%%c

