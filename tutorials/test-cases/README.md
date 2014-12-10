###**Writing Test Cases for your Command Shell**
*A short explanation for students and curious programmers taking on such a project*

I. **_“If you are not trying to break your program, you probably didn't write a good one”_**

What are test cases? What is their purpose? Why are they important?

A test case is something that is meant to check whether or not a program does what it should be doing. It's you being a good programmer.
     
In 1998, NASA's _Mars Climate Orbiter_ was tasked with looking for water on Mars (among other things), but some of the programmers of this space vessel had been working with SI units while others had been working in English units. The result? The thrusters were 4.45 times more powerful than they should have been and this $327.6 million project is now lost in space, *for ever*. Talk about a failed test case. And these were *NASA* programmers. You can imagine how *buggy* our programs might be. Bugs are inevitable at whatever the level of a programmer (I recently updated my phone to Android 5.0 and my Chrome broswer and Messenger are *always* crashing!!). 

It's important to catch these failed test cases and fix them before they come back to bite is in the behind (before they affect our **GRADES**). Basically, we want to know where our program works, where it could use a little more work, and where its limitations are. This tutorial will hopefully get you thinking about how to do this.

II. **_“You must learn to bark before you can howl with coyotes.”_**

Before I get into how to write good test cases, I will reiterate something we all should already know, yet have the tendency to keep on doing for some crazy reason (if you are a student, maybe you _just_ started on the piece of your project that is due tomorrow. I have been there, done that!) : 

	Before you write code, know what the heck you are doing! 
    
At this point, if you are working on this project then you probably know your way around `C++` (or whatever other language you are using) and certain algorithms pretty well. But *are you you comfortable with* `C`? Specifically, *POINTERS*.  What do you know about *system calls* (these require knowledge of `C`), and which are needed to accomplish what you are trying to do? How the heck will you take in user input? _Parse_ input?? *Error checking*, who???? What in the world do *_forks_* have to do with this assignment?? You get the point. 
    
It will save a lot of **pseudo work** [insert hyper link to Cal Newport blog here] and precious time in the long run (**Time Arbitration** is key [insert hyper link to 'Time Arbitration' piece]). 

While you do this, feel free to fill in some sections of the test cases table (see the example table below). This will get you thinking about how you will write your program, and will ultimately help you with your test cases later. 

(meditation [hyper link here] does help relieve the stress of CS100 though!)

**tl;dr: "You must learn to fly before you can soar with eagles."**  

III. **“You don’t have to learn to be wise. If you just _flow_ you can be successful. Mother Nature will carry you.”**

You probably want to make things as easy as possible for yourself. Here are a few things you might want to consider doing while you are writing your program:
- Keep track of what you are doing in your program [insert hyperlink pseudo code tutorial here]
- Fill in the table. Or if you don't like the table, jot it down in a notebook where you can access it later. 
The last two points will help with writing your bigger test cases later. 

Another important thing to do is to test while you code!
- The most basic test case: DOES IT COMPILE?!! I'm sure you know how ugly those compilation errors can get. I personally have no patience with those long error messages. Have two terminal windows (or several) open to make writing and compiling simultaneously quick and easy (see Xmonad, Terminator [insert hyperlink here]). It is annoying to have to go back and forth between writing something in your text editor and compiling all in one terminal: Edit your program. Save your code. Exit your code. Compile your code. Get error messages. Reopen text editor. Forget error messages. Exit. Compile AGAIN. And so on.
- Is the snippet of code you just wrote doing what it should be doing? How does it interact with the rest of your program? Before you're in too deep, check. You might be surprised. 
Does your system call work? Does `fork` create a parent a parent and child process that begins right at that spot, or does it start from the beginning of the entire program? Why should I have to `wait` for my `chilren`? How does `execvp` handle `ls` by itself? With flags? Arguments? Such curiosity about `fork`, `wait`, `execvp` and other functions or system calls might come in handy later.
- Is there an error message where there should be and is it a good one that's not too loud, not too useless? Does the program _fail/exit_ with an _error_ when it should? In other words, error check. ALWAYS! (See `~/ucr-cs100/checksyscalls.sh`)

(talk about _Modularity_ here)

**tl;dr: "Better a thousand times careful than once dead."**

IV. **_“Don't count your chickens before they hatch.”_**
	
Alright, so finally your code seems to be working. The little parts look okay. You are now ready to begin testing the functionality of your program in its entire scope—or at least a bigger and more important part of it. Keep in mind that you might have to bounce back and forth (hopefully not too much) between _II_ and _III_. (See the example of how to use the table below for more on this)
	
Here, you'll want to think of **_every_ possible situation** that can arise when the specific section of your shell that you are currently focusing on is being used. This is where the test cases you thought of and wrote down (in your table) while researching what your program was meant to do, and while writing your program, come in handy. 

Consider asking the following questions and jot down what you come up with: 

1. What are the the simple case commands that should work? If you are using `execvp`, do `ls` and `pwd` work? If you are using `execve`, do `ls` and `pwd` work? Are `execvp` or `execve` using the flags and arguments you saved into an array and passed through? There are subtleties even in these simple examples. Of course, it is important to have these working before you can move on to more advanced test cases.
2. What are different combinations you can have? If you are required to be able to chain commands, do `ls; pwd` and `pwd||ls` and `ls &&pwd` work the way they should? If you are writing an `ls` program meant to implement some flags, do `ls -a -l -R` and `ls -lRa` work? Does order matter? And what happens when you insert some directories or files as arguments in between?
What are the limitations of your program? These are things that need to be working but for whatever reason do not. You do not know these limitations for certain, yet, since you haven't tested these cases, but you likely will have a hunch at this point. Jot down what happened so you can know what to fix or not fix if worked. 
3. What is your program realistically able to do at this point? For example, say you have only messed around with `forking` and `execvp`, then your program won't be working that well—or at all—with user input. Or if your current assignment is meant to get you acquainted with `execvp` and `fork`, you likely don't need to handle `piping` and `input/output redirection` (that might be a future assignment) quite yet. In other words, don't get unnecessarily carried away with your test cases.
	
After you have all these things written down, you are ready to start testing and recording what works and doesn't work. Ideally, your end product (example: the homework you turn in) will have all possible and necessary test cases taken care of. In certain cases, you should document in your `README.md` file [hyperlink to tutorial here] what behavior (bugs) your program has in certain test cases. Always be thorough with your test cases and your documentation. 

**tl;dr "It ain't over 'til the fat lady sings."**

IV. “A failure is only a step on the way to your success.”
	
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
Test Number | Test Name | Description | Commands | Steps | Expected Result | Actual Result | Comments | References
------------------------------------------------------------------------------------------------------------------






Good luck!
