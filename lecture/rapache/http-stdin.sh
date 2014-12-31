#!/bin/bash

# this is the location of all the files
webroot="."

# read in the http request from stdin
read cmd request protocol

# print the request to stderr
echo "$cmd $request $protocol" >&2

# urls have lots of weird characters in them like "%20" instead of spaces
# this function converts the weird encoding into normal ascii encoding
# input is stdin, output is stdout
function urldecode() {
    local url_encoded="${1//+/ }"
    printf '%b' "${url_encoded//%/\x}"
}

# the GET request is the most common http command
if [ "$cmd" = "GET" ]; then

    file=$(cut -d'?' -f1 <<< "$request")
    args=$(cut -d'?' -f2 <<< "$request")

    # if the requested file is a shell script, execute the script
    # this is a Computer Generated Information (CGI) webpage
    if [ ${file##*.} = "sh" ] && [ -f "$webroot/$file" ]; then

        # FIXME: php, perl, python, and ruby are also popular languages for writing cgi scripts;
        # add support for one (or more) of these other languages

        for arg in $(tr '&' ' ' <<< "$args"); do
            arg=$(urldecode "$arg")
            export "$arg"
            echo "$arg" >&2
        done
        info=$($webroot/$file)

        echo "HTTP/1.1 200 OK"
        echo "Content-length: ${#info}"
        echo ""
        echo "$info"

    # the requested file is not a shell script, so just return the file exactly
    else

        # FIXME: if the requested file is a directory, we should:
        # display "./$file/index.html" if it exists;
        # otherwise, we should display all the files in the directory
        # double extra bonus points if you make each file clickable!
        info=$(cat "$webroot/$file")

        # the file exists, print it to stdout
        if [ $? = 0 ]; then
            echo "HTTP/1.1 200 OK"
            echo "Content-length: ${#info}"
            echo ""
            echo "$info"

        # the file could not be accessed
        else
            echo ""
            # FIXME: implement the 403 error code, which gets displayed when the file does not have permissions
            # it should display the page 403.html if it exists;
            # otherwise, it should display a standard error page

            # FIXME: implement the 404 error code, which gets displayed when the file does not exist
            # it should display the page 404.html if it exists;
            # otherwise, it should display a standard error page
        fi

        # FIXME: there is currently a bug with filetypes that are not text files (e.g. images)
        # firefox will interpret everything we send over as a text file
        # we should automatically detect the filetype of the file we're sending (using the file command)
        # then adjust the mime-type in the header appropriately
        # this will require some research to figure out exactly what to do

    fi

# the POST request is also a valid http command
elif ["$cmd" = "POST" ]; then
    echo "po"
    # FIXME: implement post requests
    # this will require a bit of research about what exactly post requests do
fi
