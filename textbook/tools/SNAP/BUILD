#!/bin/bash

rm total

for name in $(cat < ./start/info);
do
    echo $name | sed 's/,.*//' >> total
    ./grademake $(echo $name | sed 's/,.*//') >> total

    ./githubp/getem $(echo $name | sed 's/,/~~@~~/' | sed 's/.*~~@~~//' | sed 's/,.*//')
    ./githubp/makem $(echo $name | sed 's/,/~~@~~/' | sed 's/.*~~@~~//' | sed 's/,.*//') >> total

    ./redditp/getem $(echo $name | sed 's/,/~~@~~/4' | sed 's/.*~~@~~//' | sed 's/,.*//')
    ./redditp/makem $(echo $name | sed 's/,/~~@~~/4' | sed 's/.*~~@~~//' | sed 's/,.*//') >> total
     echo ?~!~endl~!~? | cat >> total
done

cat < total | sed ':a;N;$!ba;s/\n//g' | cat > total
cat < total | sed 's/?~!~endl~!~?/\n/g' | cat > total



