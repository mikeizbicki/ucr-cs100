rapache
=======

Rapache is a simple webserver built with bash commands. It implement unix command `nc`--netcat to listen http request
and send static or dynamic resources to clients corresponding to different requests. 

How to use
-------
1. Clone rapache directory to your machine.
2. Enter rapache directory and run `http.sh script` to start server.
```
$ git clone https://github.com/Dongdongshe/rapache
$ cd rapache
$ ./rapache/http.sh
```
Prerequistes
---------
Linux environment is necessary because we implement unix utility netcat to build this webserver.

Feature
-----------
The server can send Computer-generated-imagery(CGI) to clients depending on different requests. 
