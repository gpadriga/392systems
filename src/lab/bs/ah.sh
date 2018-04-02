list=$PATH
list=$(echo $list | tr ":" " ")
arr=($list)
for i in $list ; do
    if [ -x "$i/$1" ]
    then
       echo "$i/$1"
    fi
done
