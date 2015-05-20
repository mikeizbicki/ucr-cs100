##Cool linux tools that any CS student should know

This is a tutorial on LaTeX that combines the main unix tools together that a GOOD computer scientist shold know. 
The tools that will be covered here are:

* LaTeX: to create the documents
* git: to version control the documents
* vim: to edit the text
* Makefile: to put things together
* pdflatex: to output as a pdf file.

If you don't know some of these tools, this is your chance! YEY... 
So let's get started!

##LaTeX
As computer scientists or engineers, we are supposed to write papers and other kind of documents that require features not easily found in conventional word processors. With that being said, the first tool that we wan't to present is LaTeX -- a great tool that produces beautiful type and is written in a language that is fairly intuitive. 

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

Time to get some TeX code finally up! Let's create and edit out first file through `vim`: 

`vim part1.tex`

Before start entering text into your file, don't forget to press `i` while on `vim` to enter _insert mode_. At this point, you should have completed your vim tutorial... If you don't, it can be find [here]... But if you still "without time to finish it" you can start it at least knowing how to quit it as well (believe me, that can be a challenge at the very begnning and you will really want to know how to do it, haha). To quite, press `:q`. To save and quit `vim`, press `:wq`. If while you being programming you need some extra help, press `:help`.

####My First LaTeX

The following text creates a basic file: 

```
\documentclass[12pt]{article}
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

After saving and closing vim (i.e., `:wq <name of the file>`), it's time to compile our first LaTeX file and create the `.pdf`. 
One simple command should do all this work for us:

`pdflatex part1.tex`

If everything worked fine, now you should be able to open the pdf file `part1.pdf` that will look like this:

![example1](https://cloud.githubusercontent.com/assets/9004719/7717927/543e6fba-fe5e-11e4-8896-becfe2d40650.png)

And you repository will look like this: 

![dir1](https://cloud.githubusercontent.com/assets/9004719/7717933/586da8a8-fe5e-11e4-9a84-c396d3a61739.png)

If we succeed at the previous steps, it's time to our first commit. But first, we need to add the files to the staging area of git. 
Remember! We should commit ONLY source code files. We don't want our git repository to be full of executable and log files. In other words, out `part1.tex` file should be the only one that is added to the git repository. All the rest (`part1.log`, `part1.aux`, `part.pdf`) should *not* be added. 

`git add part1.tex`

Now we are ready to commit:

`git commit -m "My first TeX"`

In small projects you may not have a lot of commits, but in huge projects it's gonna happen all the time. So now, we are going to present a package for drawing Git history graphs using LaTeX, called gitdags. You are going to need it in this lab ![here]().

#A brief introduction to gitdags

`gitdags` is a LaTeX package that allows you to effortlessly produce pretty Git history graphs. It is really convenient for demonstrating the effects of Git commands such as `checkout`, `reset`, `merge`, `rebase`, etc. on a repository.

![alt tag](http://i.stack.imgur.com/Tg7Kn.png)

## What `gitdags` is *not*

Automatic generation of history graphs of repositories is *not* the purpose of `gitdags`... 

## Dependencies

To use `gitdags`, you will need

* a LaTeX distribution,
* the `tikz` package (v3.0 or later),
* the [`xcolor-solarized`](https://github.com/Jubobs/xcolor-solarized) package.


## An example

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

Organize


Since the other tools have their owns [tutorials](https://github.com/fvera002/ucr-cs100/tree/2015spring/textbook/tools),
we will just skip this part.


