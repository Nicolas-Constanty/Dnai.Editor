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
- 
<p align="center">
  <img alt="Main view screenshot" src="https://raw.githubusercontent.com/Nicolas-Constanty/Dnai.Editor/master/images/qmakeinstall.png">
</p>

- Build Dnai project
- Get the Core library from [here]()
- Put binary files of the Server inside [YOUR BUILD DNAI FOLDER]/app
- Put binary files of the Core inside [YOUR BUILD DNAI FOLDER]/app/Core
- Press Run on Qt

## License

Licensed under the [(L)GPL v2/3 ](LICENSE.md) License, with Qt Open source licence.
