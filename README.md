This is an in class edit.

# cs100 - software construction

This is a course on [how to be a hacker](http://www.catb.org/esr/faqs/hacker-howto.html).  Being a hacker [means a lot of things](http://www.catb.org/jargon/html/H/hacker.html).  It means:

1. wanting to know *how* and *why* computers work

2. being efficient / never repeating yourself

3. using and contributing to open source software

4. understanding the edge cases of your software

5. using tools in creative and unexpected ways

6. (occasionally) we combine all these together and break stuff

Hacking is a mindset.  I can't force it on you---it's up to you to embrace it.  For example, we'll be discussing many new tools in this course: a version control system called `git`, an editor called `vim`, a debugging tool called `gdb`, and we'll be going into quite a bit more depth on how to use `bash` and the `Linux` operating system.  All of these tools are very weird.  Using them will make you uncomfortable.  At first.  But these tools are powerful.  Mastering these tools will make you a *much* more efficient programmer.  Once you've mastered them, you'll never go back.

Your main goal in this course is to build your own unix shell.  This is the biggest project you've undertaken so far.  You'll be developing it as an open source project and will be forced to collaborate with each other at various points.

By the end of the course, you should be comfortable running your own open source project and contributing to other people's open source code.

### instructors

lecturer: Mike Izbicki

teaching assistant: Bryan Marsh

office hours: TBD

**IMPORTANT:** If you want to contact the instructors about the course, you should NOT do it via email.  Instead, you should report an issue via github.  We will talk about how to do this in class.  This is a system similar to the piazza system you may already be familiar with, but it more popular for open source software development. 

### course schedule

This schedule is only a rough outline, and will probably change a lot.  If there's something you want to learn not on the schedule, let me know!  We have a lot of flexibility in this course to learn fun things.

week | dates | topics
--- | --- | ---
1 | July 28 | introduction; using vim
1 | July 29 | version control with git
1 | July 30 | basic unix system calls (`open`,`close`,`read`,`write`)
1 | July 31 | more system calls (`fork`, `wait`, `exec`); fork bombs
2 | Aug 4 | case study: Linux (history of OSS)
2 | Aug 5 | debugging with gdb
2 | Aug 6 | shell scripting: introduction
2 | Aug 7 | more system calls (`readdir`,`stat`)
3 | Aug 11 | shell scripting: io redirection (`>`, `>>`, `<`, `<<<`)
3 | Aug 12 | shell scripting: piping (`|`)
3 | Aug 13 | shell scripting: `if` statements and `for` loops
3 | Aug 14 | unix signal handling (`signal`, `sigaction`);
4 | Aug 18 | unix environment variables from bash (`export`, `PATH`, `HOME`, `EDITOR`)
4 | Aug 19 | unix environment variables from C code (`getenv`, `setenv`)
4 | Aug 20 | case study: heartbleed
4 | Aug 21 | case study: hacking the email system
5 | Aug 25 | case study: stuxnet
5 | Aug 26 | TBA
5 | Aug 27 | TBA
5 | Aug 28 | TBA

### grades

We will not be using ilearn in this course.  Instead everything will be done using a combination of git and bash scripts.  The file `GRADES.md` contains a detailed breakdown of how your grades will be stored electronically, and how you can access them.  We will be using this system as a case study in bash programming and the unix philosophy.

### cheating policy

Every assignment specifies different collaboration policies.  Some assignments will be individual, and some will be in a group.  Follow the specified policy exactly!

I take cheating seriously.  When I catch students cheating, I give them an F in the class.  Then I forward your case to the academic integrity board and recommend that you be expelled from UCR.  Finally, I will post a note on this project with your full name and a description of your infraction.  This will be available on the internet forever for future employers to find.

All of your code will be run through an automated cheating detector.  It is very good.  It understands C++ better than you do and can find instances of copying much more sophisticated than just copy and pasting. 

