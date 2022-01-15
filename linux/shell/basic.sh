#!/usr/bin/sh

# use this to disable ctrl+s lock terminal[signaling senders to stop input]
# terminal driver responses fo locking scroll screen
# stty -ixon

var() {
    # a1=3
    a1=$(("1" + "2"))
    a2=1
    a3=2
    # a4=2
    a4=$((a2 > a3 ? a2 + 1: a3 + 1))
    echo $(((1 + 2) * a3 / 2))
}

if_statement() {
    if [ -f $1 ]
    then
        echo "$1 file has already existed!"
    else
        echo "$1 file doesn't exist"
    fi
    if [ -d $1 ]
    then
        echo "$1 dir has already existed!"
    else
        echo "$1 dir doesn't exist"
    fi
}

for_loop() {
    echo "for loop"
    # v1
    for num in 1 2 3; do echo -n "$num "; done; echo
    # v2
    for num in {1..10}; do echo -n "$num "; done; echo
    for num in {1..10..2}; do echo -n "$num "; done; echo
    # v3
    for file in $(ls); do echo -n "$file "; done
    for file in /usr/*; do echo -n "$file "; done
    for pid_name in $(ps ax| awk 'NR>1 {print $1 "@" $5}'); do
        local pid=`echo $pid_name | cut -d@ -f1 -`
        local cmd=`echo $pid_name | cut -d@ -f2 -`
        echo $pid $cmd
    done
    # v4
    local sm=0
    for (( i=1; i<=10; ++i  )); do sm=$((sm+$i)); done
    echo $sm
}

#
# switch_case() {
#
# }

# for_loop
var
