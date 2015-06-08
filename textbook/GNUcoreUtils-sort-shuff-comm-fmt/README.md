## GNU CoreUtils
### Outputting and manipulating text files

GNU Coreutils provides commands that aids users in formatting and manipulating texts and files.
For this tutorial, we will be dealing with:
* sort
* shuf
* comm
* fmt - Since I used this on my sort example, I'll cover a bit at the end of the tutorial.

The listed commands can be used to manipulate files according to the users desire. 
The name of the commands is straightforward and is obvious of what it does. 
For this tutorial, I downloaded a list of students from the current and previous cs100 class. 
This list is currently semi sorted.
It's from spring2015, winter2015, and fall2015. 
I took a copy of the spring2015 students then appended the winter2015 list then the fall2015.
Because of that, the list will look semi-sorted in a sense. 
We will use this list to practice and learn more about the commands that we'll tackle.

#### sort
As the title says, this command takes in a file and sorts it. 
The format for this command is `sort <option> <file>`
In the case where the user doesn't put in a file, standard input is redirected as its input.
The sort command has a lot of options that it can take in, but for this practice we'll use the following:

NOTE: I recommend that you read the man page for sort to see all the possible options that might just fit your needs.


Here's the file that we're gonna work with. As you see it's semi-sorted. Now we'll run different samples with it.

```
jpatu001@cs100: $ fmt -w 70 student
aadet001 aesgu001 amah001 aphil013 aso001 athai005 avere001 bherm001
cbarb005 cdixi001 dcals001 dchou002 dding002 dlei004 donei003
dtran049 ecarr007 echan031 examplestudent fvera002 gnori002 hkwan003
htang014 hzhu007 ichor001 imend009 jbarb011 jdixo001 jkinc002 jle034
jmeji011 jpatu001 jruel006 jtran071 jwong066 kchan049 kkimb003
kkita004 kluu006 kmins002 knels012 korte004 ktang012 kzhen002
lboyd002 lseeb002 lzhu012 masfo001 mchen046 nchun003 phung001
rheng001 skama004 srufe001 sthak004 ttruo018 unara001 vchan019
vhall001 ycao006 ykamo001 yyao007 zxie003 zzhou007 aben001 amart088
athio001 ccali003 cfan002 cibar007 cyang032 dhand002 dshe001 eneva002
hdorn001 ikim025 jcand003 jduga002 jfu006 jkinc002 jlu019 jng017
jsun031 jwang096 jweyr001 kkamg001 kkimb003 ljomo001 makba002 mchu011
mevan003 mmore019 monti004 muy003 nfarh002 rfeng001 rpasi001 ryama008
santo003 sbala003 scohe001 skuo004 slee208 tzick002 vchio001 vgarc018
vhall001 wfink001 wlee030 yli066 yliu075 yliu127 aaven004 abarb014
achao008 afan004 ahsu013 amacp001 amyll001 aorti017 asand017 atan009
atost001 atran046 bbenn003 bchen022 bleon001 ccoll010 cmanj001
dgoer001 dngo010 dpham008 drami025 emull005 fvera002 gliu016 gruiz007
hchu007 hfanc001 hgarc014 hlao002 hray001 htsai010 ifuka001 ihund001
jbarb011 jfan013 jholl013 jmaw001 jmoon018 jreye028 jstod001 karai001
kchan039 khigu001 khuan013 kkamg001 kle016 llope039 lpeng003 lxu003
mxu008 nkesa001 nlapr001 nsark002 ogonz007 palva002 pstar001 rdinh002
rheng001 rluk001 rtran012 sjin010 teloy001 tglen002 tliu020 vdoan002
yli082 zeman001
```


* `-c` checks if the file is sorted. 
In the case where it is unsorted, it prints the line of the first out-of-order item and exits with a status of 1.
```
jpatu001@cs100: $ sort -c student
sort: student:65: disorder: aben001
```

If you look at the list above you'll see that aben001 is the first username that is out of the order.


* `-C` is like `-c` minus the possibly annoying printing of diagnostics, instead it just exits with a return status of 1. 
```
jpatu001@cs100: $ sort -C student
jpatu001@cs100: $ 
```

Now running the same file with `-C`, no diagnosis was printed. 
This is not helpful in the case where we want to see if the file is sorted or not unless we catch the 1 that the command returns.


* `-d` sorts the file in a phone-directory order.
This means that it ignores any other characters besides letters, numbers and spaces when sorting.
In our test file, this is pretty much the same as running sort student.
```
jpatu001@cs100: $ sort -d student | fmt -w 60
aadet001 aaven004 abarb014 aben001 achao008 aesgu001
afan004 ahsu013 amacp001 amah001 amart088 amyll001 aorti017
aphil013 asand017 aso001 atan009 athai005 athio001 atost001
atran046 avere001 bbenn003 bchen022 bherm001 bleon001
cbarb005 ccali003 ccoll010 cdixi001 cfan002 cibar007
cmanj001 cyang032 dcals001 dchou002 dding002 dgoer001
dhand002 dlei004 dngo010 donei003 dpham008 drami025 dshe001
dtran049 ecarr007 echan031 emull005 eneva002 examplestudent
fvera002 fvera002 gliu016 gnori002 gruiz007 hchu007
hdorn001 hfanc001 hgarc014 hkwan003 hlao002 hray001
htang014 htsai010 hzhu007 ichor001 ifuka001 ihund001
ikim025 imend009 jbarb011 jbarb011 jcand003 jdixo001
jduga002 jfan013 jfu006 jholl013 jkinc002 jkinc002 jle034
jlu019 jmaw001 jmeji011 jmoon018 jng017 jpatu001 jreye028
jruel006 jstod001 jsun031 jtran071 jwang096 jweyr001
jwong066 karai001 kchan039 kchan049 khigu001 khuan013
kkamg001 kkamg001 kkimb003 kkimb003 kkita004 kle016 kluu006
kmins002 knels012 korte004 ktang012 kzhen002 lboyd002
ljomo001 llope039 lpeng003 lseeb002 lxu003 lzhu012 makba002
masfo001 mchen046 mchu011 mevan003 mmore019 monti004
muy003 mxu008 nchun003 nfarh002 nkesa001 nlapr001 nsark002
ogonz007 palva002 phung001 pstar001 rdinh002 rfeng001
rheng001 rheng001 rluk001 rpasi001 rtran012 ryama008
santo003 sbala003 scohe001 sjin010 skama004 skuo004 slee208
srufe001 sthak004 teloy001 tglen002 tliu020 ttruo018
tzick002 unara001 vchan019 vchio001 vdoan002 vgarc018
vhall001 vhall001 wfink001 wlee030 ycao006 ykamo001 yli066
yli082 yliu075 yliu127 yyao007 zeman001 zxie003 zzhou007
```


* `-r` sorts the file in reverse order.
```
jpatu001@cs100: $ sort -r student | fmt -w 60
zzhou007 zxie003 zeman001 yyao007 yliu127 yliu075 yli082
yli066 ykamo001 ycao006 wlee030 wfink001 vhall001 vhall001
vgarc018 vdoan002 vchio001 vchan019 unara001 tzick002
ttruo018 tliu020 tglen002 teloy001 sthak004 srufe001
slee208 skuo004 skama004 sjin010 scohe001 sbala003 santo003
ryama008 rtran012 rpasi001 rluk001 rheng001 rheng001
rfeng001 rdinh002 pstar001 phung001 palva002 ogonz007
nsark002 nlapr001 nkesa001 nfarh002 nchun003 mxu008 muy003
monti004 mmore019 mevan003 mchu011 mchen046 masfo001
makba002 lzhu012 lxu003 lseeb002 lpeng003 llope039 ljomo001
lboyd002 kzhen002 ktang012 korte004 knels012 kmins002
kluu006 kle016 kkita004 kkimb003 kkimb003 kkamg001 kkamg001
khuan013 khigu001 kchan049 kchan039 karai001 jwong066
jweyr001 jwang096 jtran071 jsun031 jstod001 jruel006
jreye028 jpatu001 jng017 jmoon018 jmeji011 jmaw001 jlu019
jle034 jkinc002 jkinc002 jholl013 jfu006 jfan013 jduga002
jdixo001 jcand003 jbarb011 jbarb011 imend009 ikim025
ihund001 ifuka001 ichor001 hzhu007 htsai010 htang014
hray001 hlao002 hkwan003 hgarc014 hfanc001 hdorn001 hchu007
gruiz007 gnori002 gliu016 fvera002 fvera002 examplestudent
eneva002 emull005 echan031 ecarr007 dtran049 dshe001
drami025 dpham008 donei003 dngo010 dlei004 dhand002
dgoer001 dding002 dchou002 dcals001 cyang032 cmanj001
cibar007 cfan002 cdixi001 ccoll010 ccali003 cbarb005
bleon001 bherm001 bchen022 bbenn003 avere001 atran046
atost001 athio001 athai005 atan009 aso001 asand017 aphil013
aorti017 amyll001 amart088 amah001 amacp001 ahsu013 afan004
aesgu001 achao008 aben001 abarb014 aaven004 aadet001
```

* `-R` randomizes the list instead of sorting. 
```
jpatu001@cs100: $ sort -R student | fmt -w 60
asand017 jsun031 khuan013 kchan049 korte004 vgarc018
kkamg001 kkamg001 teloy001 kkita004 jle034 jbarb011
jbarb011 amah001 hfanc001 ahsu013 atan009 jreye028 kchan039
dchou002 lzhu012 jng017 jweyr001 kkimb003 kkimb003 dpham008
scohe001 cdixi001 dhand002 ttruo018 jfan013 jmaw001
dding002 mchen046 ifuka001 avere001 wlee030 aphil013
cibar007 lseeb002 aaven004 jmoon018 vdoan002 jdixo001
mchu011 dlei004 jfu006 hlao002 jholl013 nfarh002 atran046
ktang012 dngo010 cmanj001 hdorn001 nsark002 rluk001 kle016
amacp001 vchan019 khigu001 aadet001 hkwan003 hchu007
pstar001 jwang096 hzhu007 ogonz007 jcand003 llope039
hgarc014 cfan002 ikim025 dcals001 htang014 atost001 yliu075
afan004 zxie003 dtran049 sbala003 mevan003 ryama008
ihund001 masfo001 aben001 aesgu001 ccali003 achao008
gliu016 srufe001 jlu019 kluu006 muy003 phung001 santo003
dgoer001 kzhen002 bbenn003 jmeji011 htsai010 skama004
jwong066 nchun003 cbarb005 rheng001 rheng001 rfeng001
yli066 nkesa001 cyang032 yli082 drami025 mxu008 dshe001
gruiz007 wfink001 abarb014 jkinc002 jkinc002 fvera002
fvera002 jruel006 echan031 lxu003 zzhou007 palva002
ykamo001 imend009 rpasi001 ecarr007 bleon001 tzick002
knels012 examplestudent zeman001 jduga002 tglen002 ljomo001
jstod001 aso001 rdinh002 vhall001 vhall001 lpeng003 tliu020
eneva002 athai005 sthak004 mmore019 amyll001 karai001
ccoll010 bchen022 slee208 hray001 yliu127 jpatu001 emull005
athio001 makba002 jtran071 ichor001 unara001 ycao006
gnori002 sjin010 rtran012 monti004 nlapr001 lboyd002
yyao007 aorti017 vchio001 kmins002 skuo004 donei003
bherm001 amart088
```

So how can we use `sort`? Let's say you want the student list to be sorted. 
We can do:
```
jpatu001@cs100: $ sort student > sortedStudents
jpatu001@cs100: $ fmt -w 60 sortedStudent
aadet001 aaven004 abarb014 aben001 achao008 aesgu001
afan004 ahsu013 amacp001 amah001 amart088 amyll001 aorti017
aphil013 asand017 aso001 atan009 athai005 athio001 atost001
atran046 avere001 bbenn003 bchen022 bherm001 bleon001
cbarb005 ccali003 ccoll010 cdixi001 cfan002 cibar007
cmanj001 cyang032 dcals001 dchou002 dding002 dgoer001
dhand002 dlei004 dngo010 donei003 dpham008 drami025 dshe001
dtran049 ecarr007 echan031 emull005 eneva002 examplestudent
fvera002 fvera002 gliu016 gnori002 gruiz007 hchu007
hdorn001 hfanc001 hgarc014 hkwan003 hlao002 hray001
htang014 htsai010 hzhu007 ichor001 ifuka001 ihund001
ikim025 imend009 jbarb011 jbarb011 jcand003 jdixo001
jduga002 jfan013 jfu006 jholl013 jkinc002 jkinc002 jle034
jlu019 jmaw001 jmeji011 jmoon018 jng017 jpatu001 jreye028
jruel006 jstod001 jsun031 jtran071 jwang096 jweyr001
jwong066 karai001 kchan039 kchan049 khigu001 khuan013
kkamg001 kkamg001 kkimb003 kkimb003 kkita004 kle016 kluu006
kmins002 knels012 korte004 ktang012 kzhen002 lboyd002
ljomo001 llope039 lpeng003 lseeb002 lxu003 lzhu012 makba002
masfo001 mchen046 mchu011 mevan003 mmore019 monti004
muy003 mxu008 nchun003 nfarh002 nkesa001 nlapr001 nsark002
ogonz007 palva002 phung001 pstar001 rdinh002 rfeng001
rheng001 rheng001 rluk001 rpasi001 rtran012 ryama008
santo003 sbala003 scohe001 sjin010 skama004 skuo004 slee208
srufe001 sthak004 teloy001 tglen002 tliu020 ttruo018
tzick002 unara001 vchan019 vchio001 vdoan002 vgarc018
vhall001 vhall001 wfink001 wlee030 ycao006 ykamo001 yli066
yli082 yliu075 yliu127 yyao007 zeman001 zxie003 zzhou007
```

There you go. The list is now sorted under the file sortedStudents.


#### shuf
`shuf` is a command that takes in an input file and randomizes its output. 
The format of the command is as follows:
* shuf <option> <file>
* shuf -e <option> <arg>
* shuf -i lo-hi <option>

Here are some examples of using it:

* `-e` takes in the command line argument as its input file.
```
jpatu001@cs100: $ shuf -e 1 2 3 4 5 6 7 8 9 j q k a
8
9
k
1
q
4
3
5
a
j
7 
2
6
``` 

* `-i` takes in an input range(lower-higher) and outputs a random permutation of the range.
Let's say we want to randomize a dice roll. We can do:
```
jpatu001@cs100: $ shuf -i 1-6
4
3
1
2
5
6
```

* `-n` randomizes n number of lines at maximum. 
Let's say you have a list of 100 names, you can use this option to randomly select 10. 
For our example, we use the students list.
```
jpatu001@cs100: $ shuf -n 5 sortedStudent 
ikim025
kkamg001
vgarc018
dding002
zzhou007
```
Here we take in the sortedStudent list that has more than 50 names, and randomly selected 5.

* `-o` randomizes the list but instead of outputting to the terminal, it outputs it to a file.
Here the shuffled file was saved to randomList and the option -n 10 limited it to 10 lines.
```
jpatu001@cs100: $ shuf -n 10 -o randomList sortedStudent 
jpatu001@cs100: $ cat randomList
srufe001
wlee030
cibar007
korte004
htsai010
kchan039
dngo010
jsun031
scohe001
hgarc014
```


#### comm
`comm` is the command that can be used when comparing two files.
It outputs to the terminal all the lines that are common between two input files passed to it.
It is also expected that a file is sorted before passing into `comm`.
So to use `comm`, it is a good practice to know how to use the `sort` command that we tackled earlier.
When no option is passed, `comm` produces three column output. 
Column 1: Is for lines unique to file1

Column 2: Is for lines unique to file2

Column 3: Is for lines that exist on both files. 

For this example, we have two files named sortedStudents that we genereted earlier,
and another file called studentS15 which hold the student list for spring 2015 cs100.
```
jpatu001@cs100: $ comm studentS15 sortedStudent 

				aadet001
	aaven004
	abarb014
	aben001
	achao008
				aesgu001
	afan004
	ahsu013
	amacp001
				amah001
	amart088
	amyll001
	aorti017
				aphil013
	asand017
				aso001
	atan009
				athai005
	athio001
	atost001
	atran046
				avere001
	bbenn003
	bchen022
				bherm001
	bleon001
				cbarb005
	ccali003
	ccoll010
				cdixi001
	cfan002
	cibar007
	cmanj001
	cyang032
				dcals001
				dchou002
				dding002
	dgoer001
	dhand002
				dlei004
	dngo010
				donei003
	dpham008
	drami025
	dshe001
				dtran049
				ecarr007
				echan031
	emull005
	eneva002
				examplestudent
				fvera002
	fvera002
	gliu016
				gnori002
	gruiz007
	hchu007
	hdorn001
	hfanc001
	hgarc014
				hkwan003
	hlao002
	hray001
				htang014
	htsai010
				hzhu007
				ichor001
	ifuka001
	ihund001
	ikim025
				imend009
				jbarb011
	jbarb011
	jcand003
				jdixo001
	jduga002
	jfan013
	jfu006
	jholl013
				jkinc002
	jkinc002
				jle034
	jlu019
	jmaw001
				jmeji011
	jmoon018
	jng017
				jpatu001
	jreye028
				jruel006
	jstod001
	jsun031
				jtran071
	jwang096
	jweyr001
				jwong066
	karai001
	kchan039
				kchan049
	khigu001
	khuan013
	kkamg001
	kkamg001
				kkimb003
	kkimb003
				kkita004
	kle016
				kluu006
				kmins002
				knels012
				korte004
				ktang012
				kzhen002
				lboyd002
	ljomo001
	llope039
	lpeng003
				lseeb002
	lxu003
				lzhu012
	makba002
				masfo001
				mchen046
	mchu011
	mevan003
	mmore019
	monti004
	muy003
	mxu008
				nchun003
	nfarh002
	nkesa001
	nlapr001
	nsark002
	ogonz007
	palva002
				phung001
	pstar001
	rdinh002
	rfeng001
				rheng001
	rheng001
	rluk001
	rpasi001
	rtran012
	ryama008
	santo003
	sbala003
	scohe001
	sjin010
					skama004
	skuo004
	slee208
				srufe001
				sthak004
	teloy001
	tglen002
	tliu020
				ttruo018
	tzick002
				unara001
				vchan019
	vchio001
	vdoan002
	vgarc018
				vhall001
	vhall001
	wfink001
	wlee030
				ycao006
				ykamo001
	yli066
	yli082
	yliu075
	yliu127
				yyao007
	zeman001
				zxie003
				zzhou007

```
Since file1 is a subset of our file2, the first column is empty. 
The third column is composed of students in current quarter.
And column two is the list of the rest of the students.

It is also possible to block out certain column by including `-<number of column>` to the option.
This removes the column when printing output. Also note that `--check-order` option can be used to fail the command when one file is unsorted.
Or you can use `--nocheck-order` to ignore such sortedness of a file. 
And one last usable option is `--output-delimiter=<string>`.
Instead of tab spaces separating the columns, it will be replaced by the string you declared on the option.


#### fmt
As you see from the `sort` part I used a command called `fmt`, 
though the way I used it may not be the conventional/ proper way of using it.
For that reason, I'll try to give examples of using it. 
For this example, I'll use a portion of the course's README.md from ucr-cs100 repo.
`fmt` can be as follow:
`fmt <option> <file>.
The job of the command is to output a file and to fill its maximum 75 characters per line.
By running cat on the slightly modified portion of this class' README.md, we get:
```
## cs100 - open source software construction

	This is a course on [how to be a hacker](http://www.catb.org/esr/faqs/hacker-howto.html).
Being a hacker [means a lot of things](http://www.catb.org/jargon/html/H/hacker.html).
	It means:

1. wanting to know *how* and *why* computers work

2. being efficient / never repeating yourself

3. using and contributing to open source software

4. understanding the edge cases of your software

5. using tools in creative and unexpected ways

6. (occasionally) we combine all these together and break stuff

Hacking is a mindset.
I can't force it on you---it's up to you to embrace it.
For example, we'll be discussing many new tools in this course:
a version control system called `git`,
an editor called `vim`,
debugging tools called `gdb`, `valgrind`, and `cppcheck`,
and we'll be going into quite a bit more depth on how to use the `bash` shell and the `Linux` operating system.
All of these tools are very weird.
Using them will make you uncomfortable.
At first.
But these tools are powerful.
Mastering these tools will make you a *much* more efficient programmer.
Once you've mastered them, you'll never go back.

There are two main projects you will work on in this course:

1. Your first four homework assignments walk you through the process of building your own unix shell.
This is the biggest project you've undertaken so far.
You'll be developing it as an open source project,
and you will collaborate with each other at various points.

2. Your last homework assignment is to contribute to the open source community by improving the documentation on a project of your choice.
Many of the required readings for this course were written by former cs100 students.
If you do a good job on this project, future cs 100 students will be learning from you for years to come!

By the end of the course, you should be comfortable running your own open source projects and contributing to other people's projects.


### grades

	We will not be using ilearn in this course.
Instead, we will be using a course management system called `gitlearn`.
This software was developed in part by previous cs100 students,
and you will be able to earn considerable extra credit by contributing to it.
We will be using this system as a case study in bash programming and the unix philosophy.
For details, see the [gitlearn repo](https://github.com/mikeizbicki/gitlearn).

### cheating policy

	Every assignment specifies different collaboration policies.
Some assignments will be individual, and some will be in a group.
Follow the specified policy exactly!

	I take cheating seriously.
When I catch students cheating, I give them an F in the class.
Then I forward your case to the academic integrity board and recommend that you be expelled from UCR.

	All of your code will be run through an automated cheating detector.
It is very good.
It understands C++ better than you do and can find instances of cheating much more sophisticated than just copy and pasting.
```

We see that the format follows the file formatting of the text.
By using the fmt command, the text is outputted in a way that it maximizes the 75 character long
terminal, and it also tries not to cut sentences near sentence-enders like . , or ?.
```
## cs100 - open source software construction

	This is a course on [how to be a
	hacker](http://www.catb.org/esr/faqs/hacker-howto.html).
Being a hacker [means a lot of
things](http://www.catb.org/jargon/html/H/hacker.html).
	It means:

1. wanting to know *how* and *why* computers work

2. being efficient / never repeating yourself

3. using and contributing to open source software

4. understanding the edge cases of your software

5. using tools in creative and unexpected ways

6. (occasionally) we combine all these together and break stuff

Hacking is a mindset.  I can't force it on you---it's up to you to
embrace it.  For example, we'll be discussing many new tools in this
course: a version control system called `git`, an editor called `vim`,
debugging tools called `gdb`, `valgrind`, and `cppcheck`, and we'll be
going into quite a bit more depth on how to use the `bash` shell and the
`Linux` operating system.  All of these tools are very weird.  Using them
will make you uncomfortable.  At first.  But these tools are powerful.
Mastering these tools will make you a *much* more efficient programmer.
Once you've mastered them, you'll never go back.

There are two main projects you will work on in this course:

1. Your first four homework assignments walk you through the process
of building your own unix shell.  This is the biggest project you've
undertaken so far.  You'll be developing it as an open source project,
and you will collaborate with each other at various points.

2. Your last homework assignment is to contribute to the open source
community by improving the documentation on a project of your choice.
Many of the required readings for this course were written by former
cs100 students.  If you do a good job on this project, future cs 100
students will be learning from you for years to come!

By the end of the course, you should be comfortable running your own
open source projects and contributing to other people's projects.


### grades

	We will not be using ilearn in this course.
Instead, we will be using a course management system called `gitlearn`.
This software was developed in part by previous cs100 students, and
you will be able to earn considerable extra credit by contributing
to it.	We will be using this system as a case study in bash
programming and the unix philosophy.  For details, see the [gitlearn
repo](https://github.com/mikeizbicki/gitlearn).

### cheating policy

	Every assignment specifies different collaboration policies.
Some assignments will be individual, and some will be in a group.
Follow the specified policy exactly!

	I take cheating seriously.
When I catch students cheating, I give them an F in the class.	Then I
forward your case to the academic integrity board and recommend that
you be expelled from UCR.

	All of your code will be run through an automated cheating
	detector.
It is very good.  It understands C++ better than you do and can find
instances of cheating much more sophisticated than just copy and pasting.
```
With this example compared to the first one, it is clear that the formatting is much more like a paragraph than a markdown file. This is how it is most likely going to look like in github.

With that comparison said, `fmt` is much more flexible in outputting files into your terminal comapred to cat. 
Reading txt files will be much easier with fmt with the proper options.
Such options available are:
* `-c` or crown margin which preserves the indetation of the first 2 lines, then aligns the rest towards the left.
* `-t` or tagged paragraph. Here the first line is considered a single-line paragraph if the 
indentation of the first and second line are the same.
Otherwise, it is the same formatting as -c.
* `-s` or split-only prevents the concatamnation of short sentences to form longer outputs.
Each sentence ending in punctuation mark or more than 75 characters is printed with a newline.
This looks like how a markdown should be like.
One sentence per line.
* `-w` or width tries to achieve the user given width when formatting the output.
That is when given `-w 80`, instead of 75, its width to fill will be 80 characters per line
* `-p` with this option, only lines that start with the given prefix is subjected to formatting.

To save space, I will only do one example using the -w and -c to show a comparison between
the formatted output and the one provided earlier that used cat:
```
jpatu001@cs100:~/Documents/CS100/ucr-cs100/textbook/text_manip (2015spring) $ fmt -cw 50 fmtFile 
## cs100 - open source software construction

	This is a course on [how to be a
hacker](http://www.catb.org/esr/faqs/hacker-howto.html).
Being a hacker [means a lot of
things](http://www.catb.org/jargon/html/H/hacker.html).
	It means:

1. wanting to know *how* and *why* computers work

2. being efficient / never repeating yourself

3. using and contributing to open source software

4. understanding the edge cases of your software

5. using tools in creative and unexpected ways

6. (occasionally) we combine all these together
and break stuff

Hacking is a mindset.  I can't force it on
you---it's up to you to embrace it.  For example,
we'll be discussing many new tools in this
course: a version control system called `git`,
an editor called `vim`, debugging tools called
`gdb`, `valgrind`, and `cppcheck`, and we'll
be going into quite a bit more depth on how to
use the `bash` shell and the `Linux` operating
system.  All of these tools are very weird.
Using them will make you uncomfortable.
At first.  But these tools are powerful.
Mastering these tools will make you a *much*
more efficient programmer.  Once you've mastered
them, you'll never go back.

There are two main projects you will work on in
this course:

1. Your first four homework assignments walk
you through the process of building your own
unix shell.  This is the biggest project you've
undertaken so far.  You'll be developing it as
an open source project, and you will collaborate
with each other at various points.

2. Your last homework assignment is to contribute
to the open source community by improving the
documentation on a project of your choice.
Many of the required readings for this course
were written by former cs100 students.	If you
do a good job on this project, future cs 100
students will be learning from you for years
to come!

By the end of the course, you should be
comfortable running your own open source projects
and contributing to other people's projects.


### grades

	We will not be using ilearn in
this course.  Instead, we will be using a
course management system called `gitlearn`.
This software was developed in part by previous
cs100 students, and you will be able to earn
considerable extra credit by contributing
to it.	We will be using this system as a
case study in bash programming and the unix
philosophy.  For details, see the [gitlearn
repo](https://github.com/mikeizbicki/gitlearn).

### cheating policy

	Every assignment specifies different
collaboration policies.  Some assignments will
be individual, and some will be in a group.
Follow the specified policy exactly!

	I take cheating seriously.  When I
catch students cheating, I give them an F in
the class.  Then I forward your case to the
academic integrity board and recommend that you
be expelled from UCR.

	All of your code will be run through an
automated cheating detector.  It is very good.
It understands C++ better than you do and
can find instances of cheating much more
sophisticated than just copy and pasting.

```
Here you'll see that the width was shrinked to more or less 50 characters and the output 
formatting compared to the cat command is much better since it's not in a mardown format.
One last example for comparison:
```
jpatu001@cs100: $ cat randomList 
srufe001
wlee030
cibar007
korte004
htsai010
kchan039
dngo010
jsun031
scohe001
hgarc014

jpatu001@cs100: $ fmt -w 80 randomList 
srufe001 wlee030 cibar007 korte004 htsai010 kchan039 dngo010 jsun031 scohe001
hgarc014
```

