#!/bin/bash

# GET /index.html HTTP/1.1
read cmd path protocol

filename=$((tr '?' ' ' <<< "$path") | grep -o "^.* ")
httpvar=$((tr '?' ' ' <<< "$path") | grep -o " .*$")
# httpvar='foo=bar'
export $httpvar

path=".$filename"
contents=$($path)       # dynamic
#contents=$(cat $path)   # static

echo "HTTP/1.1 200 ok"
echo "Content-type: text/html"
echo "Content-length: ${#contents}"
echo ""
echo "$contents"

