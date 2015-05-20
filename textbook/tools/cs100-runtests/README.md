#CS100 Runtests

##Table of Contents
1.[What is cs100-runtests?] (#what-is-cs100-runtests?)  
2.[Installation] (#installation)  
3.[How do I use it?] (#how-do-i-use-it?)  
    3a.[The Vim Pane] (#the-vim-pane)  
    3b.[The Shell Pane](#the-shell-pane)  
    3c.[The Runtests Controller Pane] (#the-runtests-controller-pane)  
4.[An Example Walkthrough] (#an-example-walkthrough)  
5.[Features](#features)  

##What is cs100-runtests?
``cs100-runtests`` is a script developed to assist testing of student-made bash shells.
(Specifically, "rshells" developed by UCR CS-100 students)

##Installation
Before installing ``cs100-runtests``, you must first install ``tmux``.
For Ubuntu, the command is:
```
sudo apt-get install tmux
```
``tmux`` is required for ``cs100-runtests`` to work properly.

Installing ``cs100-runtests`` is as simple as cloning this repository. For those unfamiliar with how, enter the following in your terminal:
```
git clone https://github.com/M-Evans/runtests
```

##How do I use it?
Once you have installed ``cs100-runtests``, run it with the command:
```
cs100-runtests <shell> <testcasefile>
```
where ``<shell>`` is the shell you want to test (e.g. ``bin/rshell``, ``sh``, ``bash``, etc.) and <testcasefile> is the path to the file containing all of the test cases you would like to use on your shell.
These parameters are optional, as runtests will default to ``bin/rshell`` if no shell is entered, and it is possible to load a test case file within the program after the script has been run.

Three panes are created when ``cs100-runtests`` is started.
The left pane is the [Vim Pane](#the-vim-pane), which contains an open grade file that is created in the current directory. 
The upper right pane is the [Shell Pane](#the-shell-pane), where the user-input <shell> (or default ``bin/rshell``) is started.
The lower right pane is the [Runtests Controller Pane](#the-runtests-controller-pane). All commands for ``cs100-runtests`` are entered here.

###The Vim Pane
The Vim Pane is controlled with the following commands:
* ``g <line> <amount>`` or ``grade <line> <amount>`` places the amount entered as a grade on the line entered.
* ``f <line>`` places a full score on the entered line. 
  * Nothing happens when these commands are entered if ``<line>`` is not a properly-formatted grade line.
* ``zero`` makes all grades 0.
* ``full`` makes all grades maximum.

###The Shell Pane
The Shell Pane is controlled with the following commands:
* ``n`` or ``next`` runs the next test case loaded from the test case file.
* ``p``, ``previous``, ``b``, or ``back`` runs the previous test case loaded from the test case file.
  * Note: Pressing enter following a ``next`` or ``previous`` command will repeat it.
* ``l <testcasefile>`` or ``load <testcasefile>`` loads <testcasefile> into rshell, discarding previously loaded test cases.

###The Runtests Controller Pane
The Runtests Controller Pane is controlled with the following commands:
* ``c`` or ``clear`` clears the controller screen.
* ``e``, ``exit``, ``q``, or ``quit`` ends the program.
* ``h`` or ``help`` prints a small help message detailing the controls for ``cs100-runtests``.
  * ``h?``, ``?h``, ``?``, and ``??`` also print the help message.

##An Example Walkthrough
This walkthrough will familiarize you with the basic features and usages of ``cs100-runtests``.

First, start cs100 runtests as such:
```
./cs100-runtests bin/rshell exampleFolder/exampleTestCaseFile
```

You will see the [Vim Pane](#the-vim-pane) to the left, the [Shell Pane](#the-shell-pane) to the upper right, and the [Runtests Controller Pane](#the-runtest-controller-pane) to the lower right. 
The controller will let you know if you test case file was successfully loaded, and print out the commands available.

(screenshot1 here)

First we will step through one test case. Type ``n`` or ``next`` and press Enter. 
The first test case should be run, and the result printed in the Shell Pane.

(screenshot2 here)

Step through another test case by just pressing ``Enter``. 
This utilizes the previous command repeating feature. 
If no commands are specified, pressing ``Enter`` will run the previously entered command.

(screenshot 3 here)

Now let's try running a previous case. 
Type in ``p`` or ``previous`` and hit ``Enter`` as many times as you would like. 
Notice that the controller prints an error message when you attempt to run more test cases commands after the first one has been executed.

(screenshot 4 here)

Let's step forward four times (``next``). Make sure to take advantage of the previous command repeating feature. 
Now step through one more test case and...

You'll notice that our ``bin/rshell`` has finished executing. 

(screenshot 5 here)

There is no need to quit and restart ``cs100-runtests`` when this is encountered. 
Simply run the next test case and ``cs100-runtests`` will restart ``bin/rshell``. 
You will also be notified that ``bin/rshell`` has been restarted.

(screenshot 6 here)

Step through the next test case. This one backgrounds the shell.
Fortunately, ``cs100-runtests`` is able to use job control to bring back the stopped process. Try the last case.

(Screenshot 7 here)

Now that we have run out of test cases, let's try to run more. 
Step forward as many times as you would like to. The controller prints out an error notifying you that you have run out of test cases.

(screenshot 8 here)

Now that we have finished testing the ``shell``, let's grade it. First, zero out all of the grades by entering ``zero`` in the controller pane. 

(screenshot 9 here)

Let's say the student earned full credit for the objectives on lines 5 and 7.
To enter their grades, type in:
```
f 5
f 7
```
Perhaps they received 4 points for the objective on line 6:
```
g 6 4
```
And received 11 points for the objectives on lines 8 and 9:
```
g 8 11
g 9 11
```
(screenshot 10 here)

If you wanted to give a full grade for every objective on every line, run ``full``.

(screenshot 11 here)

Now that we are done testing and grading ``bin/rshell``, type ``exit`` and hit ``Enter`` to stop running ``cs100-runtests``.

Congratulations. You now know the basic features of ``cs100-runtests``.

##Features
* If ``shell`` isn't running in the shell pane, it is restarted, and the grader is notified.
  * This allows for multiple ``exit`` commands in the same test file.
* If ``shell`` is backgrounded, the controller will attempt to foreground it.
  * ``sh`` must have job control enabled in order for this to work properly.
* The ``cs100-runtests`` session will be terminated when:
  * ``SIGINT``, ``SIGQUIT``, ``SIGTERM``, ``SIGTSTP`` signals are received  
  * ``read`` exits with an error
	  - This will happen when the user types ``Control+D`` after nothing else when prompted for a command.
* The mouse can be used to shift focus between all three panes.
* Pressing enter without entering a command will run the previously entered command. (useful for speeding through test cases)
* The previous command is displayed in the prompt.
