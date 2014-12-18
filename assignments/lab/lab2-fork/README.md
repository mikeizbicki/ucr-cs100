# Unix `fork`
 
You should complete this lab using pair programming with a new partner.

### coding instructions

Write a program that uses `fork` to create 4 processes.  Each process should:

1.  Pick a letter in `ABCD` and print it 10000 times.  Each process should pick a different letter.  Flush the output after printing every character.

2.  Print every process's PID when it is created.

Be sure you do not leave any processes running.  You can check this with the command, `ps -aux`. 

**IMPORTANT:** A parent process must `wait` for each child after it has terminated, or that child will become a [zombie](https://en.wikipedia.org/wiki/Zombie_process).

Run your program multiple times and see that the output is different each time.

#### fun with fork bombs

The `fork` system call can be used to implement a simple [denial of service](https://en.wikipedia.org/wiki/Denial-of-service_attack) attack called a "fork bomb."  Find the `C` code for a fork bomb on the [wikipedia page](https://en.wikipedia.org/wiki/Fork_bomb).  Compile and run the fork bomb... can you defuse it?!

### deliverables

When finished, demo your working code for the TA.  

