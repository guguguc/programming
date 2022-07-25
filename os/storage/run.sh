#!/bin/bash
# $1 src file
# $2 args -c
src=$1
file="test.txt"
cnt=1000
if [[ ! -f $src ]]; then exit 1; fi
gcc $src -Wno-all -o write.out || exit $?
if [[ -f test.txt ]]; then rm ${file}; fi
for (( i = 0; i < $cnt; ++i )); do ./write.out $2; echo "=============="; done
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
# ./write.out & \
echo "content of file ${file}:"
cat ${file}
echo -e "\nstat of file ${file}"
stat ${file}
