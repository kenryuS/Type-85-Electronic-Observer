#! /bin/bash

if [ -z "$QTDIR" ]; then
        echo "Missing Environment Variable: QTDIR"
	echo "Please set this variable according to https://cefview.github.io/QCefView/docs/intros/buiding#2-qt"
	exit 1
fi

currDir=$PWD
buildDir=$(mktemp -d)

echo "Build Directory is $buildDir"

cd $buildDir
git clone --depth 1 --recursive https://github.com/CefView/QCefView.git repo
cd repo

bash ./generate-linux-x86_64.sh
cmake --build .build/linux.x86_64

cmake --install .build/linux.x86_64
cp out/linux.x86_64/QCefView $currDir/linux
