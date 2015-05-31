# sh sed1.sh [input] [output]
sed -n 's/.*>\(.*\)<.*/\1/ p' $1 | cat > $2
