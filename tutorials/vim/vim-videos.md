advancing to intermediate level vim
===================================

##Introduction
I've created a few videos showing off some useful features in vim that beginners are unlikely to know exist. The features I've chosen to go over will make you select and operate on text much quicker than before after a bit of practice. By the end of the series I hope that you leave not only with some new tools to work with in vim, but with an interest to go out and learn more to become even better. Let's begin!

##Text Objects
Vim treats chunks of text surrounded by certain delimiters as a text object. You can operate on the entire object using operators like `d` `v` and `c`. Beginner vim users are often annoyed with selection in vim. Copying or moving text around often feels plain faster just using the mouse. That's because you aren't using text objects!

[![Text-Objects](http://img.youtube.com/vi/jsdm_lVBuwk/0.jpg)](https://www.youtube.com/watch?v=jsdm_lVBuwk)

For more information on text objects you can check out `:h text-objects`.

##Macros
You can record any set of actions in vim and recall them later using macros. Composing a bunch of normal mode actions in vim can often lead to magical stuff happening. The potential here is limitless!

Macros are recorded by pressing `q` to record then selecting a key as a register. You will continue recording everything you do in vim until you end the recording by pressing `q` again. You can execute a macro by pressing `@` then the key you selected as a register.

[![Macros](http://img.youtube.com/vi/0OzHGa09wNI/0.jpg)](https://www.youtube.com/watch?v=0OzHGa09wNI)

*Super pro-tip:* registers have cross uses through a few features in vim. when you copy things using `y`, you are generally using the implicit `0` register. To yank to other registers, you first pick a register through pressing `"`, the register of your choice, then any kind of yank. You paste using a specific register using the same combination. Perhaps you've used `"+p`, the implicit paste-from-clipboard command? 

Anyways, these registers mix and match across different features. You can record a macro to the `l` register and paste the textual form using `"lp`. You could tinker the textual form of a macro, yank it back to the register using `"lyy` and it will work! This pro-tip is pretty advanced, but is very useful for tinkering with a highly complex macro that isn't working as you expect.


##Visual-Block Mode
Visual-block mode is different from the other visual modes in vim. It's rather hard to describe in words and is best understood through practice. Doing my best: it allows you to highlight a box of text using your cursor. If you go into other visual modes and go down a line, it is going to highlight all of the text to the right as you progress to the next line. Visual block does not do this. This allows you to select chunks of texts, ignoring the context from where they come from. Visual block also allows special append/prepend operations and are particularly useful for operating on columns of text.

[![Visual-Block](http://img.youtube.com/vi/T_OQoRJYq9Y/0.jpg)](https://www.youtube.com/watch?v=T_OQoRJYq9Y)

*Pro-tip:* commenting out code is super easy using visual-block mode! Go to visual-block mode, traverse the lines you want to comment, and press `0` to go to the beginning of the line. `I//<Esc>` to prepend comments to every line.

##Navigation
There's a lot of ways to move around in vim. A big part of being efficient in vim is picking the best navigation relative to whatever you're doing at that time. Generally there's more than one good choice for any situation you find yourself in, and just picking one of them leads to being quick overall. It isn't really feasible to use the optimal choice perfectly at every moment, but more methods you know the merrier.

I'm much more broad in focus in this video. But the main point I try to drive home is that concise movements to get to where you want to go are almost always going to be better than imprecise `h j k l` or `w b` movement. When you're moving around a file, you generally know where you want to go and what you want to see-- learn how to make vim get to those places quicker using the stuff in this video.

[![Movement](http://img.youtube.com/vi/c_VoBUeEQOc/0.jpg)](https://www.youtube.com/watch?v=c_VoBUeEQOc)
