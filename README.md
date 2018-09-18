# Dnai Editor - Source code

[![Build status](https://ci.appveyor.com/api/projects/status/gjcxsjh80jo76coe/branch/master?svg=true&passingText=master%20-%20Windows%2010%20-%20passing&pendingText=master%20-%20Windows%2010%20-%20pending&failingText=master%20-%20Windows%2010%20-%20failing)](https://ci.appveyor.com/project/Nicolas-Constanty/dnai-editor/branch/master)
[![Build status](https://ci.appveyor.com/api/projects/status/gjcxsjh80jo76coe/branch/develop?svg=true&passingText=develop%20-%20Windows%2010%20-%20passing&pendingText=develop%20-%20Windows%2010%20-%20pending&failingText=develop%20-%20Windows%2010%20-%20failing)](https://ci.appveyor.com/project/Nicolas-Constanty/dnai-editor/branch/develop)

[![Build Status](https://img.shields.io/travis/Nicolas-Constanty/Dnai.Editor/master.svg?label=master%20-%20MacOS)](https://travis-ci.org/Nicolas-Constanty/Dnai.Editor)
[![Build Status](https://img.shields.io/travis/Nicolas-Constanty/Dnai.Editor/develop.svg?label=develop%20-%20MacOS)](https://travis-ci.org/Nicolas-Constanty/Dnai.Editor)

[![Build Circle Ci](https://img.shields.io/circleci/project/github/Nicolas-Constanty/Dnai.Editor/master.svg?label=master%20-%20Ubuntu)](https://circleci.com/gh/Nicolas-Constanty/Duly-GUI/tree/master)
[![Build Circle Ci](https://img.shields.io/circleci/project/github/Nicolas-Constanty/Dnai.Editor/develop.svg?label=develop%20-%20Ubuntu)](https://circleci.com/gh/Nicolas-Constanty/Duly-GUI/tree/develop)

[![CodeFactor](https://www.codefactor.io/repository/github/nicolas-constanty/dnai.editor/badge)](https://www.codefactor.io/repository/github/nicolas-constanty/dnai.editor)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f5ad248cb0884d53a206b12154e3295b)](https://www.codacy.com/app/nicolas.constanty/Dnai.Editor?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Nicolas-Constanty/Dnai.Editor&amp;utm_campaign=Badge_Grade)

## Introduction

[Dnai Editor](https://code.visualstudio.com) is a visual scripting software,
 build with the [Qt Open Source](https://www.qt.io/download-qt-installer) version.
 
<p align="center">
  <a href="https://www.youtube.com/watch?v=7lFM3htAfNI"><img src="https://raw.githubusercontent.com/Nicolas-Constanty/Dnai.Editor/master/images/youtube_demo.jpg" height="300" alt="IMAGE ALT TEXT"></a>
</p>

 You can download it for Windows, and macOS on [Dnai website](https://dnai.io).

<p align="center">
  <img alt="Main view screenshot" src="https://raw.githubusercontent.com/Nicolas-Constanty/Dnai.Editor/master/images/mainview.png" height="300">
</p>

## Compilation

You can compile the software using Qt >= 5.10.1, but you will need our "Core" library to run it properly.

Our Core library sources remain private, so you can find the [latest version of the Core here](https://github.com/Nicolas-Constanty/Dnai.Editor/releases).

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
- Get the Core library from [here](https://github.com/Nicolas-Constanty/Dnai.Editor/releases)
- Put binary files of the Server inside [YOUR BUILD DNAI FOLDER]/app
- Put binary files of the Core inside [YOUR BUILD DNAI FOLDER]/app/Core
- Press Run on Qt

## Authors

**Adrien Wery** - Website API and Dnai.Editor ([github](https://github.com/Adpa18))

**Fernand Veyrier** - Dnai.Core (virtual machine for compilation) and Unity3D Plugin ([github](https://github.com/FernandVEYRIER))

**Nicolas Constanty** - Dnai.Editor and Website design ([github](https://github.com/Nicolas-Constanty))

**Quentin Gasparoto** - Dnai.Core (virtual machine for compilation) and Dnai.Editor ([github](https://github.com/GasparQ))

**Victor Gouet** - Dnai.Server, Deploiement Windows/Mac and Dnai.Editor ([github](https://github.com/Gouet))

See also the list of [contributors](https://github.com/Nicolas-Constanty/Dnai.Editor/graphs/contributors) who participated in this project.

## License

Licensed under the [(L)GPL v2/3 ](https://github.com/Nicolas-Constanty/Dnai.Editor/blob/master/LICENSE) License, with Qt Open source licence.
