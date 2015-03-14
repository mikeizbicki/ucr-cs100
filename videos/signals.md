UNIX-Signals
============
a tutorial on signals by Shinray and Ian

How can vim and bash ignore `^C`? Especially considering that programs launched by bash do not ignore such signals?

This page contains a few videos that should hopefully give you a better understanding of what signals are and what you can do with them.

##Introduction
<a href="http://www.youtube.com/watch?feature=player_embedded&v=tDMjNPKQJP8" target="_blank"><img src="http://img.youtube.com/vi/tDMjNPKQJP8/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

In this video, we briefly mention what signals are, and give a few examples of some common signals.
**NOTE:** `SIGSTOP` and `SIGKILL` cannot be caught or ignored.

##`signal()` and custom handlers
<a href="http://www.youtube.com/watch?feature=player_embedded&v=GFo1Oo42Rv0" target="_blank"><img src="http://img.youtube.com/vi/GFo1Oo42Rv0/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

Here, we demonstrate how to catch a signal, and also how to override them with our own custom handler.
##`kill()`
<a href="http://www.youtube.com/watch?feature=player_embedded&v=2-pIsY7iq10" target="_blank"><img src="http://img.youtube.com/vi/2-pIsY7iq10/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

Here is a lesson on the `kill()` function. `kill()` is used to send a specified signal to a specified process.
[Code used in the video](http://pastebin.com/dq546zkG)
