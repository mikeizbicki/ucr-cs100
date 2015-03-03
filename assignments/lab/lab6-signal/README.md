# signal handling

You should complete this lab using pair programming with a new partner.

### coding instructions

Write a program called `handle_signals` that:

1.  Inside of an infinite loop, print the letter `X` to the stdout.  After you print each character, you must flush the buffer and pause for one second.

2. Whenever the user types a `^C` (interrupt), print the letter `C` to stdout.  DO NOT ABORT THE PROGRAM. 

3. Whenever the user types a `^\` (quit), print the character `\` to stdout.  DO NOT QUIT THE PROGRAM. 

4. Whenever the user types a `^Z` (stop), print the letter `S` to stdout.  Then stop the program.  You may resume the program using the `fg` command in the shell.

5. When `^Z` is pressed for the third time, print a summary of how many times `^C`, `^\`, and `^Z` were pressed.  Then exit the program.

### references

You should read the man pages for the `signal` and `sigaction` functions.

You may also find this tutorial helpful, but it is not required reading:  http://www.alexonlinux.com/signal-handling-in-linux

### deliverables

When finished, demo your working code for the TA.  
