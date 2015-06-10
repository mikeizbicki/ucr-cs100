#Sigaction System Call


This file will include information pertaining to 'sigaction'. sigaction is used to examine and change a signal action. This 
system call is very important to understand in order to properly modify signals.


**includes:** `#include <signal.h>`

**declaration:** `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

**returns:** will return 0 on success if the signal action has been changed. -1 is returned if an error has occured. 

[man page](http://man7.org/linux/man-pages/man2/sigaction.2.html)


In the function declaration, `int signum` is used to specify the signal. 
The argument `act` can be used depending on if it is a null pointer or not. If `act` is a null pointer, signal handling will 
remain unchanged and the call can mainly be used to gain knowledge of the current handling of a given signal. If it is not a 
null pointer, `act` will then point to a structure specifying the action to be associated with the specified signal. If 
`oldact` is not a null poointer, then the action that was most recently associated with the signal is stored into the 
variable.


##struct sigaction

`sigaction` also has a structure that can be used to describe an action being taken. With the struct comes different function
member types that can be used with member names for various purposes.

For example,

```
1. If `void(*)(int)` then the member name that is used is `sa_handler` and is used to associate an action
with the specified signal. 

2. If member type is `int`, then the member name used is `sa_flags` that are special flags that will 
affect the behavior of a signal. 

3. If member type is `sigset_t`, then the member name used is `sa_mask` which is primarily used as an 
additional set of signals to be blocked during execution of the signal-catching function. 

```

All the members of sigaction are defined in `signal.h` Listed above, are just a few members that are included, but many more 
are listed within the library.


###Flags
Within the different fields of struct sigaction, there are flags that can be used to carry out different processes. 

For example within the sa_flags field, defined in `signal.h` comes a  full list of flags that can be set and used for various
purposes. 

For example,

1. SIG_BLOCK - Union of the current set and the signal set.

2. SA_RESTART - Causes certain functions to become restartable.

3. SS_DISABLE - Alternate signal stack will get disabled.

Above are just a few flags, but the list of flags goes to nearly 15, all serving different purposes relating to disabling, 
enabling, changing functions, or modifying sets.

For a full list of the flags, refer to [signal.h](http://pubs.opengroup.org/onlinepubs/007908775/xsh/signal.h.html)
 
##Examples

Below is some example code which shows how sigaction is called and used for different signals. The code will call sigaction 
to deal with termination of the program.

```
#include <signal.h>

void handler(int signum)
{
	struct temp_file *p;

	for (p = temp_file; p; p = p->next)
	{
		unlink(p->name);
	}
}
```

In the code above, a function is declared in order to deal with signal handling. The signals that will be focused on will 
mainly deal with termination and interruption, but the handler here deals deleting temporary files when certain fatal signs 
happen. 

```
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
```

In the code listed above, the function handler(int signum) takes the appropriate actions for signal delivery. In main, we can
see that the function is used with the struct sigaction new_action, and with sa_handler. As listed above, sa_handler is used 
with the member function of type void()(int)'. This program is mainly used to terminate signals.

The new_action sstructure is loaded with the desired parameters and passed in with the sigaction call. `SIGTERM` is used 
mainly for program termination, `SIGHUP` is mainly sent once the terminal controlling it has been closed, and `SIGINT` 
interrupts the active signal. So why didn't we use something like `SIGQUIT?` A signal that quits the program. This example 
mainly proivdes information for debugging and then the temporary files may provide useful information. 

Also note that if a given signal was set to be ignored, this code will alter that setting. This happens normally because 
shells are used to ignoring certain signals once a child is started. But, this kind of example shows the usage of different 
signals and how each of them are used and how it all goes back to working towards the same goal of termination.

Another example that you can use to see how sigaction works is shown below. 

```
void handle_sigalrm(int signum){
	if (signum != SIGALRM){
		perror("Wrong signal");
	}
	
	printf("SIGALRM caught");
}
``` 
We first show the void handle_sigalrm function that will handle the sigalrm signal. You'll see a better example of how this 
will work in main.

```
int main(){
	struct sigaction sa;
	sigset_t mask;
	
	sa.sa_handler = &handle_sigalrm;
}
```

Now stop! Before we continue, this line right here is important to understand. With sa.sa_handler being set to handle_sigalrm
passed by reference it essentially intercepts and ignores the SIGALRM signal.

```
	sa.sa_flags = SA_RESETHAND;
```

Now we see the usage of sa_flags again, but this time being set to the signal SA_RESETHAND. This will remove the ahandler 
after the first signal passed through. Once the signal is caught, that is when sigaction will be called.

```
sigaction(SIGALRM, &sa, NULL);
```

So signals can be blocked, ignored, or caught. Almost like flies. Catch the flies you want and use them as you seee fit, or 
just ignore them but the more they fly around the more annoying it will be for you. 
