#!/bin/sh
#test -f Application-Installer.dmg && rm Application-Installer.dmg
./yoursway-create-dmg/create-dmg \
--volname "DNAI Installer" \
--volicon "Image/DNAI_icon.icns" \
--background "Image/DNAI_logo.png" \
--window-pos 200 120 \
--window-size 800 400 \
--icon-size 100 \
--icon DNAI.app 0 0 \
--hide-extension DNAI.app \
--app-drop-link 200 100 \
DNAI-Installer.dmg \
Application/