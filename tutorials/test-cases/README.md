Test Cases
==========

**What is a “test case”?**

The IEEE defines test case writing as “Documentation specifying inputs, predicted results, and a set of execution conditions for a test item.” And the computer scientist and author, Glenn Meyers, says that a test case is “a process of executing a program with the intent of finding an error.” A test case essentially checks that a program works as it should.

Finding and fixing _bugs_ is an important part of the programming process. A bug you didn't know existed can come back to haunt you later. For example, consider NASA's Mars Climate Orbiter which, in 1998, was tasked with looking for water and studying the weather on Mars. However, some of its programmers had been working in SI units while others had been working in English units. The result from this lack of communication was a _bug_ that made the thrusters 4.45 times more powerful than they should have been. This $327.6 million project was consequently lost in space, most likely in pieces. 

No program is ever perfect (not even those that NASA writes). But a good programmer makes a habit out of making sure her or his program is as bugless as possible.

The aim of test case writing is to separate a program into small, important units that produce a quantifiable result. For example, the quality of our shell can be measured by test cases that examine functionality and usability. Test case writing should make knowing how well a program works as easy and efficient as possible. Here are some questions that test cases should address: 

1. What scenarios have been tested and which still need to be tested?
2. Which parts of the program are stable? What parts are unstable?
3. Where does the program need more work?
4. Have enough possibilities and input combinations been tested?
5. Is there appropriate error checking and error messages? (negative test cases)
6. Is the User Interface (UI) similar enough to Bash's UI? (the command prompt for example)
7. Are the required features working? (the assignment specifications)
8. Have the possible scenarios been documented? Are these scenarios in a working state?
9. Are the tests strong enough? Are the tests finding issues in the program? 
10. What is the overall quality of the segment of the shell you just implemented? The entire shell?


**Types of Test cases:** 

- Unit Test Case: Every line of code is tested thoroughly. This is done at the development stage. It should go into the intricate details of the program to ensure that these are working correctly.

- Functional Test Case: The program is tested at the functional level. This checks if a given function or segment of code does the job it is designed to do. 

- System Test Case: The complete, integrated program is tested to check its compliance with predefined requirements. The purpose is to look for inconsistencies when the units are integrated together. 

- User Acceptance Test Case: The program is tested at the operational level. Testing here is based on scenarios the shell will encounter during its use. 

**Test Design Strategies:**

The following are useful strategies for test case writing.

- Branch Coverage Test Design: Testing is devised with decision making points in the source code in mind. A decision point is a place that may include a an _important_ conditional `if` or `else` statement, a `for` or `while` loop, or some function or chunk of code where the program in question _**changes course**_ (_branches off_). This method is effective when all the important decision point combinations are tested.

  - Decision points and branching off occur when your program decides how to handle the `child` and `parent` processes when the connectors `;`, `||`, or `&&` are used. `ls || pwd` should only execute one command or the other (the first that doesn't fail) but not both, while `ls && pwd` executes both commands as long as the first one doesn't fail, and `ls ; pwd` attempts to execute both commands. Notice that in some cases all parent and child processes should end, while in others they should continue. 

- Equivalence Class Partitioning: Think of an equivalence class as a set of test values that are similar enough that it is sufficient to test one or two and determine that the rest work, too. This style of testing eliminates redundancy, allowing the tester to move on to another part of testing.

  - For example, if `ls` by itself works then `pwd` and most other _Bash_ commands should work by theirselves. You could therefore move on to an equivalence class that includes _flags_ and _arguments_ for a command, such as `cmd [flags] [args]`. 

- Boundary Value Test Design: This strategy is used when the tester is aware of bugs in the program for certain test values. The boundary around those buggy test values is tested in order to determine the extent of the problem.

  - Consider a bug with the command `ls;pwd` in your shell. It is likely an issue with your **_parsing_** method or your **_forking_** method and **_child process_** handling. Boundary test values will therefore include 
    - different spacing between commands and connectors: `ls ; pwd`, `ls; pwd`, `ls ;pwd`, and `ls    ;     pwd`. It may not seem like it, but these are likely to cause trouble. 
    - varying amounts of chained commands: `ls; pwd; ls -a dir; ....` where each chained command should be executed by a separate process. 
    - different connectors: `ls|| pwd ` or `ls -l . && pwd` 

- Specification Based: Test functionality against existing specifications. For example, ask “What does the Bash do?” Check what _Bash_ does then run that same test on your shell.

- Risk Based: In this approach, the tester attempts to break the program in order to get an idea of what still needs work.
  
  - For example, say I am implementing `ls` (second homework assignment). I know `ls -a -l -R` works fine, but do `ls -alR` or `ls file1 -la file2 file3 -R file4` work? The latter two are more likely to find an issue. 

- Negative Test Cases: Test whether the program _does not_ do things that it _shouldn't_. The tester looks for any funny behavior in the program. These tests check whether there are appropriate error checks and error messages where there should be.
  
  - For one of my homework assignments, I was tasked with implementing the `cd` command. Everything worked great when I had the usual `cd dir`, but when I had `cd` by itself or `cd dir1 dir2 ...` my entire shell crashed. It turns out I accidentally called `exit(1)` in my code if the user gave anything other than one argument for `cd`. I totally missed this _negative test case_.
  - Appropriate error checks for system calls and `perror` messages are important: Make a test cases in which `exec*()` , `readir()`, `stat()`, `dup()` and other functions/system calls will fail. Make sure your program exhibits the appropriate behavior.


Combining two or more of these approaches  at a time is likely to yield good results.


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

The above template allows the tester to document test cases and useful information that goes along with them in a clean fashion.

- Description: This column gives a brief explanation of the test case. It should be easy to read and understand for you and others who may look at it later.
- Commands: These are the commands that are being tested. Ideally, these will not be neither redundant nor overly complex.
- Expected Result: This the behavior that the requirement specs call for. Be sure to also reference your machine's Bash terminal for exactly what should happen.
- Actual Result: This column contains a brief message addressing the actual result of the test case. A simple "same as expected" is enough when the test case succeeds. 
- Status: Either "pass" or "fail". If the test case is not entirely working--for example 97% working--then it should still be consider a "fail" until the issue is fully fixed.
- Comments: This is a conscise message stating the possible reasons for a failed test case and any other issues that need to be addressed. When a test case changes status from "fail" to "pass", this message should keep a brief summary of the bug that was fixed.
- Reference: The source file and the line numbers that (1) contains the code that dealt with the test and/or (2) possibly contains the bug.

	
Here is an example of how to fill in the test table. The program in question implements a basic version of the _Bash command shell_ using `execvp`, `fork`, and `waitpid` (see [requirement specs](https://github.com/mikeizbicki/ucr-cs100/blob/cs100-2014fall/assignments/hw/hw0-rshell/README.md) for this program). These are only some of the possible test cases I tried.

![screenshot from 2014-12-16 23 38 05](https://cloud.githubusercontent.com/assets/9201839/5468037/df8d176a-857d-11e4-9f61-4a18ecafcc2d.png)
![screenshot from 2014-12-16 23 38 46](https://cloud.githubusercontent.com/assets/9201839/5468045/e78666d8-857d-11e4-945e-3cbc836670c2.png)
![screenshot from 2014-12-16 23 39 01](https://cloud.githubusercontent.com/assets/9201839/5468060/0ea8e5a6-857e-11e4-973c-e43116386799.png)

Notice the trend in the failed test cases: _parsing_ fails when connectors have no spacing between them and other text, like "..-f**&&**ls...". Having it all documented allows the tester to see the extent of the problem: the issue appears for all three connectors, `;` `||` and `&&`, which can be considered _boundary values_.

Writing test cases requires some creativity on the tester's part, but they shouldn't be the most difficult part of creating a command shell. The above tips and tools will help make this a bit easier.
