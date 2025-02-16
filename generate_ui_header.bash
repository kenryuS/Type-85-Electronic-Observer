#! /bin/bash

mkdir -p forms/include

for uiFile in forms/*.ui ; do
	uiFileWithoutDirName="$(basename $uiFile)"
	outFile="forms/include/ui_${uiFileWithoutDirName%.*}.h"
	echo "$uiFile -> $outFile"
        uic -o $outFile $uiFile
done
