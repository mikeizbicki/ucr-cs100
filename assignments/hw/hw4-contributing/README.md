## giving back to the open source community

### requirements

For this assignment, you must give something back to the open source community.  One common problem with open source software is a lack of documentation and easily accessible tutorials.  You will create some.  Future students of this class (and random strangers on the internet) will be using your tutorials to help them learn.

Your tutorial should be between 1000-2000 words.
It should have plenty of code examples and/or pictures illustrating your topic.

#### topic

You are free to choose any topic that will be interesting to future cs100 students.
Here are some past assignments and some suggestions for extending their work:

* [Rashid Goshtasbi and Kyler Rynear's video tutorials](https://izbicki.me/blog/videoguide-for-github-vim-bash.html).
A good topic would be to provide similar video tutorials for another aspect of this class.

* [William Coates's valgrind tutorial](../../../tutorials/valgrind).
A good topic would be to extend this tutorial to cover more of valgrind's features.
A similar tutorial for `gdb` or `cppchecker` (or another tool) would also be nice.

* [Daniel Ting and Katherine Gallaher's syscall tutorial](../../../tutorials/syscalls).
A good topic would be to extend this tutorial to cover more syscalls.
If you choose a topic like this, make sure it stays nice and cohesive and is not just a list of examples.

* [Antoine Guerrero's writeup of how he hacked git to change his grades in this course](https://github.com/aguerrero/Faking-Git-Commits).
If you have a similarly engaging story about some cool programming trick you've done, that would make a good writeup.

* [Brunna Amorim's git cheatsheet](../../lab/lab1-git/git-cheatsheet.md).
A similar cheatsheet for `gdb` or `bash` would make a decent topic.

* [Kevin Nguyen clarified lab 1 by adding pictures to the README file](../../lab/lab1-git).
You can run `git blame` on the file to see exactly what his contributions were.
If one of the labs/assignments was confusing to you, you could extend it in a similar manner.
You will have to work closely with me to make sure the changes are appropriate.

Some other ideas are:

* Think of a topic that initially confused you, and explain it in a way that makes sense to you.
This will help future students master the topic.

* What aspect of computer science do you wish you knew more about?
Research it and writeup your findings.

* The stl and boost libraries have lots of cool features not covered in courses here.
Pick two or three related topics and write them up in a guide.

* Templates are becoming more and more important in C++ programming.
Write a tutorial on how to do template meta programming.
Similarly, write a tutorial on some of the features in the recent C++ 11 or 14 standards.

* Pick an entry in the [international obfuscated C code contest](http://ioccc.org) and give a writeup explaining how it works.

<!--One simple way to format these tutorials is as a "top ten list."  For example, the project might be "the top ten most useful bash commands."  Then provide ten commands from bash and show how they work and why they're useful.-->

#### writing style

Your writeup must be FUN and ENGAGING.
Informal writing is encouraged.
Imagine your favorite internet blog post and write like that.

In particular, don't write long, drawn-out sentences that use sophisticated verbage because no one wants to read that, especially not cs100 students or random programmers on the internet be kind to us oh and use proper punctuation because reading this sentence totally sucks.
Also, spll chck ur writing and dnt use txt spk b/c I hate tht 5|-|!7.

I highly recommend you visit UCR's writing center.

A short, clear writeup is MUCH better than a long wordy writeup.

### collaboration policy

You may work in a team on this assignment, or you may work individually.
Teams can be of any size, but a larger team must give a larger contribution.
If you choose a topic that overlaps with someone else, I will assign you to the same team.

You are ENCOURAGED to discuss this assignment with anyone, whether they are on your team or not.
In particular, you should get other people to read your drafts!

You must NOT copy and paste material from the internet or any other source.

You MAY use images that you did not create yourself if the use conforms to the images' licensing agreements.

### submission instructions

There are three submissions for this assignment:

The first is part is due at midnight on **Friday, Nov 7**.
In this submission, you must create an issue on github describing what your tutorial will be about, and who will be on your team.
I will use this submission to ensure your topic is appropriate.

The second submission is due at midnight on **Thursday, Dec 4**.
This is a rough draft submission of your project.
Create a folder in this repo called `/tutorials/yoursubject`.
You should create a pull request through github on this repo showing the current status of your project.
You should be approximately 75% complete with your project's content at this point.
I will use this submission to make sure that your project will actually provide benefit to future cs100 students.

Your third submission is due at midnight on **Thursday, Dec 11**.
This will be the final submission for your project.
You must submit your tutorial as a pull request on this repository through github.
Use the same folder from above called `/tutorials/yoursubject`.
Inside the folder should be at least a file called `README.md` that contains the contents of your tutorial.
You may include other files in this folder, such as images or cpp files, if they are relevant to the tutorial.
I will evaluate the pull request the same as any other pull request into an open source project.

### grading

20 points for your first draft

40 points for technical accuracy

40 points for writing style

Ultimately, grading is entirely subjective on my part.
If I enjoyed reading your writeup, you will get a good score.
If I don't enjoy reading it, you will get a bad score.
Therefore, I recommend you show me drafts of your progress.
I'll give you advice on how to make your writeup more fun.

If you visit the writing center, I will give you +5 points of extra credit on this assignment.
(You'll also get a much higher grade anyways.)
