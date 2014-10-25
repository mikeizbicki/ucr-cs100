# grades

We will not be using ilearn in this course.
Instead, we will use git.
All of your grade information will be stored in the repo you forked during lab1.
This file contains detailed information about how your grades will be stored in that repo.

**IMPORTANT:**
If you did not give all of the instructors write access to your repository (make them collaborators on github), then you won't be able to get your grades updated, and you will get zeros on the assignments!

**IMPORTANT:**
By default, github sets your repo to `public` and gives everyone read access.
That means everyone can view your grade.
If you do not want others to view your grade, you can set your repo to be `private` instead.
This won't affect our ability to grade your assignments.

## grade format

Every assignment has a corresponding directory.
In that directory is a file called `grade`.
This file (in the `grades` branch) contains your score on that assignment.

An example `grade` file might look like:

```
90 / 100

-5 points for making mistake X

-20 points for not doing task Y

+15 points extra credit for doing Z
```

The first line specifies how many points you earned on the assignment, and how many points the assignment is out of.
The rest of the file gives a detailed breakdown of why your assignment earned that final grade.

If the assignment has not yet been graded, then the contents of the file will contain just a slash and the number of points the assignment is worth:

```
/ 100
```

## checking your overall grade

You can use the `scripts/calcgrade.sh` script to calculate your whole grade for the course.
This script automatically downloads the latest version of your repo, inspects the grade you received on each assignment, and calculates your current and final grades for the course.

The `calcgrade.sh` script expects a single argument that corresponds to the UCR netid/CS account of the grade you want to check.
For example, if you want to find the grade of the `examplestudent` account, you would run:

```
$ ./scripts/calcgrade.sh examplestudent
```

and the output looks something like:

```
finding grade for github account examplestudent
repository exists... fetching ORIGIN

===========================================
    grade        |  assignment
===========================================
    --- /   0    |  hw0-vim
     85 / 100    |  hw1-rshell
    --- / 100    |  hw2-ls
     33 / 100    |  hw3-piping
     54 / 100    |  hw4-signals
     10 /  10    |  lab0-vim
    --- /  10    |  lab1-git
      8 /  10    |  lab2-fork
    --- /  10    |  lab3-debugging1
    --- /  10    |  lab4-cp
    --- /  10    |  lab5-debugging2
    --- /  10    |  lab6-signal
    --- /  10    |  lab7-cstring
    --- /  10    |  lab8-spam
    --- /  10    |  lab9-rm
    --- /  50    |  linux
    --- /   0    |  reading
===========================================

running total =  190 /  320 = 58.64
overall total =  190 /  550 = 34.29
```

Notice that ungraded assignments are marked with a grade of `---` and not included in the running total.

## cheating

All of your grade information will be stored in your own git repository.
You have write access to this information, so you may be tempted to change it.
Don't!

We have access to the full changelog of all the files in your repo.
For example, if I run the command:

```
$ git log hw/hw1-rshell/grade
```

Then I will get output similar to:

```
commit b72f2c09206bb05c93612fea4cfc6c53f718988f
Author: Mike Izbicki <mike@izbicki.me>
Date:   Sat Jul 20 07:35:46 2014 -0700

    graded hw1

commit b72f2c09206bb05c93612fea4cfc6c53f718988f
Author: Mike Izbicki <mike@izbicki.me>
Date:   Sat Jul 12 11:52:42 2014 -0700

    initial commit
```

This tells us who has modified the file and what they've done.
If you modify your grades, we will catch you.
As a reminder, I take cheating very seriously.
I will forward your case to the academic conduct committee and recommend you be expelled from UCR.

If you are an advanced git user, you may be aware that it's possible to commit changes under other people's names using the `--author` flag.
All of our grading scripts, however, sign the commits we make using the RSA public key crypto system.
Since you do not have access to the instructors' private keys, you will not be able to properly sign the grading commits.

**IMPORTANT:**
I encourage you to try to "hack" this grading system.
And if you find a way to change your grades in any way, I will give you a considerable amount of extra credit in this course.
But please do it responsibly and let the instructors know what you're doing before you try.
