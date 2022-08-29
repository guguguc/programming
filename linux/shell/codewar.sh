#!/bin/bash
# =====================================================
# Pad string
# =====================================================
function pad_str() {
    # expr length $1
    # echo $1|awk '{print length}'
    len=${#1}
    pad_len=$((5-len))
    # echo -n [no new line]
    # echo -e [bashslash escape]
    for (( i=1; i<=pad_len; i++ )); do echo -n 0; done
    echo $1
}
function pad_str_clean() {
    printf "Value is %05d" $1
}
# pad_str $1
# pad_str_clean $1

# =====================================================
# Double num
# =====================================================

function double_num() {
    num=$1
    echo $((num * 2))
}
function double_num_clean() {
    echo $(($1 * 2))
    echo $[$1 * 2]
}
# double_num $1
# double_num_clean $1

# =====================================================
# Echo message
# =====================================================

function echo_msg() {
    echo "Hello, $1 how are you doing today?"
}
# echo_msg $1

# =====================================================
# Caculate milliseconds since midnight
# =====================================================

function calc_millisecs() {
    h=$1
    m=$2
    s=$3
    echo $[(s+60*m+3600*h) * 1000]
}

# calc_millisecs $1 $2 $3

# =====================================================
# Twice as old
# =====================================================

function caculate_years() {
    year=$[$1-2*$2]
    if [[ $year -lt 0 ]]; then year=$[-year]; fi
    echo $year
}

function caculate_years_clean() {
    (( year=$1-2*$2 )); echo ${year#-}
}
# caculate_years $1 $2
# caculate_years_clean $1 $2

# =====================================================
# Transform string by mapping
# =====================================================
# A -> T
# T -> A
# C -> G
# G -> C
function str_transform() {
    input=$1
    str='ATCG'
    str_map='TAGC'
    len=${#1}
    ans=''
    for (( i=1; i<=len; ++i )); do
        c=${input:i-1:1}
        idx=`expr index $str $c`
        ans=$ans${str_map:idx-1:1}
    done
    echo $ans
}

function str_transform_clean() {
    echo $1 | tr "ATCG" "TAGC"
}

# str_transform 'ATCG' # TAGC
str_transform_clean 'ATCG' # TAGC
