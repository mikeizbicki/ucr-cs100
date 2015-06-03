#hw3 FAQs

Below are some simple answers to the most frequently asked questions on hw3, with links to the issues they are referenced from.


##signals

Can we use `signal()` instead of `sigaction()`?  
No, [you can't.](https://github.com/mikeizbicki/ucr-cs100/issues/1625)


##errors

Do I need to do any new error-checking?  
Yes, [library calls should be checked.](https://github.com/mikeizbicki/ucr-cs100/issues/1640)

My program hangs after catching a signal, what do I do?  
Besides checking that your signal handler is only trying to kill children,
you should check if [errno was set to EINTR.](https://github.com/mikeizbicki/ucr-cs100/issues/1626)

