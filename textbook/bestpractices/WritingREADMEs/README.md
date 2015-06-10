<<<<<<< HEAD
README Quick Reference Guide
---
* This is by no means an all-inclusive list of everything you should have in your README.
* READMEs can be written in Markdown(```.md```) or as a text file (```.txt```).

Program Overview
---
* Give a brief description of what your project is and what it is intended to do.
* Include an example of what your project can do, something that will grab the attention of someone who just happened upon your repository.

How to use
---
* Provide the information required to effectively use your project.
* You can, but are not required to, include example code.

Prerequisites
---
* List any special or third party prerequisites needed to run your project (if your project requires a library that has to be installed on its own, it is a prerequisite).
* If no unordinary prerequisites are needed this section is not necessary.
  * E.g. For a C++ project the SDL library would be a prerequisite but the vector library would not because it is included with the standard g++ installation.

Installation guide
---
* List the steps needed to install your project.
* It is better to explicitly list the commands needed rather than describe the steps. 
  * E.g. ```make``` as opposed to "run make".

Bugs/Limitations/Issues
---
* Explicitly list all of the known bugs in your project.
* If there are any known limitations or issues, explicitly list those as well.
* The more effective you are at conveying the nature of the bug/limitation/issue the better. This means being clear and concise in your wording and providing as much relevant information as possible.
  * E.g. "The foo function causes a segmentation fault when the argument passed in is negative" as opposed to "foo fails when the parameter is negative"

Things **not** to do
---
* Do not include an authors and contributors section in your README, this information can be found elsewhere on GitHub.
* There is no need to list the files in your repository in your README.
* Avoid listing commands in words, instead explicitly list the commands using ``` ` ``` in sequential order.
* It is not necessary to include information about your licensing beyond where to find it in your README.
=======
# How to write a good README file

The README file is the most important file in every repo.
If your README is good, lots of people will use your code.
If your README is bad, no one will understand what your code does, so no one will use it.
Without a good README, your project may as well not exist.

In the first section of your README, you should outline the contents of the file.
For example in this file, we'll first discuss the file formats used for READMEs;
then the README's contents (with lots of examples!);
and we'll conclude with things *not* to do.

## Formatting your README file

There are two main formats for README files.
The simplest is plaintext.
This format is usually used by older projects (like the [Linux kernel](https://github.com/torvalds/linux/blob/master/README) or [git](https://duckduckgo.com/l/?kh=-1&uddg=https%3A%2F%2Fgithub.com%2Fgit%2Fgit)).
I recommend not using plaintext, and using markdown instead.
Markdown is a special formatting language that is easy to read.
Most newer projects use this format.
For details on markdown syntax, see the [`Markdown.md`](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/textbook/bestpractices/WritingREADMEs/Markdown.md) file.
If you use markdown, your README should be called `README.md`.

**IMPORTANT:**
README files should *never* be word documents, pdf files, or other complex formats.

## The contents of your README file

The first sentence of your README file needs to describe what your project does.
Most readers will stop after reading just this sentence, so make sure it's a good one!
Most students really struggle with writing this sentence because they don't spend enough time on it.
Spending an *hour* coming up with the perfect one sentence summary is time well spent.
I'm not joking.
You cannot spend too much time polishing this sentence.

You should also include an example at the top of your README.
If possible, include an animated gif.
This will capture your audience's attention fast.

The following repos have great introductions and examples:

* The [PacVim game](https://github.com/jmoon018/PacVim#pacvim) has one of the best intros I've ever seen.
There is very little text.
Everything gets explained by the awesome animated gif.
In less than 5 seconds, you instantly know what this program is about!

* This [regular expression simulator](https://github.com/Liniarc/regexProgram#practice-regular-expressions) also uses a nice animated gif.

* The [BrightTime! Android App](https://github.com/Team-Unguided/BrightTime#brighttime) is a nice example that of a program that doesn't rely on the command line.
Again, the animated gif shows *exactly* what the app does without you having to read a word.
This is nice!


### Installation

After your introduction comes the first section of your README, where you explain how to install your project.

List the actual commands your reader should run.
For example:
```
$ git clone https://github.com/examplestudent/awesome-project
$ cd awesome-project
$ make
```
For some reason, lots of students describe these steps in words.
But here's a general rule:
NEVER say something in words that you can say with code.

If your installation instructions are complicated, then it's nice to provide an installation script that automates the process.
For example, look at this [prebuilt vimrc repo](https://github.com/Anthony1234567/Vimrc1234567#vimrc1234567).
Installing the vimrc file requires installing lots of other projects.
Your users won't have the time or desire to do this, so you should do it for them.

#### Dependencies
If your program uses any special packages not provided in a standard Unix installation, you should list them here.
Don't forget to provide links!
If your project has no dependencies, then this section is not needed.
For example, if your C++ project uses the [SDL library](http://libsdl.org/) for graphics, that's a dependency because the user might need to install it.
But if you use the vector library, that is not a dependency because it is included with all compilers.

### Bugs/Limitations/Issues

Explicitly list all of the known bugs in your project.
People like it when you tell them your project has bugs!
Seriously.
All projects have bugs.
When I read about your project, I'll assume (correctly) that yours does to.
In fact, I'll assume they're awful bugs that destroy my computer (experience shows this is usually the case).
So set

Plus, lots of programmers are just browsing GitHub looking for bugs to fix.
Make it easy for them to find the bugs, and they'll fix them for you!

## Things **not** to do

Never include anything in your README that is better located in other places.
For example:

* Do not include an authors and contributors section in your README.
Git records this for you automatically.
If you do it manually, you'll just get out of date.
Older projects (that started before version control was widely used) would list contributors, but you don't need to.

* Do not list the files in your repository in your README.
I can just run `ls`/look on GitHub for that info.

* Avoid listing commands in words, instead explicitly list the commands using backticks (``` ` ```) in sequential order.

* Never follow these rules if it results in a worse README.
The [git game repo](https://github.com/hgarc014/git-game) breaks almost all the rules I've listed above, but it is super popular!
If you read what the project does, you'll find out why it doesn't have a traditional README file.

>>>>>>> eaf388b... redid writing README files
