## cs100 - open source software construction

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
For example, we'll be discussing many new tools in this course:
a version control system called `git`,
an editor called `vim`,
debugging tools called `gdb`, `valgrind`, and `cppcheck`,
and we'll be going into quite a bit more depth on how to use the `bash` shell and the `Linux` operating system.
All of these tools are very weird.
Using them will make you uncomfortable.
At first.
But these tools are powerful.
Mastering these tools will make you a *much* more efficient programmer.
Once you've mastered them, you'll never go back.

There are two main projects you will work on in this course:

1. Your first four homework assignments walk you through the process of building your own unix shell.
This is the biggest project you've undertaken so far.
You'll be developing it as an open source project,
and you will collaborate with each other at various points.

2. Your last homework assignment is to contribute to the open source community by improving the documentation on a project of your choice.
Many of the required readings for this course were written by former cs100 students.
If you do a good job on this project, future cs 100 students will be learning from you for years to come!

**By the end of the course, you should be comfortable running your own open source projects and contributing to other people's projects.**

### instructors

position | name | office hours (WCH 110)
--- | --- | ---
lecturer | Mike Izbicki | Tuesday 11-noon
teaching assistant | Busra Celikkaya | Friday 2pm-3pm
teaching assistant | Zachary Benavides | Friday 1pm-2pm

**IMPORTANT:**
If you want to contact the instructors about the course, you should NOT do it via email.
Instead, you should report an issue via github.
We will talk about how to do this in class.
This is a system similar to the piazza system you may already be familiar with,
but it is more popular for open source software development.

### course schedules

Our lectures will roughly follow this schedule.
You should do the required readings before class.
I will occasionally have unscheduled quizzes to ensure you are doing the reading.

week | date | reading/quiz | topics
--- | --- | --- | ---
1 | Jan05 | | introduction; using vim
1 | Jan07 | Daniel Lemire's [how to learn efficiently](http://lemire.me/blog/archives/2014/12/30/how-to-learn-efficiently/); Paul Graham's [what to do in college](http://www.paulgraham.com/college.html); and Ian Malpass's [advice to future software engineers](https://medium.com/@indec/advice-to-future-software-engineers-64a29669d179)| version control with git
2 | Jan12 | esr's [all about unix](http://www.catb.org/esr/writings/taoup/html/context.html) and [about common software licenses](http://www.catb.org/esr/writings/taoup/html/ch16s07.html) | version control with git
2 | Jan14 | **quiz**; the relevant sections of the [syscalls tutorial](textbook/assignment-help/syscalls)| syscalls: managing processes (`fork`,`wait`,`exec`,`perror`)
3 | Jan19 | Lucas Xu's [Makefile tutorial](textbook/tools/Makefiles); Alexander Ortiz's [how to write a README file](textbook/bestpractices/WritingREADMEs); esr's thoughts on [unix documentation part I](http://www.catb.org/esr/writings/taoup/html/ch18s02.html) and [part II](http://www.catb.org/esr/writings/taoup/html/ch18s06.html) | syscalls: managing files (`open`,`close`,`read`,`write`)
3 | Jan21 | Kenley Arai's tutorial on [test driven development](textbook/bestpractices/TestDrivenDevelopment); Gabriel Ruiz's [tutorial on how to design test cases](textbook/bestpractices/WritingGoodTestCases);  | debugging tools (`gdb`)
4 | Jan26 | William Coates' [valgrind tutorial](textbook/tools/valgrind); Paul Graham's [how to be a good hacker](http://www.paulgraham.com/gh.html); Jeff Atwood's [how to become a better programmer](http://blog.codinghorror.com/how-to-become-a-better-programmer-by-not-programming/) | debugging tools (`valgrind`,`cppcheck`)
4 | Jan28 | **quiz**; [bitwise operators](textbook/assignment-help/bitwise-ops); [macros](textbook/assignment-help/macros); the relevant sections of the [syscalls tutorial](textbook/assignment-help/syscalls) | syscalls: managing directories (`readdir`,`stat`)
5 | Feb02 | Ycombinator's [startup ideas we'd like to fund](http://old.ycombinator.com/ideas.html) and Paul Graham's [start up funding](http://paulgraham.com/startupfunding.html) | shell scripting: io redirection/piping
5 | Feb04 | Patrick McKenzie [on salary negotiation for programmers](http://www.kalzumeus.com/2012/01/23/salary-negotiation/) (it's long; you don't have to read it all) | shell scripting: io redirection/piping
6 | Feb09 | the relevant sections of the [syscalls tutorial](textbook/assignment-help/syscalls) | syscalls: io redirection/piping (`pipe`,`dup`)
6 | Feb11 | **quiz** | shell scripting: control flow with `if` and `for`
7 | Feb16 | esr's thoughts on [using make](http://www.catb.org/esr/writings/taoup/html/ch15s04.html) | shell scripting: detailed makefiles
7 | Feb18 | Shubhro Saha's [why engineers should write](http://www.shubhro.com/2014/12/27/software-engineers-should-write/); the economist's [good writing style](http://www.economist.com/styleguide/introduction) | syscalls: signal handling (`signal`,`sigaction`)
8 | Feb23 | the relevant sections of the [syscalls tutorial](textbook/assignment-help/syscalls) | shell scripting: environment variables (`export`,`PATH`,`HOME`,`EDITOR`)
8 | Feb25 | **quiz** | syscalls: environment variables (`getenv`,`setenv`)
9 | Mar02 | esr's classic [Master Foo series](http://www.catb.org/esr/writings/taoup/html/unix_koans.html) | syscalls: pthreads
9 | Mar04 | esr's thoughts on [flaws with unix](http://www.catb.org/esr/writings/taoup/html/ch20s03.html); Poul-Henning Kamp's [a generation lost in the bazaar](https://queue.acm.org/detail.cfm?id=2349257&ref=fullrss) | syscalls: sockets
10 | Mar09 | **quiz** | case study: hacking the email system and the [ioccc.org](http://ioccc.org)
10 | Mar11 | --- | case study: stuxnet and heartbleed

If there's something you want to learn not on the schedule, let me know!
We have a lot of flexibility in this course to learn fun things.

The assignments are due on the following days:

assignment | date
--- | ---
[hw0](assignments/hw/hw0-rshell) | Friday of week 3 (Jan 23rd) @ 11:59 PM
[hw1](assignments/hw/hw1-ls) | Sunday of week 6 (Feb 8th) @ 11:59 PM
[hw4](assignments/hw/hw4-contributing) - topic | Wednesday of week 6 (Feb 11th) before class
[hw2](assignments/hw/hw2-piping) | Sunday of week 8 (Feb 22th) @ 11:59 PM
[hw4](assignments/hw/hw4-contributing) - draft | Wednesday of week 8 (Feb 25th) before class
[hw3](assignments/hw/hw3-signals) | Sunday of week 10 (Mar 8th) @ 11:59 PM
[hw4](assignments/hw/hw4-contributing) - final | Friday of week 10 (Mar 13th) @ 11:59 PM

### grades

We will not be using ilearn in this course.
Instead, we will be using a course management system called `gitlearn`.
This software was developed in part by previous cs100 students,
and you will be able to earn considerable extra credit by contributing to it.
We will be using this system as a case study in bash programming and the unix philosophy.
For details, see the [gitlearn repo](https://github.com/mikeizbicki/gitlearn).

### cheating policy

Every assignment specifies different collaboration policies.
Some assignments will be individual, and some will be in a group.
Follow the specified policy exactly!

I take cheating seriously.
When I catch students cheating, I give them an F in the class.
Then I forward your case to the academic integrity board and recommend that you be expelled from UCR.

All of your code will be run through an automated cheating detector.
It is very good.
It understands C++ better than you do and can find instances of cheating much more sophisticated than just copy and pasting.

