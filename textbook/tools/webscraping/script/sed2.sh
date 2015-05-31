# sh sed2.sh [input] [output]
sed -n 's/.*>\(.*\)\.<.*/\1/ p;s/.*>\(.*\)<.*/\1/ p' $1 | cat > $2
