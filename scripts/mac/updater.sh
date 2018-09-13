#!/bin/sh                                                                                                                                                                                   

#VARIABLES                                                                                                                                                                                   
app_path="$TRAVIS_BUILD_DIR/Application/"
app_name="DNAI.app"

repository_update_path="$TRAVIS_BUILD_DIR/dependencies/DNAI_updaters"

#END                                                                                                                    

current_dir=$PWD
release_version=null
mac_files="mac_files.updater"

if [ "$1" == "--release" ]
  then
    if [ "$2" ]
        then
        release_version=mac$2
    fi
fi

if [ $release_version == null ]
then
    exit 1
fi

cd $app_path
find "$app_name/Contents/Frameworks" -type f -follow -print0|xargs -0 stat -f "%A %N" > $current_dir/$mac_files
find "$app_name/Contents/Info.plist" -type f -follow -print0|xargs -0 stat -f "%A %N" >> $current_dir/$mac_files
find "$app_name/Contents/MacOS" -type f -follow -print0|xargs -0 stat -f "%A %N" >> $current_dir/$mac_files
find "$app_name/Contents/PkgInfo" -type f -follow -print0|xargs -0 stat -f "%A %N" >> $current_dir/$mac_files
find "$app_name/Contents/PlugIns" -type f -follow -print0|xargs -0 stat -f "%A %N" >> $current_dir/$mac_files
find "$app_name/Contents/Resources" -type f -follow -print0|xargs -0 stat -f "%A %N" >> $current_dir/$mac_files
cd $current_dir

cd $repository_update_path

git checkout -f master
git tag $release_version
git branch $release_version-branch $release_version
git checkout $release_version-branch

rm -rf mac
mkdir -p mac

cd -
cp -rf $app_path$app_name  $repository_update_path/mac
mv $current_dir/$mac_files $repository_update_path/
cd -

git add --all
git commit -m "new version $release_version on mac"

git tag -d $release_version
git tag $release_version

git remote rm origin
git remote add origin https://Gouet:$GithubRW@github.com/Gouet/DNAI_updaters.git

git push origin :$release_version
git push origin $release_version

echo "--- new version available $release_version ---"