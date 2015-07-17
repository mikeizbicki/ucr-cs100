#Tutorial on LaTeX

As computer scientists and engineers we are supposed to produce papers and to document programs that we create.
With that being said, we want to present LaTeX — a great tool which produces beautiful type and is written in an intuitive language. 

## A brief history
**TeX** is a program designed by Donald Knuth in the 70s to allow everybody to produce high-quality written content using a fair amount of effort, and return the same output on every computer.

**LaTeX** is a program that collects commands using TeX as processing base and it was created by Leslie Lamport in the 80s in order to facilitate the use of TEX through commands for different functions.

If you want to know more about it you can check [Tex page](http://en.wikipedia.org/wiki/TeX) and [LaTeX page](http://en.wikipedia.org/wiki/LaTeX) on wikipedia!


##Structure

The LaTeX language is based on commands that always starts with `\`, which is a marker. 
The commands are written like this `\<command>` or between `\begin{<command>}` and `\end{<command>}`.
This is, instead of `<command>` you will replace it as the following example.

```latex
\documentclass {article}
\title {My first \LaTeX}
\author{your_name_here}
\begin {document}
Hello World! This is my first \LaTeX!
\end {document}
```
Everything that comes after `\end {document}` will be ignored. 
In the example above we used the document class `article`, but there are many classes that you can use.
Classes sets the overall document format like the available sectioning structure and also defines some basic font related macros.
You can find further explanation on different classes [here](http://en.wikibooks.org/wiki/LaTeX/Document_Structure#Document_classes).

The next step to generate our first pdf is compiling.
One simple command on the terminal should do the hard work for us:

`pdflatex example1.tex`

As you can see it's as simple as that. 
If you have done everything correctly so far, running the command `pdflatex` and passing the name of your TeX file would be everything you need. 
You're done! :D
The resulting pdf show look like this:

![example1](images/example1.png)

If you want, you can take a look on the pdf file [here](examples/example1.pdf). 

The fact that LaTeX uses plain text files is a great advantage, so it is compatible with git.
It means that you can version control your TeX files and benfit from all advantages git offers.

##Style
In the `\documentclass` tag you may want to define some of your document's properties style as optional parameters.
The only difference from the example above is the following line:

```latex
\documentclass [a4paper, 12pt, landscape] {article}
```

This is, between the `[]` we defined the paper size, the letter size, and the layout of the page.
There are many options that you may use in this tag.
For example, you can create your document with two columns, change the font size, type and color, change the layout of the document and many other things.
All the possibilities you can check [here](http://en.wikibooks.org/wiki/LaTeX/Document_Structure#Document_Class_Options).


##Packages
Packages are add-ons that implement additional features for documents written in LaTeX.
Here is a great example:

```latex
\documentclass[12pt]{article}
\usepackage{color}
\begin{document}
Lorem ipsum dolor sit amet, pro saperet luptatum repudiandae an. 
Ex nam everti inimicus, ex has error scaevola consetetur, pericula molestiae ut usu.
Duo te consul concludaturque.
\textcolor {red} {Et blandit petentium torquatos eum, eam an facilis principes inciderint, nec an expetenda delicatissimi. 
Ut sea agam laudem}.
\end{document}
```

As you can see, packages are always inserted before `\begin{document}` by using the command `\usepackage [optional]{package}`.
If you want to check the packages that are pre-installed with LaTeX, check the  [package reference page](http://en.wikibooks.org/wiki/LaTeX/Package_Reference). 

Compile with: 

`pdflatex example2.tex`

Result:

![example2](images/example2.png)

If you want, you can take a look on the pdf file [here](examples/example2.pdf). 

Also, know that anyone can create their own packages, even you!
In this case, it's just put the package file in the same folder of the project. 
In the [CS Environment section](/textbook/tools/latex/README.md#cs-environment) you are going to find a example on how it works.

##Math Environment
One of the main advantages of using LaTeX is the ability to write math formulas easily.
That's why we, as science, math and engineering students, should learn LaTeX to write papers, articles, etc.

###Math Tags
There are three main ways to insert formulas or other calculations. 
This section will go over these three ways and also give more information about some useful tags to do math.

* **Inline**: You can insert a formula in the same line as you text by using dollar sign to start and to end a formula. 

    ```latex
  The volume inside a sphere is given by $V = \frac{4}{3} \pi r^{3}$.
  ```
  
  Note that in this example the `\frac` tag was used to build a fraction.
  The first pair of curly brackets contains the numerator and the second contains the denominator.
  Also, this example uses the `\pi` tag to show the corresponding symbol to the Greek letter Pi. 
  
  Compile with: 

  `pdflatex example3.tex`

  Result:
    
  ![example3](images/example3.png)
    
  If you want, you can take a look on the pdf file [here](examples/example3.pdf). 

* **New line with section number**: This is a really nice looking way to organize your formulas.
  You just need to use the tag `\begin{equation}` and `\end{equation}` to close.

    ```latex 
  \begin{equation}
  f(x) = \sqrt{x^{a} + y^{b}}
  \end{equation}    
  ```

  By doing this, LaTeX will centralize your formula and also insert whatever section it belongs to.
  Also, the tag`\sqrt` was used to represent a square root so that everything in between the curly brackets gets under the square root symbol. 
  Furthermore, note that by using the syntax `x^{a}`, `x` will become the base and `b` will become an exponent.
  Thus, we will have `x` to the power of `a`. 
  
  
  Compile with: 

  `pdflatex example4.tex`

  Result:
    
  ![example4](images/example4.png)
    
  If you want, you can take a look on the pdf file [here](examples/example4.pdf). 

* **New Line without section number**: If you do not need the section number, this is the best option.

  ```latex
  \[
  x_{3j}^{2i}
  \]
  ```
  
  As you can see, it can easily be done by using the tag `\[` and `\]` to close.
  Also, another important thing to note is that the underscore was used to indicate that the value between the curly brackets is being used as an index.
  
  Compile with: 

  `pdflatex example5.tex`

  Result:
    
  ![example5](images/example5.png)
    
  If you want, you can take a look on the pdf file [here](examples/example5.pdf). 


###CS Environment
As Computer Scientists we may want to use LaTeX to document what we are coding.
The package `listings` typesets code in LaTeX, such as C/C++, Java and others.

```latex
\documentclass[a4paper]{article}
\usepackage{xcolor}
% Define new colors
\definecolor{green}{rgb}{0,0.5,0}
% Setting layout to display codes C ++
\usepackage{listings}
\lstset{
  language=C++,
  basicstyle=\ttfamily\small, 
  keywordstyle=\color{blue}, 
  stringstyle=\color{green}, 
  commentstyle=\color{red}, 
  extendedchars=true, 
  showspaces=false, 
  showstringspaces=false, 
  numbers=left,
  numberstyle=\tiny,
  breaklines=true, 
  backgroundcolor=\color{green!10},
  breakautoindent=true, 
  captionpos=b,
  xleftmargin=0pt,
}
\pagestyle{empty}
\begin{document}
\begin{lstlisting}
#include 
using namespace std;
int main()
{
  /* Comment */
  int n, i, a = 0, b = 1, F;
  cout << "Enter the number of terms of Fibonacci’s sequence: ";
   cin >> n;
  cout << a << " " << b << " ";
   for (i = 0; i < n - 2; i++)   {
     F = a + b;
     cout << F << " ";
     a = b;
     b = F;
   } cout << endl; return 0;
 } \end{lstlisting}
\end{document}
```
This example is in C++, but we can change to many languages. It's just change the value of the line `language=C++`

Compile with:

`pdflatex example6.tex`

Result:

![example6](images/example6.png)

If you want, you can take a look on the pdf file [here](examples/example6.pdf). 


In order to use many languages in the same LaTeX file, we need to use this:

```
\lstdefinestyle{LaTeX}{
  language={[LaTeX]TeX},
  basicstyle=\ttfamily\small, 
  identifierstyle=\color{black}, 
  keywordstyle=\color{blue}, 
  commentstyle=\color{red}, 
  extendedchars=true, 
  showspaces=false, 
  showstringspaces=false, 
  numbers=none,
  breaklines=true,
  backgroundcolor=\color{yellow!20}, 
  breakautoindent=true, 
  captionpos=b,
  xleftmargin=0pt,
  frame=none,
  rframe={},
}
```
You can find a complete example using many languages  [here](/textbook/tools/latex/ex23.tex).

#Combining Unix tools

Now, let's combine some of the main Unix tools together, so you can have an idea on how use it in the future.

First of all, let's set our environment. 
We will be using the folder `article`. 
After creating the folder (i.e., `mkdir article`) and navigating by using the `cd` command to get in on it, initialize the git repository: 

`git init`

Time to get some TeX code finally done! Let's create and edit out first file through `vim`: 

`vim loremipsum.tex`

The following text creates a basic file.

```latex
\documentclass[12pt]{article}
\begin{document}
Lorem ipsum dolor sit amet, pro saperet luptatum repudiandae an. 
Ex nam everti inimicus, ex has error scaevola consetetur, pericula molestiae ut usu. 
Duo te consul concludaturque.
Et blandit petentium torquatos eum, eam an facilis principes inciderint, nec an expetenda delicatissimi. 
Ut sea agam laudem. 
\end{document}
```

After saving and closing `vim`, it's time to compile our LaTeX file and create the pdf file. 
Compile with:

`pdflatex example7.tex`

When compiled, it’s going to look like this:

![example7](images/example7.png)

If everything worked fine, now you should be able to open the pdf file [example7.pdf](examples/example7.pdf). .


If we succeed at the previous steps, it's time to do some commits. 
But first, we need to add the files to the staging area of git. 
Remember! We should commit ONLY source code, README and LICENSE files.
This is, do not add pdf files.
In the following example we are going to create some tags and branches just to exemplify the usage of `gitdags` that comes next.

```
echo "This is the most important file of your project" > README
git add README
git commit -m "Starting project"
git tag beginning
git branch coding
git checkout coding
git add loremipsum.tex
git commit -m "Added tex file"
git checkout master
git merge coding
touch LICENSE
git add LICENSE
git commit -m "Added license file"
```
In small projects you may not have a lot of commits, but in huge projects it's gonna happen all the time.
It allows collaboration with other people using the same tools that you are already familiar with.
So now, we are going to present a package for drawing Git history graphs using LaTeX, called gitdags. 
It can be really helpful to draw a really nice looking git repository for this [lab1](/assignments/lab/lab1-git).

##Gitdags

`gitdags` is a LaTeX package that allows the production of pretty Git history graphs. 
It doesn't make automatic generation of Git history graphs, but it's handy.
We really encourage you to use it in [this lab](/assignments/lab/lab1-git/using-git.md).

##Dependencies
To use `gitdags`, we will need
* [gitdags.sty](https://raw.githubusercontent.com/Jubobs/gitdags/master/gitdags.sty) file;
* `tikz` package - come automatically installed with every latex distribution;
* [`xcolor-solarized`](https://github.com/Jubobs/xcolor-solarized) package.

If we decide to use `gitdags` to draw the Git history graphs of the example above, we may use the following code. 
The explanation is commented on it.

```latex
\documentclass[landscape, 12pt]{article}

\usepackage{subcaption}
\usepackage{gitdags}

\begin{document}
\begin{figure}
    \centering
    \begin{tikzpicture}
      \gitDAG[grow right sep = 2em]{ % arrow's size
        % Commits that you create appear here 
        Starting Project -- { 
          Added LICENSE file, 
          Added TEX file,
        }
      };
      % Tag reference
      \gittag
        [beginning]       % node name
        {beginning}       % node text
        {above=of Starting Project} % node placement
        {Starting Project}          % target
      % Branch
      \gitbranch
        {master}     % node name and text 
        {above=of Added LICENSE file} % node placement
        {Added LICENSE file}          % target
      % Branch
      \gitbranch
        {coding}     % node name and text 
        {below=of Added TEX file} % node placement
        {Added TEX file}          % target
      % HEAD reference
      \gitHEAD
        {above=of master} % node placement
        {master}          % target
    \end{tikzpicture}
\end{figure}

\end{document}
```

This is just a simple example on how you can use it.

Compile with:

`pdflatex example8.tex`

Result:

![example8](images/example8.png)

If you want, you can take a look on the pdf file [here](examples/example8.pdf). 

A more complex example can be found [here](https://github.com/Jubobs/gitdags/wiki).
We really recommend that you take a few minutes and "play" with this codes.

#Conclusion
So as you can see, we can use:
* LaTeX: to create the documents
* [git](/assignments/lab/lab1-git/using-git.md): to version control the documents
* [vim](/cheatsheets/vim-cheatsheet.pdf): to edit the text
* [Makefile](/textbook/tools/make): to put things together
* pdflatex: to output as a pdf file.

We hope you liked this tutorial and use it in the future!
