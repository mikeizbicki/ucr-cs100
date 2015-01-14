Test Cases
==========


Finding and fixing _bugs_ is an important part of the programming process. A bug you didn't know existed can come back to haunt you later. For example, consider NASA's Mars Climate Orbiter which, in 1998, was tasked with looking for water and studying the weather on Mars. However, some of its programmers had been working in SI units while others had been working in English units. The result from this lack of communication was a _bug_ that made the thrusters 4.45 times more powerful than they should have been. This $327.6 million project was consequently lost in space, most likely in pieces. 

No program is ever perfect (not even those that NASA writes). But a good programmer makes a habit out of making sure her or his program is as bugless as possible.

The aim of test case writing is to separate a program into small, important units that produce a quantifiable result. For example, the quality of our shell can be measured by test cases that examine functionality and usability. Test case writing should make knowing how well a program works as easy and efficient as possible.

**Test Design Strategies:**

The following are useful strategies for test case writing.

- Branch Coverage Test Design: Testing is devised with decision making points in the source code in mind. A decision point is an important segment of code where the program in question _**changes course**_ (_branches off_). This method is effective when all the important decision point combinations are tested.

  - Decision points and branching off occur when your program decides how to handle the **child** and **parent** processes when the connectors `;`, `||`, or `&&` are used. The test case `ls || pwd` should only execute one command or the other (the first that doesn't fail) but not both, while the test case `ls && pwd` executes both commands as long as the first one doesn't fail, and the test case `ls ; pwd` attempts to execute both commands. The logic for when the parent and child processes should end or continue is different for each connector.  

- Equivalence Class Partitioning: Think of an equivalence class as a set of test values that are similar enough that it is sufficient to test one or two and determine that the rest work, too. This style of testing eliminates redundancy, allowing the tester to move on to another part of testing.

  - For example, if `ls` by itself works then `pwd` and most other _Bash_ commands should also work by themselves. There is _definitely_ no need to test all of them. 

- Boundary Value Test Design: This strategy is used when the tester is aware of bugs in the program for certain test values. The boundary around those buggy test values is tested in order to determine the extent of the problem.

  - Consider a bug with the command `ls;pwd` in your shell. It is likely an issue with your parsing method or your forking method and child process handling. Boundary test values will therefore include 
    - different spacing between commands and connectors: `ls ; pwd`, `ls; pwd`, `ls ;pwd`, and `ls    ;     pwd`. It may not seem like it, but these are likely to cause trouble. 
    - varying amounts of chained commands: `ls; pwd; ls -a dir; ....` where each chained command should be executed by a separate process. 
    - different connectors: `ls|| pwd ` or `ls -l . && pwd` 

- Specification Based: Test functionality against existing specifications. For example, check what _Bash_ does then run that same test on your shell. The `info` command and `--help` flag also give useful information (try `info ls` and `ls --help` as an example). 

  - Consider the second homework assignment, where you are tasked with implementing `ls`. The following is output in Bash when `ls -l` is run:

  ```
  $ ls -l
  total 24
  drwxrwxr-x 2 owner group 4096 Dec 18 23:38 dir1
  drwxrwxr-x 2 owner group 4096 Dec 18 23:38 dir2
  -rw-rw-r-- 1 owner group    0 Dec 18 23:38 file1
  -rw-rw-r-- 1 owner group    0 Dec 18 23:38 file2
  ```

   `total 24` indicates that there are 24 disk blocks taken by the directory, while the first column in the following lines indicates the type of file and the read, write, and execute permissions for the owner of the file, the group, and all other users. The following columns are the number of hard copies, owner name, group name, size in bytes, time stamp, and the name of the file. There are many more subtleties with the different combinations of all three flags you have to implement (`-a`, `-l`, `-R`), such as the order the `.` files take in the listing of all the files or the order in which to recurse subdirectories and print their contents. Take an incremental approach, making sure you have the test cases for one flag at a time working first, then two flags, and finally all three. 
  

- Risk Based: In this approach, the tester attempts to break the program in order to get an idea of what still needs work.
  
  - For example, say I am implementing `ls` (second homework assignment). I know `ls -a -l -R` works fine, but does `ls -alR`, and even `ls dir1 -la file1 -RaRaRa dir1 -l file2`, work? The latter two examples should work and may even find an issue. 

- Negative Test Cases: Test whether the program _does not_ do things that it _shouldn't_. The tester looks for any funny behavior in the program. These tests check whether there are appropriate error checks and error messages where there should be.
  
  - For the fourth homework assignment, I was tasked with implementing the `cd` command. Everything worked great when I had the usual `cd dir`, but when I had `cd` by itself or `cd dir1 dir2 ...` my entire shell crashed. It turns out I accidentally called `exit(1)` in my code if the user gave anything other than one argument for `cd`. I totally missed this _negative test case_.
  - Appropriate error checks: For every system call, run some tests that will cause it to fail to make sure your program exhibits the appropriate behavior.


Combining these approaches is likely to yield good results.


**Writing Test Cases:** 

The main idea behind writing test cases is to be as effective and to the point as possible. There is no need to get overly complex as long as the essential parts of the program are tested adequately.

- Get the necessary background:
  
  - What features should be implemented? 
  - How will users interact with the program?
  - What system calls do you need, and how do they work?
  - Study the requirement specifications
  - Look at available documentation (see _[Bash's source code](https://www.gnu.org/software/bash/)_)
  - Try Bash itself on your Linux system

- Decide on a test case writing strategies: 
  - Certain parts will require different strategies. You should know the program you are testing well enough to know which parts need what. Make sure the entire flow of you program is covered by your test cases.

- Use a test case template for documentation:
  - This should be a minimally complicated part of the test case writing process. It is an important part nonetheless. Done correctly, documentation of test cases will increase efficiency by allowing focus on actually coming up with test scenarios and by being a quick reference when needed later.

![screenshot from 2014-12-17 01 26 31](https://cloud.githubusercontent.com/assets/9201839/5469090/32cb6676-858c-11e4-99a3-2ff32a382fdb.png)

The above template lets you document test cases and the useful information that goes along with them in a neat fashion.

- Description: This column gives a brief explanation of the test case. It should be easy to read and understand for you and others who may look at it later.
- Commands: These are the commands that are being tested. Ideally, these will not be neither redundant nor overly complex.
- Expected Result: This is the behavior that the requirement specs call for. Be sure to also reference your machine's Bash terminal for exactly what should happen.
- Actual Result: This column contains a brief message addressing the actual result of the test case. A simple "same as expected" is enough when the test case succeeds. 
- Status: Either "pass" or "fail". If the test case is not entirely working--for example 97% working--then it should still be consider a "fail" until the issue is fully fixed.
- Comments: This is a concise message stating the possible reasons for a failed test case and any other issues that need to be addressed. When a test case changes status from "fail" to "pass", this message should keep a brief summary of the bug that was fixed.
- Reference: The source file and the line numbers that (1) contains the code that dealt with the test and/or (2) possibly contains the bug.

	
Here is an example of how to fill in the test table. The program in question implements a basic version of the _Bash command shell_ using `execvp`, `fork`, and `waitpid` (see [requirement specs](https://github.com/mikeizbicki/ucr-cs100/blob/cs100-2014fall/assignments/hw/hw0-rshell/README.md) for this program). These are only some of the possible test cases I tried.


![test-1](https://cloud.githubusercontent.com/assets/9201839/5503021/bae61ccc-8726-11e4-9890-cfa0b788e38a.png)
![test-2](https://cloud.githubusercontent.com/assets/9201839/5503018/b73ca596-8726-11e4-8dc7-e5209c6a93f1.png)
![test-3](https://cloud.githubusercontent.com/assets/9201839/5503015/b3d547fa-8726-11e4-87a0-cfb34b3b5925.png)


Notice the trend in the failed test cases: _parsing_ fails when connectors have no spacing between them and other text, like "..-f**&&**ls...". Having it all documented allows the tester to see the extent of the problem: the issue appears for all three connectors, `;` `||` and `&&`, which can be considered _boundary values_.

Writing test cases requires some creativity on the tester's part, but they shouldn't be the most difficult part of creating a command shell. The above tips and tools will help make this a bit easier.
