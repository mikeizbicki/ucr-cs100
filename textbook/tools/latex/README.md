##Tutorial on LaTeX and more unix tools

This is a tutorial on LaTeX that combine lots of unix tools together. 

As computer scientists, we are supposed to write papers and other kind of documents that require features not easily found
in conventional word processors. With that being said, LaTeX is a great tool that produces beautiful type and 
is written in a language that is fairly intuitive. Therefore, this tutorial is going to guide you through the process
of creating an article using:
* LaTeX: to create the documents
* git: to version control the documents
* vim: to edit the text
* Makefile: to put things together
* pdflatex: to output as a pdf file.


###Installation 

The following commands are the only thing you need to install LaTeX on Debian or Ubuntu:

```
$ apt-get update
$ apt-get install texlive texlive-base
```

If you need more help installing, you can find it [here](http://www.tug.org/texlive/).

Since the other tools have their owns [tutorials](https://github.com/fvera002/ucr-cs100/tree/2015spring/textbook/tools),
we will just skip this part.

###First steps
Now that the package to compile TeX files is installed, let's get started. 

####Before coding

Throughout this tutorial we will be using the folder `article`. After creating the folder (i.e. `mkdir`) and navigating by using the `cd` command 
to get to the `article` folder, initialize the git repository: 

`git init`

Time to get some TeX code finally up. 

Let's create and edit out first file through `vim`: 

`vim part1.tex`

Before start entering text into your file, don't forget to press `i` while on `vim` to enter _insert mode_.

####My First LaTeX

The following text creates a basic file: 

```
\documentclass[12pt]{article}
\begin{document}

Lorem ipsum is a pseudo-Latin text used in web design, typography, layout, and 
printing in place of English to emphasise design elements over content. 

It's also called placeholder (or filler) text. It's a convenient tool for mock-ups. 
It helps to outline the visual elements of a document or presentation, eg typography, font, or layout.

\end{document}
```

This small example shows us that the first information LaTeX needs to know when processing a file is
the type of document. This is specified with the `\documentclass` command. Further explanation on different classes 
can be found [here](http://en.wikibooks.org/wiki/LaTeX/Document_Structure#Document_classes).

After saving and closing vim (i.e. `:wq`), it's time to compile our first LaTeX file and create the `.pdf`. 
One simple command should do all this work for us:

`pdflatex part1.tex`

If everything worked fine, now you should be able to open the pdf file `part1.pdf` that will look like this:



