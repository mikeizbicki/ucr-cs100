cppcheckTutorial
================

As a heads up, if you are here trying to figure out how to use this tool for Windows, we can not be sure
that everything discussed will work. This tutorial was written mainly for Linux users as that is what we 
are using.


Quick Info
==========
Cppcheck is a static code analysis tool for the C/C++ programming 
languages. It is a versatile tool that can check non-standard code. The 
creator and lead developer is Daniel Marjamäki. Unlike C/C++ compilers and 
many other analysis tools it does not detect syntax errors in the code. 
Cppcheck primarily detects the types of bugs that the compilers normally do
not detect. 
The goal is to detect only real errors in the code. 

Cppcheck is free software under the GNU General Public License.


HOW TO INSTALL
==================
Windows: 
	In order to install for Windows, it must be downloaded from their
	website which can be found at http://cppcheck.sourceforge.net/
	After downloading, run the .msi file and it should install automatically.

Linux:
	In order to install for Linux you can simply run the following command:

```
sudo apt-get install cppcheck
```

Mac:
	We were not able to figure out how to install onto Mac, We would recommend to either ssh
	into a server that can use it or to explore the wonders that is the internet and figure it
	out. If you do, you are more than welcome to contriubte that to this project.


Optional arguments
====================

--append=\<file\>

	This allows you to provide information about functions by providing an implementation for these.

-D\<id\>

	By default Cppcheck checks all configurations. Use -D to limit the checking. When -D is used the 
	checking is limited to the given configuration. Example: -DDEBUG=1 -D__cplusplus

--enable=\<id\>
	Enable additional checks. The available ids are:

	all

		Enable all checks

	style

		Check coding style
		
	information

		Enable information messages

	unusedFunction

		Check for unused functions. 
		(This is pretty useful to clean up the source code.
		These funcitons may cause little gremlins later when trying to debug. 
		From experience, I have tried to fix bugs but tried fixing it by making
		changes to a function that is no longer been used. Three hours later, it was
		finally pointed out to me what I was doing...).
	
	missingInclude

		Check for missing include statements.

By default none of the additional checks are enabled. Several ids can be given if you separate them 
with commas, e.g. --enable=style,unusedFunction.

--error-exitcode=\<n\>

	If errors are found, integer <n> is returned instead of default 0. EXIT_FAILURE is returned 
	if arguments are not valid or if no input files are provided. Note that your operating 
	system can modify this value, e.g. 256 can become 0.

--errorlist

	Print a list of all possible error messages in XML format.

--exitcode-suppressions=\<file\>

	Used when certain messages should be displayed but should not cause a non-zero exitcode.

--file-list=\<file\>

	Specify the files to check in a text file. One filename per line.

-f, --force

	Force checking of files that have a lot of configurations. Error is printed if such a file is 
	found so there is no reason to use this by default.

-h, --help

	Print help text.

--inline-suppr

	Enable inline suppressions. Use them by placing comments in the form: 
	// cppcheck-suppress memleak before the line to suppress.

-q, --quiet

	Only print something when there is an error.

--report-progress

	Report progress when checking a file.

--rule=\<rule\>

	Match regular expression to create your own checks. E.g. rule "/ 0" can be used to check 
	division by zero.

--rule-file=\<file\>

	Use given rule XML file. See https://sourceforge.net/projects/cppcheck/files/Articles/ for more 
	info about the syntax.


--suppress=\<spec\>

	Suppress a specific warning. The format of <spec> is: [error id]:[filename]:[line]. The 
	[filename] and [line] are optional. [error id] may be * to suppress all warnings (for a 
	specified file or files). [filename] may contain the wildcard characters * or ?.

--suppressions-list=\<file\>

	Suppress warnings listed in an included file. Each suppression is in the format of <spec> above.

-v, --verbose

	More detailed error reports

--xml

	Write results in XML to error stream


How To Use cppcheck
===================

There are more code examples provided in the example files.

```
int main()
{
	char a[10];
	a[10] = 0;

	return 0;
}
```

In the above code, the glaring error is the out of bounds assignment into the char array a.
Now to compile with nothing but the basic cppcheck commands, `cppcheck <filename>` is called in the command line
prompt.

The returned error from cppcheck is as follows:

```
Checking badcode.cpp...
[badcode.cpp:10]: (error) Array 'a[10]' accessed at index 10, which is out of bounds.
```

Simply what this error states is that there is an assignment accessed at an out of bounds index. This is just one
method of using cppcheck to check your code for errors the compiler will not check at compile time.

Given the specific flags such as the `--enable=<id>` flag, you can test your code for a larger variety of errors.

Users should also configure cppcheck before diving into the program so that the checker will check the things the
user wants it to check. 

Given the configuration and usage syntax of:
```
cppcheck [--append=<file>] [-D<id>] [--enable=<id>] [--error-exitcode=<n>] [--errorlist]
[--exitcode-suppressions=<file>] [--file-list=<file>] [--force] [--help] [-I<dir>] [-i<dir>] [--inline-suppr]
[-j<jobs>] [--quiet] [--report-progress] [--rule=<rule>] [--rule-file=<file>] [--style] [--suppress=<spec>]
[--suppressions-list=<file>] [--template '<text>'] [--verbose] [--version] [--xml] [--xml-version=<version>]]
[file or path] ...
```
the end user can customize the way the program functions in a number of ways such as error suppression or batch
processing a directory of files.


##Using cppcheck With Other Programs

cppcheck can be configured to work with a number of development tools and is included in tools such as:
* Code::Blocks
* CodeDX
* CodeLite
* CppDepend 5

and can be installed as a package in tools such as:
* Eclipse ([Cppcheclipse](http://cppcheclipse.googlecode.com/))
* gedit ([plugin](http://github.com/odamite/gedit-cppcheck))
* Hudsons ([plugin](http://wiki.hudson-ci.org/display/HUDSON/Cppcheck+Plugin))
* Jenkins ([plugin](http://wiki.jenkins-ci.org/display/JENKINS/Cppcheck+Plugin))
* Visual Studios ([plugin](https://github.com/VioletGiraffe/cppcheck-vs-addin/releases/latest))

the above are not the only programs with cppcheck integration but only a small portion.


What cppcheck can and can't do
=============================
##Capabilites of cppcheck

* out of bounds error check
* class code checks
* code exception checking
* memory leak checking to a certain extent
* obselete function usage warning
* invalid usage of STL
* usage of uninitialized variables and unused functions

##Limits of cppcheck

Some limits of cppcheck include user ignorance and lack of knowledge. Ok, joking aside, the use of cppcheck is to
limit the amount of false positive errors given by other compilers and checkers. What this means is with general
usage, cppcheck will not check much but what it does check, it checks extremely well. Similar to a crafting NPC in
a game, cppcheck will tell you only what it can tell you forsure. Given the right ingredients, or in cppcheck's
case, configurations and flags, it will give you errors that are almost guaranteed to be errors.

cppcheck works in a way where it trues to avoid false positives so many of the bugs listed will be actual bugs.
this being said, there will be many things that cppcheck will not catch such as stylistic errors and syntax bugs.

tl;dr: cppcheck is good at what it does, but use a variety of tools to fully debug your programs.
