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
binarycorepath="$TRAVIS_BUILD_DIR/dependencies/Duly/CoreDaemon/bin/Release/"
csprojcorepath="$TRAVIS_BUILD_DIR/dependencies/Duly/CoreDaemon/CoreDaemon.csproj"
csprojcorepackagepath="$TRAVIS_BUILD_DIR/dependencies/Duly/CorePackage.sln"

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
git clone https://github.com/Gouet/DNAI_updaters.git

build_dir=$TRAVIS_BUILD_DIR/build
mkdir $build_dir

install_dir=$build_dir/app/release/DNAI.app/Contents/MacOS/
install_dir_app=$build_dir/app/release/DNAI.app/
final_dir="$TRAVIS_BUILD_DIR/Application"
mkdir $final_dir

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

# if [ $release == true ]
# then
#     echo "WARNING ! ARE YOU SURE YOU WANT TO UPDATE SOFTWARE VERSION ? Press [yes|no]."
#     read sure_version
#     if [ $sure_version != "yes" ]
#     then
# 	exit 1
#     fi
# fi

# rm -rf DNAI-Installer.dmg

if [ $compile == true ]
then
    cd $build_dir

    VERSION_MAJOR=$(echo $version | cut -d. -f1)
    VERSION_MINOR=$(echo $version | cut -d. -f2)
    VERSION_BUILD=$(echo $version | cut -d. -f3)

    $qmakebinary "VERSION_MAJOR=$VERSION_MAJOR" "VERSION_MINOR=$VERSION_MINOR" "VERSION_BUILD=$VERSION_BUILD" $dnaipropath
    make -j 8
    make install

    mkdir $install_dir/settings
    cp -rf $dnaisettingpath $install_dir/settings

    $qmakebinary $serverpropath
    make -j 8
    cp Server $install_dir

    mkdir $install_dir/Core

    echo "---- Core generation ----"
    brew install nuget
    brew link --overwrite mono
    nuget restore $csprojcorepackagepath
    /Library/Frameworks/Mono.framework/Commands/msbuild $csprojcorepath /t:Rebuild /p:Configuration=Release;Platform=x64
    cd $binarycorepath
    /Library/Frameworks/Mono.framework/Commands/mkbundle -o CoreDaemon --simple CoreDaemon.exe
    cd $build_dir
    cp -rf $binarycorepath/CoreDaemon $install_dir/Core/
    echo "---- Core generation END ----"

    echo "----- Create depandancy framework -----"
    sleep 1
    $deployqt $install_dir_app -qmldir=$dnairessourcespath -verbose=2
    
    echo "----- Settings plugin -----"
    sleep 3
    mv $build_dir/plugins/Controls $install_dir../PlugIns
    mv $build_dir/plugins/FontAwesome $install_dir../PlugIns
    mv $build_dir/plugins/Settings $install_dir../PlugIns
    mv $build_dir/plugins/Theme $install_dir../PlugIns
    install_name_tool -add_rpath @rpath/../PlugIns/Controls/libdnaicontrolsplugin.dylib $install_dir/DNAI
    install_name_tool -add_rpath @rpath/../PlugIns/FontAwesome/libdnaifontawesomeplugin.dylib $install_dir/DNAI
    install_name_tool -add_rpath @rpath/../PlugIns/Settings/libdnaisettingsplugin.dylib $install_dir/DNAI
    install_name_tool -add_rpath @rpath/../PlugIns/Theme/libdnaithemeplugin.dylib $install_dir/DNAI

    mv -f $install_dir_app $final_dir
    cd $final_dir/DNAI.app/Contents/MacOS/

    echo "----- Setting Server -----\n\n"
    sleep 1
    otool -L Server
    install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ./Server
    install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ./Server
    otool -L Server

#DEPLOY UPDATER DNAI

    rm -rf $build_dir
    mkdir $build_dir
    cd $build_dir
    $qmakebinary $updaterpropath
    make -j 8
    $deployqt "DNAI Updater.app" -qmldir=$updateressourcespath -verbose=2

    mv "DNAI Updater.app" $final_dir/DNAI.app/Contents/Frameworks

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
	echo "--- START REQUEST ---"
    ./request.sh --release $version
    if [ $? -eq 0 ]
    then
	echo "--- RELEASE ON SERVER ---"
	./updater.sh --release $version
	exit 0
    fi
fi
echo "------ FAILED -----"
exit 1