#!/bin/sh
prj_dir="my-c-headerlibs-1.0"
prj_dist="$prj_dir.tar.gz"

cd .. && tar czvf $prj_dist $prj_dir && echo "Done." || echo "Failed."

