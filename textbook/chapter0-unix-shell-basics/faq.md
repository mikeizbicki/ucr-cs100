#hw0 FAQs

Below are some simple answers to the most frequently asked questions on hw0, with links to the issues they are referenced from.

##compiling

Can we use C++11 to compile?  
[Yes](https://github.com/mikeizbicki/ucr-cs100/issues/838) , [you can.](https://github.com/mikeizbicki/ucr-cs100/issues/1378)


Why isn't C++11 working?  
[Make sure you've entered the cs100 command]
(https://github.com/mikeizbicki/ucr-cs100/issues/253) 
, and [avoid using the -ansi tag if you're using c++11.](https://github.com/mikeizbicki/ucr-cs100/issues/1389)


##connectors

How should I handle mixed connectors in a single statement?  
However you'd like, [as long as you document your choice.](https://github.com/mikeizbicki/ucr-cs100/issues/1385)

How should I handle incorrect connectors?  
If the connector itself is invalid, the best choice would be to [print an error message.](https://github.com/mikeizbicki/ucr-cs100/issues/1381)
If the connector is incorrectly placed, how to handle it is [up to you.](https://github.com/mikeizbicki/ucr-cs100/issues/850)


##execvp

Why am I getting this "bad address" error?  
[Because the char** argument you are passing into execvp needs to be null terminated.](https://github.com/mikeizbicki/ucr-cs100/issues/256)

##getlogin()

getlogin() doesn't work correctly, what should I do?  
[Use getpwuid instead.](https://github.com/mikeizbicki/ucr-cs100/issues/284)


##git

Why isn't `git push` working?  
If you're getting the "403 forbidden while accessing" error, [you probably forgot to run the cs100 command.](https://github.com/mikeizbicki/ucr-cs100/issues/281)
Also, make sure that your local repository is up to date by [doing a git pull.] (https://github.com/mikeizbicki/ucr-cs100/issues/269)


##make

I don't understand the "bin/rshell", what does it mean?  
[Your Makefile is supposed to create a new directory named `bin`](https://github.com/mikeizbicki/ucr-cs100/issues/855)
[and install your program in it.](https://github.com/mikeizbicki/ucr-cs100/issues/853)



