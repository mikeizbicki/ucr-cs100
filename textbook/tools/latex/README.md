#Tutorial on LaTeX

After being in touch with the most important tools that a computer scientist must know, we want to introduce one last tool, which is called LaTeX.
Before you know what LaTeX is necessary to know the TEX. TEX is a program created by
Donald Knuth in the 70s in order to increase the quality of printing texts and mathematical formulas. Nowadays it can be used for basically anything, even to document programs that you create from now on. 
Latex is a program that collects commands using TEX as processing base and it was created by Leslie Lamport in the 80s in order to facilitate the use of TEX through commands for different functions.

LaTeX is a processor based on a two logical style. 

Visual style:
This is known as WHAT-YOU-SEE-IS-WHAT-YOU-GET (WYSIWYG). 

Logical style this category processing is done in two stages.
- The text to be printed and formatting commands are written in a file
source with the use of an editor.
- Then this file is compiled and generates an output file that can be
displayed. Eg HTML.

We are going to learn the second option.

###Structure

The LaTeX language works the command base that start with \ which is a marker
(Tags, tag languages).
The commands are written in the forms `\ command` or `\ begin {command} ... \ end {command}`.
When it comes written in the second version, it is called environment.
The text of each document type starts with `\ begin {document}` and ends with `\ end {document}`. Everything that comes before that is considered the preamble and everything that comes after `\ end {document}` is ignored.
It is in the preamble that are placed all the information on the main characteristics are placed.It begins with `\documentclass{style}`.

In style place we put the name of one of the predefined styles, which are:
- article
- report
- book

Here are some options within the chosen style
- size: Letter Standard (12pt is more used)
- twoside: prints on both sides of the page;
- oneside: prints on one side of the page;
- twocolumn: produces text in two columns on the page;
- onecolumn: produces text arranged in a column;
- landscape: produces a page in the form of landscape;
- Sheet size: Can be a4, letterpaper, etc ...

Example 1:

```latex
\documentstyle[twocolumn,12pt,a4]{article}
\usepackage{pacote}
\begin{document}
.
.
.
\end{document}
```




__________
This is a tutorial on LaTeX that combines the main unix tools together that a GOOD computer scientist should know. 
The tools that will be covered here are:

* LaTeX: to create the documents
* [git](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/assignments/lab/lab1-git/using-git.md): to version control the documents
* [vim](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/cheatsheets/vim-cheatsheet.pdf): to edit the text
* [Makefile](https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/make): to put things together
* pdflatex: to output as a pdf file.

If you don't know any of these tools, this is your chance! YEY... The tools that have their own tutorials, you can just click on the links and access. The rest you can check here... So let's get started!

##LaTeX
As computer scientists or engineers, we are supposed to write papers and other kind of documents that require features not easily found in conventional word processors. With that being said, the first tool that we want to present is LaTeX -- a great tool that produces beautiful type and is written in a language that is fairly intuitive. 

###Installation 

The following commands are the only thing you need to install LaTeX on Debian or Ubuntu:

```
$ apt-get update
$ apt-get install texlive texlive-base
```

If you need more help installing, you can find it [here](http://www.tug.org/texlive/).


###First steps
Now that the package to compile TeX files is installed, let's get started. 

####Before coding

Throughout this tutorial we will be using the folder `article`. After creating the folder (i.e., `mkdir article`) and navigating by using the `cd` command to get in on it, initialize the git repository: 

`git init`

Time to get some TeX code finally done! Let's create and edit out first file through `vim`: 

`vim part1.tex`

Before start entering text into your file, don't forget to press `i` while on `vim` to enter _insert mode_. At this point, you should have completed your vim tutorial... If you don't, it can be found [here](https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/assignments/lab/lab0-vim)... But if you still "without time to finish it" you can start it at least knowing how to quit it as well (believe me, that can be a challenge at the very beginning and you will really want to know how to do it, haha). To quite, press `:q`. To save and quit `vim`, press `:wq`. If while you being programming you need some extra help, press `:help`.

####My First LaTeX

The following text creates a basic file: 

```latex
\documentclass[12pt]{article}
\usepackage{color}
\begin{document}
Mike Izbicki is a great professor. Actually, he is the best professor ever... 
All cs100 students \textcolor{red}{LOVE} him. 
Mike Izbicki is a great professor. Actually, he is the best professor ever... 
All cs100 students \textcolor{blue}{LOVE} him. 
\end{document}
```

This small example shows us that the first information LaTeX needs to know when processing a file is
the type of document. This is specified with the `\documentclass` command. Further explanation on different classes 
can be found [here](http://en.wikibooks.org/wiki/LaTeX/Document_Structure#Document_classes).

After saving and closing vim (i.e., `:wq`), it's time to compile our first LaTeX file and create the `.pdf`. 
One simple command should do all this work for us:

`pdflatex part1.tex`

If everything worked fine, now you should be able to open the pdf file `part1.pdf` that will look like this:

![example1](https://cloud.githubusercontent.com/assets/9013439/7720575/b7d1c4bc-fe83-11e4-94c7-362913a08292.jpg)

And you repository will look like this: 

![dir1](https://cloud.githubusercontent.com/assets/9004719/7717933/586da8a8-fe5e-11e4-9a84-c396d3a61739.png)

If we succeed at the previous steps, it's time to our first commit. But first, we need to add the files to the staging area of git. 
Remember! We should commit ONLY source code files. We don't want our git repository to be full of executable and log files. In other words, out `part1.tex` file should be the only one that is added to the git repository. All the rest (`part1.log`, `part1.aux`, `part.pdf`) should *not* be added. 

`git add part1.tex`

Now we are ready to commit:

`git commit -m "My first TeX"`

In small projects you may not have a lot of commits, but in huge projects it's gonna happen all the time. So now, we are going to present a package for drawing Git history graphs using LaTeX, called gitdags. It can be really helpful to draw a really nice looking git repository for this [lab1](https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/assignments/lab/lab1-git).

###A brief introduction to gitdags

`gitdags` is a LaTeX package that allows you to effortlessly produce pretty Git history graphs. It is really convenient for demonstrating the effects of Git commands such as `checkout`, `reset`, `merge`, `rebase`, etc. on a repository.

![alt tag](http://i.stack.imgur.com/Tg7Kn.png)

### What `gitdags` is *not*

Automatic generation of history graphs of repositories is *not* the purpose of `gitdags`... 

### Dependencies

To use `gitdags`, you will need

* a LaTeX distribution,
* the `tikz` package (v3.0 or later),
* the [`xcolor-solarized`](https://github.com/Jubobs/xcolor-solarized) package.


### An example

The code below, compiled with `pdflatex`, will produce the graph shown above. HERE IS GONNA BE OUR PERSONAL EXAMPLE, TEACHING HOW STUDENTS REALLY USE IT (CREATING BOXES, POINTING IT TO ANOTHERS, ETC)

```latex
\documentclass{article}

\usepackage{subcaption}
\usepackage{gitdags}

\begin{document}

\begin{figure}
  \begin{subfigure}[b]{\textwidth}
    \centering
    \begin{tikzpicture}
      % Commit DAG
      \gitDAG[grow right sep = 2em]{
        A -- B -- { 
          C,
          D -- E,
        }
      };
      % Tag reference
      \gittag
        [v0p1]       % node name
        {v0.1}       % node text
        {above=of A} % node placement
        {A}          % target
      % Remote branch
      \gitremotebranch
        [origmaster]    % node name
        {origin/master} % node text
        {above=of C}    % node placement
        {C}             % target
      % Branch
      \gitbranch
        {master}     % node name and text 
        {above=of E} % node placement
        {E}          % target
      % HEAD reference
      \gitHEAD
        {above=of master} % node placement
        {master}          % target
    \end{tikzpicture}
    \subcaption{Before\ldots}
  \end{subfigure}

  \begin{subfigure}[b]{\textwidth}
    \centering
    \begin{tikzpicture}
      \gitDAG[grow right sep = 2em]{
        A -- B -- { 
          C -- D' -- E',
          {[nodes=unreachable] D -- E },
        }
      };
      % Tag reference
      \gittag
        [v0p1]       % node name
        {v0.1}       % node text
        {above=of A} % node placement
        {A}          % target
      % Remote branch
      \gitremotebranch
        [origmaster]    % node name
        {origin/master} % node text
        {above=of C}    % node placement
        {C}             % target
      % Branch
      \gitbranch
        {master}      % node name and text 
        {above=of E'} % node placement
        {E'}          % target
      % HEAD reference
      \gitHEAD
        {above=of master} % node placement
        {master}          % target
    \end{tikzpicture}
    \subcaption{\ldots{} and after \texttt{git rebase origin/master}}
  \end{subfigure}
  \caption{Demonstrating a typical \texttt{rebase}}
\end{figure}

\end{document}
```

Finally, now that you you learned a lot of cool tools, it is time to mention that in your own Resume and being at the front line in the Computer Science market.
The following tutorial will teach some codes that you can use to creat a new beatiful Resume using LaTeX.
