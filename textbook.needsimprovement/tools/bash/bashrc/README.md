Customizing .bashrc for Fun and Profit
=====================
<a name="top"/>
<h1>Table of Contents</h1>
[1. Introduction](#intro)

[2. Syntax and Basics](#basics)
+ [Variables](#vars)
+ [Functions](#funcs)

[3. The Point of All This](#finally)
+ [`$PS1`](#ps1)
+ [Alias](#alias)
+ [Color and Beyond](#color)
+ [Git Branch Prompt Information](#git)

[4. Conclusion](#conclusion)

[5. Useful Resources](#moar)


<a name="intro"/>
<h2>Introduction</h2>

<code>.bashrc</code> refers to the file that allows customization of [Bash](http://en.wikipedia.org/wiki/Bash_%28Unix_shell%29), and is located at <code>~/.bashrc</code> on Linux systems. Customizing <code>.bashrc</code> will allow you to be a more efficient programmer in the Unix environment, since you can easily create and modify your own custom commands, variables, and functions to your taste. 

`.bashrc` is simply a Bash script that will run when Bash is started interactively. Its definitions will remain persistent throughout the existence of that shell. This guide will explore the process of customizing Bash through `.bashrc`, in order to create not just a workable, but enjoyable programming environment. 

Note: If you would rather not read a guide, and instead ~~steal~~ examine a custom `.bashrc` file that has been created with CS100 functionality in mind, check out the example `.bashrc` file located in this folder.

<a name="basics"/>
<h2>Syntax and Basics</h2>

Before we delve into the possibilities, we should go over some basics of what we can user in `.bashrc` to create the file that we want. `~/.bashrc` is written in the Bash syntax. This language is very powerful, and is full of simple tools that will allow you to express complex commands succinctly. In the language, we find there are some constructs that will be useful to you in understanding and, more importantly, creating your own useful tools in Bash. Note that the `#` character denotes the comment symbol. Everything after a `#` will be ignored when entered as a command.

<a name="vars"/>
<h4>Variables</h4>
[Variables](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-5.html) in bash are super simple. They work much as they do in other high level languages, though there are a few caveats. Consider the following code from a Bash script:

    okra='wogmalumpa'         # define a delicious variable
    echo ${okra}              # prints "wogmalumpa" to stdout, $okra also valid

Note that there are no spaces around `=` in the first statement. To assign variables, this "whitespaceless" syntax is required. In the terminal, once <code>okra</code> is defined in <code>.bashrc</code> (as above), one can check its value by typing the following into the terminal (the <code>$</code> denotes the prompt, don't type that).

    $ echo ${okra}              # prints "wogmalumpa"

Variables will be useful when we wish to work within our <code>.bashrc</code> file, as well as in the terminal itself. Variable substitution will always be of the form <code>#{var}</code>. There are many more syntactical options in Bash, which are covered quickly and succinctly [here](http://www.cheat-sheets.org/saved-copy/shellcheatsheet.pdf).

Variables in <code>.bashrc</code> are also important since some are predefined to interact with your shell. For instance, <code>echo $HOME</code> in the terminal will show you what the tilde is interpreted to - that is - your home directory. To make Bash always feel like <code>$HOME</code>, you can simply change the value of the environment variable on the command line, in this form:

    $ HOME=/your/proffered/path
    $ echo $HOME                    # prints /your/preferred/path
    $ cd ~                          # takes you to /your/preferred/path

Note that this lasts only for the duration of the shell.

<a name="funcs"/>
<h4>Functions</h4>
[Functions](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-8.html) in bash scripts can help break up code logically. They follow a simple syntax. Consider the following code, which will change the current working directory to the specified directory on Bash startup:

    take_me_home () { cd /your/preferred/path; }
    take_me_home

`take_me_home` is a function. Functions in Bash are similar to those in programming languages you may have used before already, such as C or Java. After defining the function, you can call it wherever you like within the file simply by invoking its title, as above. Should you wish to use arguments passed to the function, call them in order with `$1, $2, $3`, and so on. In this particular code, Bash will, on startup, take you directly to the directory you specify in <code>take_me_home()</code>.  What's more, you can now call `take_me_home` anywhere in your shell, and it will always take you to the specified directory!

<a name="finally"/>
<h2>The Point of All This</h2>
Now that you know a few things about Bash scripting syntax, it's time to get into the fun stuff and customize Bash!

<h3><code>$PS1</code></h3>

`$PS1` is a Bash variable that contains the string that will be printed as the prompt each time Bash awaits a command from the user. It can be customized with some certain escape characters. They are decoded in a special way. Here, we see the use of <code>\u</code>, <code>\h</code>, and <code>\w</code>.

    me@computer:/home/ $             # here, PS1 = "\u@\h:\w", that is, user@hostname:current/working/directory  
    me@computer:/home/ $ PS1="\u $ "
    me $                             # The prompt prints even less information.
    me $ PS1="$ "
    $                                # a very minimal example
    
In `.bashrc`, we can alter `PS1` and all spawned instances of Bash by writing `export PS1="\$ ";` in `.bashrc`. Since it will run on Bash startup, your user prompt will always be whatever you set it to in that line.

Particularly useful escape sequences to use for `PS1` customization include:

Escape Sequence | Meaning 
--- | --- 
`\u` | user
`\h` | hostname
`\w` | current working directory
`\n` | newline 
`\T` | current time (12hr format) 
`\#` | command number of this command (corresponds to history)
`\\` | a backslash! 

See a full list [here!](https://wiki.archlinux.org/index.php/Color_Bash_Prompt#Prompt_escapes)

<a name="alias"/>
<h2>Alias</h2>

After some experience with the shell, you might find yourself tiring of typing cumbersome command strings over and over. Aliases will save you from this pain. In <code>.bashrc</code>, consider adding lines such as these:

    alias ll='ls -alF'                          # long-listing format for ls
    
    alias c='clear'                             # useful, common
    
    alias ..='cd ..'
    alias ...='cd ../../../'
    alias ....='cd ../../../../'                # and so on
    alias meminfof='free -mlt'                  # memory information
    
    # print subdirectories in a tree visualization
    alias tree="ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'"
    
    # create a random password
    alias genpasswd="strings /dev/urandom | grep -o '[[:alnum:]]' | head -n 30 | tr -d '\n'; echo"

...and so on. Aliases are a very quick way to boost efficiency for simple commands. You can find more interesting aliases in the sample `.bashrc` file located in this directory.

<a name="color"/>
<h3>Colors</h3>

Bash has color features based on [ANSI escape codes](http://en.wikipedia.org/wiki/ANSI_escape_code). This is occasionally extra credit, but may more importantly be used to expand your zen. For instance, these color codes, added to your <code>~/.bashrc</code> file, will allow you to select colors using variable substitution, as discussed earlier.

    # Normal Colors
    Black='\e[0;30m'        # Black
    Red='\e[0;31m'          # Red
    Green='\e[0;32m'        # Green
    Yellow='\e[0;33m'       # Yellow
    Blue='\e[0;34m'         # Blue
    Purple='\e[0;35m'       # Purple
    Cyan='\e[0;36m'         # Cyan
    White='\e[0;37m'        # White
    
    # Bold
    BBlack='\e[1;30m'       # Black
    BRed='\e[1;31m'         # Red
    BGreen='\e[1;32m'       # Green
    BYellow='\e[1;33m'      # Yellow
    BBlue='\e[1;34m'        # Blue
    BPurple='\e[1;35m'      # Purple
    BCyan='\e[1;36m'        # Cyan
    BWhite='\e[1;37m'       # White
    
    # Background
    On_Black='\e[40m'       # Black
    On_Red='\e[41m'         # Red
    On_Green='\e[42m'       # Green
    On_Yellow='\e[43m'      # Yellow
    On_Blue='\e[44m'        # Blue
    On_Purple='\e[45m'      # Purple
    On_Cyan='\e[46m'        # Cyan
    On_White='\e[47m'       # White
    
    NC="\e[m"               # Color Reset
    
Using these, we may more easily use colors, without having to think in terms of confusing brackets and numbers. Consider, for example, constructing this function, which reminds you, in haiku form, of your frailty:

    function _exit
    {
        echo -e "${Blue}a crash reduces\nyour ${Red}${On_White}expensive${NC}${Blue} computer\ntosimple ${Black}stone${NC}"
    }
    trap _exit EXIT

This function will be called when we exit Bash, since we trap the `EXIT` signal with <code>trap</code>. To ~~test~~ experience this haiku, try calling Bash within a Bash shell, then exiting it, as below:

    $ /bin/bash
    $ exit              # enlightenment awaits
    
These colors can be similarly used on the command line, or in any scripts you may write. Let us say, for instance, that you wished to color the output of the `pwd` command. You could simply define a function, and call it whenever you wish to have the altered output. For instance:

    red_pwd {
        echo -e "${Red}`pwd`${NC}"
    }
    
With this defined in `.bashrc`, you will suddenly be able to type have a red `pwd` whenever you want! But why should we be restricted to red? Consider this function, which uses parameters to generalize colors:

    function mod_pwd {
        if [ $1 = "red" ]; then
            echo -e "${Red}"
        elif [ $1 = "blue" ]; then
            echo -e "${Blue}"
        elif [ $1 = "green" ]; then
            echo -e "${Green}"
        fi
        pwd
        echo -e "${NC}"
    }
    
This concept is extensible to many more useful customizations. The following, more useful function composes some ideas into one:

    function extract_pwd {
        for file in $( ls | grep "^.*\.tgz$" ); do
            tar -xvf $file
        done
    }
    
    function tgz_pwd {
        local files=$(ls)
        tar -cvzf $1 $files
    }
    
The first function finds and extracts all `.tgz` files in the current directory. The second function tars all files in the current directory, and gives them a name specified by the first argument to the function `$1`. Here you can see the power of functions. With just a few lines of code, you can create functions of huge timesaving value.

<a name="git"/>
<h2>Git Branch Prompt Information</h2>

If you are familiar with the `hammer` server within UCR's CS department, you may have noticed that the prompt behaves a certain way when inside of a git repository, by displaying the current branch information. It turns out that doing that is actually fairly simple, and can even be expanded to be slightly cooler! Consider the following additions to `.bashrc`:

    # print the branch name for git
    function git_branch_pun_intended {
        __git_ps1 "${1:-(%s) }"
    }
    
    # Add the branch to PS1
    export GIT_PS1_SHOWDIRTYSTATE=yes
    export PS1="\$(git_branch_pun_intended)${PS1}";
    
The function definition simply gets the name of the branch and formats it slightly, such that it lies flush with the terminal window edge. The next segment sets a variable called `GIT_PS1_SHOWDIRTYSTATE` which appends a `*` to the branch name if there are changes in the repository, and a `+` to the branch name if there are additions staged and ready for commit within the repository. This works for all folders and subfolders in any git repository. Note: If you happen to work with other version control systems, such as Mercurial, Subversion, or Bazaar, check out [this](http://blog.grahampoulter.com/2011/09/show-current-git-bazaar-or-mercurial.html) guide to get the same effect.

<a name="conclusion"/>
<h2>Conclusion</h2>
Hopefully seeing this small primer has inspired you with some ideas of your own functionality to add to your Bash shell via `.bashrc`. To see an example Bash customization file (and hopefully add to it!), please look at the `.bashrc` file located in this directory, or start your own. Good luck!

<a name="moar"/>
<h2>Useful Resources</h2>
[Mike G's introduction to Bash Programming](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html)

[Introduction to Aliases](https://www.digitalocean.com/community/tutorials/an-introduction-to-useful-bash-aliases-and-functions)

[Try Putting These in `.bashrc`!](http://stackoverflow.com/questions/68372/what-is-your-single-most-favorite-command-line-trick-using-bash)

