UNIX-Signals
============

How can vim and bash ignore `^C`? Especially considering that programs launched by bash do not ignore such signals?

This page contains a few videos that should hopefully give you a better understanding of what signals are and what you can do with them.

##Introduction
<a href="http://www.youtube.com/watch?feature=player_embedded&v=LgNg_fyk8-c" target="_blank"><img src="http://img.youtube.com/vi/LgNg_fyk8-c/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

In this video, we briefly mention what signals are, and give a few examples of some common signals.
**NOTE:** `SIGSTOP` and `SIGKILL` cannot be caught or ignored.

##`signal()` and custom handlers
<a href="http://www.youtube.com/watch?feature=player_embedded&v=mzdCf0zCmrg" target="_blank"><img src="http://img.youtube.com/vi/mzdCf0zCmrg/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

Here, we demonstrate how to catch a signal, and also how to override them with our own custom handler.

##`sigaction()` and an example
<a href="http://www.youtube.com/watch?feature=player_embedded&v=ahRBRGVTi5w" target="_blank"><img src="http://img.youtube.com/vi/ahRBRGVTi5w/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

This is a simple lesson on what sigaction is and how sigaction can be used.
##`kill()`
<a href="http://www.youtube.com/watch?feature=player_embedded&v=O3UZqUTB5-w" target="_blank"><img src="http://img.youtube.com/vi/O3UZqUTB5-w/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

Here is a lesson on the `kill()` function. `kill()` is used to send a specified signal to a specified process.
[Code used in the video](http://pastebin.com/dq546zkG)