#!/bin/sh

#
#  DNAI DMG GENERATOR
#

#---------------------------------------------------------------------------------------

#QT VERSION
qtv="5.10.1"

#BINARIES
qmakebinary="/Users/victorgouet/Qt/$qtv/clang_64/bin/qmake"
deployqt="/Users/victorgouet/Qt/$qtv/clang_64/bin/macdeployqt"
monopath="/Library/Frameworks/Mono.framework/Commands/mono"

#DNAI GUI
dnaipropath="../../DNAI/DNAI.pro"
dnaisettingpath="../../DNAI/app/settings/"
dnairessourcespath="/Users/victorgouet/Documents/DulyGUI/Duly-GUI/DNAI/app/resources/"

#DNAI CORE
binarycorepath="$HOME/Documents/Rendu/Core/Duly/CoreDaemon/bin/Release/"

#DNAI SERVER
serverpropath="../../Server/Server.pro"

#---------------------------------------------------------------------------------------

compile=true
release=false
version=""

help() {
    echo "--compile=true\t\tcompile the project"
    echo "--compile=false\t\tDOES NOT compile the project"
    echo "--release ${VERSION}\t\tRELEASE VERSION UPDATE"
}

# GESTION DES ARGUMENTS

for var in "$@"
do
    if [[ $release == true && "$version" == "" ]]
    then
	version=$var
    fi
    if [ $var == "--compile=true" ]
    then
	compile=true
    fi
    if [ $var == "--compile=false" ]
    then
	compile=false
    fi
    if [ $var == "--help" ]
    then
	help
	exit 0
    fi
    if [ $var == "--release" ]
    then
	release=true
    fi
done
# END

if [[ "$version" == "" && $release == true ]]
then
    echo "No version found.\nPlease ./install.sh --release ${VERSION}"
    exit 1
fi

if [ $release == true ]
then
    echo "WARNING ! ARE YOU SURE YOU WANT TO UPDATE SOFTWARE VERSION ? Press [yes|no]."
    read sure_version
    if [ $sure_version != "yes" ]
    then
	exit 1
    fi
fi

rm -rf DNAI-Installer.dmg

if [ $compile == true ]
then
    rm -rf Application


    $qmakebinary $dnaipropath
    make

    cd app/DNAI.app/Contents/MacOS/
    mkdir settings
    cd -
    cp -rf $dnaisettingpath ./app/DNAI.app/Contents/MacOS/settings

    $qmakebinary $serverpropath
    make
    cp Server app/DNAI.app/Contents/MacOS/

    cd app/DNAI.app/Contents/MacOS/
    mkdir Core
    cd -

    cp -rf $binarycorepath ./app/DNAI.app/Contents/MacOS/Core/

    cp $monopath ./app/DNAI.app/Contents/MacOS/Core/

    rm *.o
    rm *.cpp
    rm -rf lib/
    rm *.h
    rm Server
    cp -rf app/DNAI.app ./
    rm -rf app
    rm Makefile

    echo "----- Create depandancy framework -----"
    sleep 1
    $deployqt DNAI.app -qmldir=$dnairessourcespath -verbose=2
    sleep 3

    rm -rf Application
    mkdir Application
    mv -f DNAI.app Application
    cd Application/DNAI.app/Contents/MacOS

    echo "----- Setting Server -----\n\n"
    sleep 1
    otool -L Server
    install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ./Server
    install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Server
    otool -L Server
    cd -

    sleep 3
fi

echo "----- Generate DMG file -----\n\n"
sleep 1
./dmg-generator.sh

if [ $? -eq 1 ]
then
    echo "------ FAILED -----"
    exit 1
fi

echo "----- SUCCESS TO GENERATE DMG -----"

if [ $release == true ]
then
    ./request.sh --release $version
    if [ $? -eq 0 ]
    then
	echo "--- RELEASE ON SERVER ---"
	./updater.sh --release $version
	exit 0
    fi
fi

exit 1