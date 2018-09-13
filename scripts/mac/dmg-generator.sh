#!/bin/sh
#test -f Application-Installer.dmg && rm Application-Installer.dmg
$TRAVIS_BUILD_DIR/scripts/mac/yoursway-create-dmg/create-dmg \
--volname "DNAI Installer" \
--volicon "$TRAVIS_BUILD_DIR/scripts/mac/Image/DNAI_icon.icns" \
--background "$TRAVIS_BUILD_DIR/scripts/mac/Image/BackgroundDmg720p.png" \
--window-pos 200 120 \
--window-size 800 450 \
--icon-size 100 \
--icon DNAI.app 260 265 \
--hide-extension DNAI.app \
--text-size 16 \
--app-drop-link 540 265 \
$TRAVIS_BUILD_DIR/DNAI-Installer.dmg \
$TRAVIS_BUILD_DIR/Application/