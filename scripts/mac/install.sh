#!/bin/sh

#
#  DNAI DMG GENERATOR
#

#---------------------------------------------------------------------------------------

#QT VERSION
qtv="5.10.1"

#BINARIES
qmakebinary="$QTDIR/bin/qmake"
deployqt="$QTDIR/bin/macdeployqt"
monopath="/Library/Frameworks/Mono.framework/Commands/mono"

#DNAI GUI
dnaipropath="$TRAVIS_BUILD_DIR/Gui/DNAI.pro"
dnaisettingpath="$TRAVIS_BUILD_DIR/Gui/app/settings/"
dnairessourcespath="$TRAVIS_BUILD_DIR/Gui/app/resources/"

#DNAI CORE
binarycorepath="$TRAVIS_BUILD_DIR/dependencies/bin/Release/"
csprojcorepath="$TRAVIS_BUILD_DIR/dependencies/CoreDaemon.csproj"

#DNAI SERVER
serverpropath="$TRAVIS_BUILD_DIR/Server/Server.pro"

#DNAI UPDATER
updaterpropath="$TRAVIS_BUILD_DIR/dependencies/Software-updater/SoftwareUpdater/SoftwareUpdater.pro"
updateressourcespath="$TRAVIS_BUILD_DIR/dependencies/Software-updater/SoftwareUpdater/qml/"

#---------------------------------------------------------------------------------------

compile=true
release=false
version=""

help() {
    echo "--compile=true\t\tcompile the project"
    echo "--compile=false\t\tDOES NOT compile the project"
    echo "--release ${VERSION}\t\tRELEASE VERSION UPDATE"
}

# CLONE DEPENDENCIES

mkdir $TRAVIS_BUILD_DIR/dependencies
cd $TRAVIS_BUILD_DIR/dependencies
git clone https://github.com/Gouet/Software-updater.git
git clone https://$TravisToken@duly-eip.visualstudio.com/_git/Duly

build_dir=$TRAVIS_BUILD_DIR/build
install_dir=$install_dir/app/DNAI.app/Contents/MacOS/
mkdir $build_dir


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
    cd $build_dir

    $qmakebinary $dnaipropath
    make -j 8
    
    cd plugins
    rm -rf */*.o
    rm -rf */*.cpp
    rm -rf */*.h
    rm -rf */Makefile.*

    cd $install_dir
    
    mkdir settings
    cp -rf $dnaisettingpath $install_dir/settings

    $qmakebinary $serverpropath
    make -j 8
    cp Server $install_dir

    cd $install_dir
    mkdir Core
    cd $build_dir

    echo "---- Core generation ----"
    msbuild $csprojcorepath /t:Rebuild /p:Configuration=Release;Platform=x64
    cd $binarycorepath
    mkbundle -o CoreDaemon --simple CoreDaemon.exe
    cd $TRAVIS_BUILD_DIR/build
    cp -rf $binarycorepath/CoreDaemon $install_dir/Core/
    echo "---- Core generation END ----"
    sleep 3

    #cp $monopath $install_dir/Core/

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
    
    echo "----- Settings plugin -----"
    sleep 3
    mv plugins/Controls DNAI.app/Contents/PlugIns
    mv plugins/FontAwesome DNAI.app/Contents/PlugIns
    mv plugins/Settings DNAI.app/Contents/PlugIns
    install_name_tool -add_rpath @rpath/../PlugIns/Controls/libdnaicontrolsplugin.dylib DNAI.app/Contents/MacOS/DNAI
    install_name_tool -add_rpath @rpath/../PlugIns/FontAwesome/libdnaifontawesomeplugin.dylib DNAI.app/Contents/MacOS/DNAI
    install_name_tool -add_rpath @rpath/../PlugIns/Settings/libdnaisettingsplugin.dylib DNAI.app/Contents/MacOS/DNAI
    
    sleep 3


    rm -rf plugins
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

#DEPLOY UPDATER DNAI
    rm -rf "DNAI Updater.app"

    $qmakebinary $updaterpropath
    make -j 8
    $deployqt "DNAI Updater.app" -qmldir=$updateressourcespath -verbose=2

    rm *.o
    rm *.cpp
    rm *.h
    rm Makefile

    mv "DNAI Updater.app" ./Application/DNAI.app/Contents/Frameworks

    sleep 3
fi

echo "----- Generate DMG file -----\n\n"
sleep 1
cd $TRAVIS_BUILD_DIR/scripts/mac
./dmg-generator.sh

if [ $? -eq 1 ]
then
    echo "------ FAILED -----"
    exit 1
fi

echo "----- SUCCESS TO GENERATE DMG -----"
cd $TRAVIS_BUILD_DIR/scripts/mac
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