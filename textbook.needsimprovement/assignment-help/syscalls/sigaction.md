#Sigaction System Call


This file will include information pertaining to `sigaction.` This system call is used to examine and change a signal action and is very important to understand in order to properly modify and handle signals.


**includes:** `#include <signal.h>`

**declaration:** `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

**returns:** will return 0 on success if the signal action has been changed. -1 is returned if an error has occured. 

[man page](http://man7.org/linux/man-pages/man2/sigaction.2.html)


For a full list of the flags included in the `sigaction` structure, refer to [signal.h](http://pubs.opengroup.org/onlinepubs/007908775/xsh/signal.h.html)
 
##Examples

Below is some example code which shows how `sigaction` is called and used for different signals. The code will call `sigaction` 
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

In the main function, we can see that the function is used with the struct sigaction `new_action,` and with `sa_handler` which is used with the member function of type `void()(int)`. This program is designed to terminate signals.

The new_action structure is loaded with the desired parameters and passed in with the sigaction call. `SIGTERM` is used for program termination, `SIGHUP` is mainly sent once the terminal controlling it has been closed, and `SIGINT` 
interrupts the active signal. 

Also note that if a given signal was set to be ignored, this code will alter that setting. This happens normally because shells are used to ignoring certain signals once a child is started. But, this kind of example shows the usage of different signals and how each of them are used and how it all goes back to working towards the same goal of termination.

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

Now stop! Before we continue, this line right here is important to understand. With `sa.sa_handler` being set to `handle_sigalrm,` it essentially intercepts and ignores the SIGALRM signal.

```
	sa.sa_flags = SA_RESETHAND;
```

Now we see the usage of `sa_flags` again, but this time being set to the signal `SA_RESETHAND.` This will remove the handler after the first signal passed through. Once the signal is caught, that is when sigaction will be called.

```
sigaction(SIGALRM, &sa, NULL);
```

So signals can be blocked, ignored, or caught. Almost like flies. Catch the flies you want and use them as you see fit, or just ignore them but the more they fly around the more annoying it will be for you. 
