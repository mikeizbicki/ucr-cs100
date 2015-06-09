#Video Tutorial on Strace

Strace is debugging tool that is used in linux to monitor things such as system calls, changes in processes and signals.

Video on how to read strace output

<a href="http://www.youtube.com/watch?feature=player_embedded&v=OSsQy9XLukM
" target="_blank"><img src="http://img.youtube.com/vi/OSsQy9XLukM/0.jpg" 
alt="Basic strace Video" width="480" height="360" border="10" /></a>

Flags covered in this video

|Flag	| Description of Use							|
|-------|-----------------------------------------------------------------------|
|-e	|traces a specific system call						|
|-o	|saves strace to an output file						|
|-p	|runs strace on a running process					|
|-t	|puts timestamps on each systemcall in strace				|
|-r	|puts relative time on each systemcall in strace			|
|-c	|outputs statistics about syscalls such as # of calls and errors	|
|-f 	|follows children							|


##Why use strace?

Strace is useful for checking if a program is behaving in an unexpected manner such as crashing or taking a long time. 
Strace works best when debugging system call errors as debuggers such as GDB more useful for finding errors in the program rather tahn errors regarding syscalls.
