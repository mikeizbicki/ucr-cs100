#! /bin/bash

# GET / HTTP/1.1
# cin >> cmd >> path >> proto;
read cmd path proto

echo "cmd=$cmd" >&2
echo "path=$path" >&2
echo "proto=$proto" >&2

cat "./$path"

