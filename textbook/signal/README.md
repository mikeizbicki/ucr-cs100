#signal Tutorial

todo:there will be a video eventually

###What are signals and why do we care?
So you’re working on a program for Linux systems, and you’re wondering about things such as, “What’s the proper way to exit a program?” or “I want to interrupt my program when x happens in the OS”. Or, if you’re in lab, you wonder “What does my program do when the user does Ctrl-C? What if I don’t want to quit?” The answer: SIGNALS.

You hopefully should already know about how system functions return success/error codes, so it should be natural to see that the os has SIGNALS for certain events.

We can do three things to a signal:
* leave it alone (default behavior)
* ignore/block it (disable handling)
* overwrite the normal handler with something a little more fun :]

####Side note: using bitmasks
Depending on how far you’ve gotten in lecture, you will have seen bit masks. C programmers are big on being efficient, and so all the signals are stored as a single 32bit integer (but instead of the 32 bits representing a binary number, each 1 and 0 in there is a flag for a signal (on or off)). (technically there are 31 signals since 0 isn’t used)

We’ll learn about two ways to mess with these signals inside our own programs.


###signal()
	```
		signal(int signum, sighandler_t handler);
	```
signal is a unix syscall that takes 2 parameters: an int signum that is a signal such as SIGINT (interrupt, ^C) or SIGSEGV (a segfault); and a handler. This handler can be SIG_IGN (ignore), SIG_DFL (default) or it can also just be the name of a function that YOU wrote.

Be careful when you are overwriting the program exit signals such as ctrl + c, ctrl + \, ctrl + z; once you overwrite all of the exit functions of shell, you will not have any ways to exit them without exiting the actual terminal.

an example handler looks something like this:
	```
		void myhandler(int i)
		{
			if (i == SIGINT)
			insult_user();
		}
	```
and is simply passed into the signal call as a parameter
```
	signal(SIGINT, myhandler);
```
which you place in your code
```
int main()
{
	while(1)
	{
		signal(SIGINT, myhandler);
		//…
		sleep(100);
}
	return 0;
}
```

###sigaction()

Basically, it’s advised that nobody use signal() because it’s an older way of doing things, and because not every system will handle it the same way (*portability*). Instead, use sigaction().

Works similarly to signal(), but uses this structure creatively named sigaction.

You probably don’t need to know this, but if you’re curious, this is what is inside of a sigaction struct:

```
struct sigaction
    {
        void (*sa_handler)(int signum);
        void (*sa_sigaction)(int signum, siginfo_t *siginfo,
            void *uctx);
        sigset_t sa_mask;
        int sa_flags;
        void (*sa_restorer)(void);
    };
```
you can store your handler function inside of sigaction
```
struct sigaction myact;
myact.sa_handler = myhandler;  // simple
//OR
myact.sa_sigaction = myhandler; // detailed (wants to know the signal’s info, who called it)
```

When you use the advanced handler sa_sigaction, you need to also set sa_flags with SA_SIGINFO

```
myact.sa_sigaction = myhandler;
myact.sa_flags = SA_SIGINFO;
//Don’t worry about *uctx unless you are planning on writing a debugger.
```

sa_mask are the signals that you wish to block when you are running your handler. THIS INCLUDES THE SIGNAL THAT TRIGGERS YOUR HANDLER by default, unless you do SA_NODEFER in flags.

Like all syscalls, sigaction returns 0 on success, -1 on error

####the difference between signal() and sigaction();
signal() function does not necessarily block other signals from arriving while the current handler is executing.
sigaction() function DOES block other signals

The signal() function resets the signal action back to default for almost all signals; signal handler must reinstall itself as its first action.
