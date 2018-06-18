# Dnai Editor - Source code

[![Build Circle Ci](https://circleci.com/gh/Nicolas-Constanty/Dnai.Editor/tree/master.svg?style=shield)](https://circleci.com/gh/Nicolas-Constanty/Dnai.Editor/tree/master.svg?style=shield)

[Dnai Editor](https://code.visualstudio.com) is a visual scripting software,
 build with the [Qt Open Source](https://www.qt.io/download-qt-installer) version.
 You can download it for Windows, and macOS on [Dnai website](https://dnai.io).

You can compile the software using Qt >= 5.10.1, but you will need our "Core" library to run it properly.

Our Core library sources remain private, so you can find the [latest version of the Core here]().

<p align="center">
  <img alt="Main view screenshot" src="https://raw.githubusercontent.com/Nicolas-Constanty/Dnai.Editor/master/images/mainview.png">
</p>

## Compilation

- Get the repository content
```
git clone https://github.com/Nicolas-Constanty/Dnai.Editor.git
git submodule update --init --recursive
```
- Open Dnai.Editor/Server/Server.pro
- Run qmake
- Build the Server project
- Open Dnai.Editor/Gui/DNAI.pro with Qt >= 5.10.1
- Run qmake
- Go to Projects->Build->Add Build step->Make
- add "install" to the make argument
<p align="center">
  <img alt="Main view screenshot" src="https://raw.githubusercontent.com/Nicolas-Constanty/Dnai.Editor/master/images/qmakeinstall.png">
</p>

- Build Dnai project
- Get the Core library from [here]()
- Put binary files of the Server inside [YOUR BUILD DNAI FOLDER]/app
- Put binary files of the Core inside [YOUR BUILD DNAI FOLDER]/app/Core
- Press Run on Qt

## License

Licensed under the [(L)GPL v2/3 ](https://github.com/Nicolas-Constanty/Dnai.Editor/blob/master/LICENSE) License, with Qt Open source licence.
