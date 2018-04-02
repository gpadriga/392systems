#!/bin/bash
list=$PATH
list=$(echo $list | tr ":" " ")
arr=($list)
for i in "${arr[@]}" ; do
	echo $i
done