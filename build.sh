#!/bin/sh
build_dir="$(pwd)/build"

cmake -H. -B"$build_dir"
if [ ! "$?" = "0" ]; then
	echo "Configure failed."
	exit 1
fi
cmake --build "$build_dir" --target all
if [ ! "$?" = "0" ]; then
	echo "Building failed."
	exit 1
fi
echo "Built successfully."
exit 0
