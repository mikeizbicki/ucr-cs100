#!/bin/bash

rm total.csv

for name in $(cat < ./start/info);
do
    echo $name | sed 's/,.*//' >> total.csv
    ./grademake $(echo $name | sed 's/,.*//') >> total.csv

    ./githubp/getem $(echo $name | sed 's/,/~~@~~/' | sed 's/.*~~@~~//' | sed 's/,.*//')
    ./githubp/makem $(echo $name | sed 's/,/~~@~~/' | sed 's/.*~~@~~//' | sed 's/,.*//') >> total.csv

    ./redditp/getem $(echo $name | sed 's/,/~~@~~/4' | sed 's/.*~~@~~//' | sed 's/,.*//')
    ./redditp/makem $(echo $name | sed 's/,/~~@~~/4' | sed 's/.*~~@~~//' | sed 's/,.*//') >> total.csv
     echo ?~!~endl~!~? | cat >> total.csv
done

cat < total.csv | sed ':a;N;$!ba;s/\n//g' | cat > total.csv
cat < total.csv | sed 's/?~!~endl~!~?/\n/g' | cat > total.csv



