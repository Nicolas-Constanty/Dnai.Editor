#!/bin/sh                                                                                                                                                                                   

#VARIABLES                                                                                                                                                                                   
app_path="./Application/"
app_name="DNAI.app"

repository_update_path="/Users/victorgouet/Documents/Rendu/DNAI_updaters"

#END                                                                                                                    

current_dir=$PWD
release_version=null
mac_files="mac_files.updater"

if [ "$1" == "--release" ]
  then
    if [ "$2" ]
        then
        release_version=$2
    fi
fi

if [ $release_version == null ]
then
    exit 1
fi

cd $app_path
find $app_name -type f -follow -print|xargs stat -f "%A %N" > $current_dir/$mac_files
cd $current_dir

rm -rf $repository_update_path/mac
mkdir -p $repository_update_path/mac
cp -rf $app_path$app_name  $repository_update_path/mac
mv $current_dir/$mac_files $repository_update_path/

cd $repository_update_path

git branch $release_version-branch $release_version
git checkout $release_version-branch

git add --all
git commit -m "new version $release_version on mac"

git tag -d $release_version
git tag $release_version

git push origin :$release_version
git push origin $release_version

echo "--- new version available $release_version ---"