#!/bin/sh
build_dir="$(pwd)/build"

rm -rf $build_dir
if [ ! "$?" = "0" ]; then
	echo "Error occured while removing directory."
	exit 1
fi
echo "Build files cleaned up."
exit 0
