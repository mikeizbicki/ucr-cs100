#Sigaction System Call


This file will include information pertaining to 'sigaction'. sigaction is used to examine and change a signal action. This system call is very important to understand in order to properly modify signals.


**includes: ** `#include <signal.h>`

**declaration: ** `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

**returns: ** will return 0 on success if the signal action has been changed. -1 is returned if an error has occured. 

[man page](http://man7.org/linux/man-pages/man2/sigaction.2.html)


In the function declaration, `int signum` is used to specify the signal. 
The argument `act` can be used depending on if it is a null pointer or not. If `act` is a null pointer, signal handling will remain unchanged and the call can mainly be used to gain knowledge of the current handling of a given signal. If it is not a null pointer, `act` will then point to a structure specifying the action to be associated with the specified signal. If `oldact` is not a null poointer, then the action that was most recently associated with the signal is stored into the variable.


##struct sigaction

`sigaction` also has a structure that can be used to describe an action being taken. With the struct comes different function member types that can be used with member names for various purposes.

For example,
1. If `void(*)(int)` then the member name that is used is `sa_handler` and is used to associate an action with the specified signal. 

2. If member type is `int`, then the member name used is `sa_flags` that are special flags that will affect the behavior of a signal. 

3. If member type is `sigset_t`, then the member name used is `sa_mask` which is primarily used as an additional set of signals to be blocked during execution of the signal-catching function. 


All the members of sigaction are defined in `signal.h` Listed above, are just a few members that are included, but many more are listed within the library.


###Flags
Within the different fields of struct sigaction, there are flags that can be used to carry out different processes. 

For example within the sa_flags field, defined in `signal.h` comes a 


Within sa_flags comes a full list of flags, defined in `signal.h` that can be set in sa_flags. 

For example,
1.  
2. 
3. 
4. 
5.  
 

Some example code can be shown below.

#include <signal.h>

void handler(int signum)
{
	struct temp_file *p;

	for (p = temp_file; p; p = p->next)
	{
		unlink(p->name);
	}
}

int main(void)
{
	struct sigaction new_action;
	struct sigaction old_action;

	new_action.sa_handler = handler;

	sigemptyset (&new_action.sa_mask);

	new_action.sa_flags = 0;

	sigaction(SIGINT, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction(SIGINT, &new_action, NULL);
	}

	sigaction (SIGHUP, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction(SIGHUP, &new_action, NULL);
	}

	sigaction (SIGTERM, NULL, &old_action);

	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction(SIGTERM, &new_action, NULL);
	}
}

In the code listed above, the function handler(int signum) takes the appropriate actions for signal delivery. In main, we can see that the function is used with the struct sigaction new_action, and with sa_handler. As listed above, sa_handler is used with the member function of type void()(int)'. This program is mainly used to terminate signals.

The new_action sstructure is loaded with the desired parameters and passed in with the sigaction call. `SIGTERM` is used mainly for program termination, `SIGHUP` is mainly sent once the terminal controlling it has been closed, and SIGINT interrupts the active signal.

This kind of example shows the usage of different signals and how each of them are used.

