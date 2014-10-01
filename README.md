# cs100 - software construction

This is a course on [how to be a hacker](http://www.catb.org/esr/faqs/hacker-howto.html).
Being a hacker [means a lot of things](http://www.catb.org/jargon/html/H/hacker.html).
It means:

1. wanting to know *how* and *why* computers work

2. being efficient / never repeating yourself

3. using and contributing to open source software

4. understanding the edge cases of your software

5. using tools in creative and unexpected ways

6. (occasionally) we combine all these together and break stuff

Hacking is a mindset.
I can't force it on you---it's up to you to embrace it.
For example, we'll be discussing many new tools in this course: a version control system called `git`, an editor called `vim`, debugging tools called `gdb`, `valgrind`, and `cppcheck`, and we'll be going into quite a bit more depth on how to use the `bash` shell and the `Linux` operating system.
All of these tools are very weird.
Using them will make you uncomfortable.
At first.
But these tools are powerful.
Mastering these tools will make you a *much* more efficient programmer.
Once you've mastered them, you'll never go back.

Your main goal in this course is to build your own unix shell.
This is the biggest project you've undertaken so far.
You'll be developing it as an open source project and will be forced to collaborate with each other at various points.

By the end of the course, you should be comfortable running your own open source project and contributing to other people's open source code.

### instructors

position | name | office hours
--- | --- | ---
lecturer | Mike Izbicki |  Thursday 3:30-5:00 PM, WCH110
teaching assistant | Taeyoung Kim | Tuesday 3:30-5:00 PM, WCH110

**IMPORTANT:**
If you want to contact the instructors about the course, you should NOT do it via email.
Instead, you should report an issue via github.
We will talk about how to do this in class.
This is a system similar to the piazza system you may already be familiar with, but it more popular for open source software development.

### text book

The course textbook is *The Art of Unix Programming* by Eric Steven Raymond (more commonly known as esr).
You can download it for free at [esr's website](http://www.catb.org/esr/writings/taoup/html).

Other required readings:

* [Paul Graham on what to get out of college](http://www.paulgraham.com/college.html)

* [Paul Graham on how to be a good hacker](http://www.paulgraham.com/gh.html)

* [Jeff Atwood on how to become a better programmer](http://blog.codinghorror.com/how-to-become-a-better-programmer-by-not-programming/)

* [Patrick McKenzie on salary negotiation for programmers](http://www.kalzumeus.com/2012/01/23/salary-negotiation/)

* [Ian Malpass's advice to future software engineers](https://medium.com/@indec/advice-to-future-software-engineers-64a29669d179)

You can get extra credit for reading any of the following and discussing it with me in office hours:

* Elizer Yudowski's [Harry Potter and the Methods of Rationality](http://hpmor.org) (free online)

* Peter Seibel's *Coders at Work* (a copy is in the ACM room)

* Jessica Livingston's *Founders at Work* (a copy is in the ACM room)

### course schedule

This schedule is only a rough outline, and will probably change a lot.
If there's something you want to learn not on the schedule, let me know!
We have a lot of flexibility in this course to learn fun things.

week | date | assignments | topics
--- | --- | --- | ---
0 | Oct02 | | introduction; using vim
1 | Oct07 | | version control with git
1 | Oct09 | [all about unix](http://www.catb.org/esr/writings/taoup/html/context.html)] and [about common software licenses](http://www.catb.org/esr/writings/taoup/html/ch16s07.html) | version control with git
2 | Oct14 | quiz | syscalls: managing processes (`fork`,`wait`,`exec`,`perror`)
2 | Oct16 | [reading about documentation](http://www.catb.org/esr/writings/taoup/html/ch18s02.html) and [part II](http://www.catb.org/esr/writings/taoup/html/ch18s06.html) | syscalls: managing files (`open`,`close`,`read`,`write`)
3 | Oct21 | hw1 | debugging tools (`gdb`)
3 | Oct23 | | debugging tools (`valgrind`,`cppcheck`)
4 | Oct28 | quiz | syscalls: managing directories (`readdir`,`stat`)
4 | Oct30 | | shell scripting: io redirection/piping
5 | Nov04 | hw2 | shell scripting: io redirection/piping
5 | Nov06 | | syscalls: io redirection/piping (`pipe`,`dup`)
6 | Nov11 | quiz | shell scripting: control flow with `if` and `for`
6 | Nov13 | [reading about make](http://www.catb.org/esr/writings/taoup/html/ch15s04.html) | shell scripting: detailed makefiles
7 | Nov18 | hw3 | syscalls: signal handling (`signal`,`sigaction`)
7 | Nov20 | [Master Foo](http://www.catb.org/esr/writings/taoup/html/unix_koans.html) | shell scripting: environment variables (`export`,`PATH`,`HOME`,`EDITOR`)
8 | Nov25 | quiz | syscalls: environment variables (`getenv`,`setenv`)
8 | Nov27 | | THANKSGIVING
9 | Dec02 | hw4 | syscalls: pthreads
9 | Dec04 | [flaws with unix](http://www.catb.org/esr/writings/taoup/html/ch20s03.html) | syscalls: sockets
10 | Dec11 | quiz | case study: hacking the email system and the [ioccc.org](http://ioccc.org)
10 | Dec13 | hw5 | case study: stuxnet and heartbleed

### grades

We will not be using ilearn in this course.
Instead everything will be done using a combination of git and bash scripts.
The file `GRADES.md` contains a detailed breakdown of how your grades will be stored electronically, and how you can access them.
We will be using this system as a case study in bash programming and the unix philosophy.

### cheating policy

Every assignment specifies different collaboration policies.
Some assignments will be individual, and some will be in a group.
Follow the specified policy exactly!

I take cheating seriously.
When I catch students cheating, I give them an F in the class.
Then I forward your case to the academic integrity board and recommend that you be expelled from UCR.
Finally, I will post a note on this project with your full name and a description of your infraction.
This will be available on the internet forever for future employers to find.

All of your code will be run through an automated cheating detector.
It is very good.
It understands C++ better than you do and can find instances of cheating much more sophisticated than just copy and pasting.

