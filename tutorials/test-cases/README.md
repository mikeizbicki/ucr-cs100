###**Writing Test Cases for your Command Shell**
*A short explanation for students and curious programmers taking on such a project*

I. **_“If you are not trying to break your program, you probably didn't write a good one”_**

What are test cases? What is their purpose? Why are they important?

A test case is something that is meant to check whether or not a program does what it should be doing. It's you being a good programmer.
     
In 1998, NASA's _Mars Climate Orbiter_ was tasked with looking for water on Mars (among other things), but some of the programmers of this space vessel had been working with SI units while others had been working in English units. The result? The thrusters were 4.45 times more powerful than they should have been and this $327.6 million project is now lost in space, *for ever*. Talk about a failed test case. And these were **_NASA_** programmers, so you can imagine how *buggy* our programs might be. Bugs are inevitable at whatever the level of a programmer. For example, I recently updated my phone to Android 5.0 and my Chrome broswer and Messenger are *always* crashing!! (darn Google). 

It's important to catch these failed test cases and fix them before they come back to bite is in the behind (before they affect our **GRADES**). Basically, we want to know where our program works, where it could use a little more work, and where its limitations are. This tutorial will hopefully get you thinking about how to do this.

II. **_“You must learn to bark before you can howl with coyotes.”_**

Before I get into how to write good test cases, I will reiterate something we all should already know, yet have the tendency to keep on doing for some crazy reason (if you are a student, maybe you _just_ started on the piece of your project that is due tomorrow. I have been there, done that!) : 

	Before you write code, know what the heck you are doing! 
    
At this point, if you are working on this project then you probably know your way around `C++` (or whatever other language you are using) and certain algorithms pretty well. But *are you you comfortable with* `C`? Specifically, *POINTERS*.  What do you know about *system calls* (these require knowledge of `C`), and which are needed to accomplish what you are trying to do? How the heck will you take in user input? _Parse_ input?? *Error checking*, who???? What in the world do *_forks_* have to do with this assignment?? You get the point. 
    
It will save a lot of **pseudo work** [insert hyper link to Cal Newport blog here] and precious time in the long run (**Time Arbitration** is key [insert hyper link to 'Time Arbitration' piece]). 

While you do this, go ahead and fill in some sections of the test cases table (see the example table below). This will get you thinking about how you will write your program, and will ultimately help you with your test cases later. 

(meditation [hyper link here] does help relieve the stress of CS100 though!)

**_tl;dr: "You must learn to fly before you can soar with eagles."_**  

III. **_“You don’t have to learn to be wise. If you just _flow_ you can be successful. Mother Nature will carry you.”_**

You probably want to make things as easy as possible for yourself. Here are a few things you might want to consider doing while you are writing your program:
- Keep track of what you are doing in your program [insert hyperlink pseudo code tutorial here]
- Fill in the table! Or if you don't like the table, jot it down in a notebook where you can access it later. 

The last two points will help with writing your bigger test cases later. 

Another important thing to do is to test while you code!

- The most basic test case: DOES IT COMPILE?!! I'm sure you know how ugly those compilation errors can get. I personally have no patience with those long error messages. Have two terminal windows (or several) open to make writing and compiling simultaneously quick and easy (see Xmonad, Terminator [insert hyperlink here]). It is annoying to have to go back and forth between writing something in your text editor and compiling all in one terminal: Edit your program. Save your code. Exit your code. Compile your code. Get error messages. Reopen text editor. Forget error messages. Exit. Compile AGAIN. And so on.

- Is the snippet of code you just wrote doing what it should be doing? How does it interact with the rest of your program? Before you're in too deep, check. You might be surprised. 
Does your system call work? Does `fork` create a parent and child process that begins right at that spot, or does it start from the beginning of the entire program? Why should I have to `wait` for my `chilren`? How does `execvp` handle `ls` by itself? With flags? Arguments? Such curiosity about `fork`, `wait`, `execvp` and other functions or system calls might come in handy later.

- Is there an error message where there should be and is it a good one that's not too loud, not too useless? Does the program _fail/exit_ with an _error_ when it should? In other words, **error check. _ALWAYS!_** (See `~/ucr-cs100/checksyscalls.sh`)

(mention _Modularity_ here)

**_tl;dr: "Better a thousand times careful than once dead."_**

IV. **_“Don't count your chickens before they hatch.”_**
	
Alright, so finally your code seems to be working. The little parts look okay. You are now ready to begin testing the functionality of your program in its entire scope—or at least a bigger and more important part of it. Keep in mind that you might have to bounce back and forth (hopefully not too much) between _II_ and _III_. (See the example of how to use the table below for more on this)
	
Here, you'll want to think of **_every_ possible situation** that can arise when the specific section of your shell that you are currently focusing on is being used. This is where the test cases you thought of and wrote down (in your table) while researching what your program was meant to do, and while writing your program, come in handy. 

Consider asking the following questions and jot down what you come up with: 

1. What are the the simple case commands that should work? If you are using `execvp`, do `ls` and `pwd` work? If you are using `execve`, do `ls` and `pwd` work? Are `execvp` or `execve` using the flags and arguments you saved into an array and passed through? There are subtleties even in these simple examples. Of course, it is important to have these working before you can move on to more advanced test cases.

2. What are different combinations you can have? If you are required to be able to chain commands, do `ls; pwd` and `pwd||ls` and `ls &&pwd` work the way they should? If you are writing an `ls` program meant to implement some flags, do `ls -a -l -R` and `ls -lRa` work? Does order matter? And what happens when you insert some directories or files as arguments in between?
What are the limitations of your program? These are things that need to be working but for whatever reason do not. You do not know these limitations for certain, yet, since you haven't tested these cases, but you likely will have a hunch at this point. Jot down what happened so you can know what to fix or not fix if worked. 

3. What about the things that shouldn't be working? Check here that there isn't an weird or undefined behavior going on. It is recommended that you handle these cases similar to bash. See the functionaliry of the command you are tesing via `info [command]` in your terminal, the bash documentations, and the bash source code. These cases are as important as the cases that should work.

4. What is your program realistically able to do at this point? For example, say you have only messed around with `forking` and `execvp`, then your program won't be working that well—or at all—with user input. Or if your current assignment is meant to get you acquainted with `execvp` and `fork`, you likely don't need to handle `piping` and `input/output redirection` (that might be a future assignment). In other words, don't get unnecessarily carried away with your test cases.
	
After you have all these things written down, you are ready to start testing and recording what works and doesn't work. Ideally, your end product (example: the homework you turn in) will have all possible and necessary test cases taken care of. In certain cases, you should document in your `README.md` file [hyperlink to tutorial here] what behavior (bugs) your program has in certain test cases. Always be thorough with your test cases and your documentation. 

**_tl;dr "It ain't over 'til the fat lady sings."_**

IV. **_“A failure is only a step on the way to your success.”_**
	
It is very impossible that, when you finish your program, you'll right away have all test cases taken care of (it'd probably have to be a very simple program, which is not really the cases with this project). It takes **trial and error** with these sort of things. You will likely go back and forth between II and III a bit. However, recording the test cases you have tried, the pseudo code [hyperlink here] you have been writing, and of course having started early with your writing process, will help you keep your _sanity_!
	
There are quite a few resources and _debugging_[hyperlink here] tools out there that will help you in your endeavors—namely [insert hyper links for each]:
- `bash`'s source code
- `stackoverflow`
- `gdb`
- `valgrind`
- `cppchecker`
- GOOGLE

tl;dr: Read it!

V. An example

This is an example for a table that documents your test cases. 

![alt tag](https://cloud.githubusercontent.com/assets/9201839/5372690/bde1e374-8001-11e4-8e93-1693ef004568.png)

- Test Name: A unique name for the test you are running
 
- Description: A concise explaination of the test you are running. Leave out unimportant details.

- Commands: The command you tried running on your shell.

- Steps: The steps you took in this test. For example, compile then run command.

- Expected Result: You should have ran this test case in `bash` to get an idea of what to do here. Jot this down.

- Actual Result: What actually happens with your shell. Notice the example above has a different result than the expected one. When successful these two will be the same. 

- Status: Pass if your expected and actual results are the same. Fail otherwise.

- Comments: Here you can state possible reasons for why your test case failed (if it did). Or you can put reminders for things to fix, or possible bugs that may come up later. 

- Reference: The source file and line number that contains the code that 1. dealt with your test and/or 2. contains the possible bug. 

I recommend a some sort of spread sheat for this table, since its a little more maneuverable than a table on Github or in _Vim_. However, you might find it a lot easier to write drafts of this table down in a notepad. And maybe your instructor will give you extra credit for a nice final draft of this table. (\*_cross fingers_\*). 

The ultimate goal of this table is to keep track of your successful test cases, and your test cases pending, so you can rest assured knowing that one important test case you thought of while you were furiously typing away is in a safe place where it won't ever be forgotten. It takes just a couple of seconds to write it down, and like a minute to fill in the rest of the row later after you are not in _the zone_. For cs100 students, you'll be thankful for it later if you're writing your test script in the waning minutes before your submission deadline for example.


don't mind this, just a _Failed table_
###### # |Test Name | Description | Command(s) | Steps | Expected Result | Actual Result | Comments | References
       - | -------- | ----------- | ---------- | ----- | --------------- | ------------- | -------- | ----------
 1 | Simple `ls` | `ls` no flags or args | `bin/ls` | 1. Compile 2. run `bin/ls` | Prints out none hidden directory files | _Woops_ accidentally printed out hidden `.` files | Must not have check for no `-a` flag | ls.cpp, lines 197-217



Good luck!
