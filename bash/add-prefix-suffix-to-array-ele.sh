#!/usr/bin/env bash

arr=("aa" "bb" "cc")

pref="pre-"
suff="-suf"

#method 1
new_arr=()
for ele in ${arr[@]}
do
    new_arr+=("${pref}${ele}${suff}")
done
echo ${new_arr[@]}

#method 2
for i in ${!arr[@]}
do
    arr[$i]=${pref}${arr[$i]}${suff}
done
echo ${arr[@]}

#method 3
arr=("aa" "bb" "cc")
arr=(${arr[@]/#/${pref}})
echo ${arr[@]}
arr=(${arr[@]/%/${suff}})
echo ${arr[@]}
