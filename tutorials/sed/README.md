#SED TEXT MODIFIER

Welcome to cs100! :smiley: :trollface: :fearful:

![Image of Yaktocat]
(http://pixabay.com/get/5af74f65eb7e7253bd20/1418518821/tux-293844_1280.png?direct)

Today you will be learning about the `sed` bash command!

## <a name="Top"></a>Top

###1. [What is *sed*?](#What is *sed*?)

###2. [How Does it Work?](#How Does it Work?)

###3. [What Does it Look Like?](#What Does it Look Like?)

###4. [What Can We Do With it?](#What Can We Do With it?)

###5. [Why Should We Ever Use it?](#Why Should We Ever Use it?)

### <a name="What is *sed*?"></a>What is *sed*?

`sed` (standing for {**s**}tream {**ed**}itor) is a quick and efficient way of changing the text inside of a file without having to go in and change things yourself.

##### [Back to Top](#Top)

### <a name="How Does it Work?"></a>How Does it Work?
`sed` works by maintaining two data buffers: the active **pattern**
space and the auxiliary **hold** space. Both begin empty.

`sed` operates by going line by line of the input source and placing each line
into the **pattern** space after removing any leading newline characters.
Once the text is in the pattern space, the provided commands are executed.
A command will only execute if the text in the pattern space qualifies for
the command, or matches the pattern. When the end of the line is reached,
the pattern space is output to the output stream and has its newline replaced
back in. Another cycle then begins for the next line of text in the file.

The **pattern** space is deleted between any two cycles; however, the
**hold** space maintains its data throughout the process.

##### [Back to Top](#Top)

### <a name="What Does it Look Like?"></a>What Does it Look Like?
The general format of a call to the `sed` command is as follows:
```
sed options ... [ script ] [ inputfile ... ]
```

* *options* refers to a passed in flag (i.e. **-n** or **-i**)

* *script* refers to a pattern that will be used to filter the input/a regular expression

* *inputfile* refers to the filename of the file you want to modify

In practice, `sed` is not entirely strict in how it can be called.

For example, say you had a file containing a list of subscriber email addresses (each email address on its own line) and you accidently got all of
 the domain names wrong. One way you could quickly and painlessly resolve this dilemma would be to pass your old email list into the `sed` command as follows:
```
sed 's/aol.com/gmail.com/' oldlist > newlist
```

or
```
sed s/aol.com/gmail.com/ oldlist > newlist
```

which replaces the first occurence of "aol.com" on each line of the input source with "gmail.com".

**NOTE:** `sed` can be written with or without single quotations. Although, it is better practice to always include them. It makes recognizing which instructions belong to `sed`
and which instructions belong to another command easier.

Alternatively, you can accomplish the same goal by piping the old email list to `sed`:
```
cat oldlist | sed 's/aol.com/gmail.com/' > newlist
```

If `sed` is called without a source of input:
```
sed 's/aol.com/gmail.com/'
```

`sed` will become "hungup" and will wait for input from standard input (manually entered input from the user), which is not very useful in practice.

#### [Back to Top](#Top)

### <a name="What Can We Do With it?"></a>What Can We Do With it?
Despite what the average programmer might suggest, `sed` can be used for more than just simple text transformations. With regular expressions, `sed` has potential to handle very complex transformations.
You can build an entire program using only `sed` (i.e. a script that capitalizes all the vowels in a text file and so forth). You can also make `sed` behave like other commands (i.e. `grep` and `head`).

For the purposes of cs100, we will confine the scope of our usage of `sed` to the following 2 categories:

####1. [Substitution](#Substitution)
####2. [Emulation](#Emulation)

#####1. <a name="Substitution"></a>Substitution
The meat and potatoes of `sed` is the **s** command (s for substitution)

Here is a simple example of `sed` substitution in action:

```
echo aol.com | sed 's/aol.com/gmail.com/'
```

There are four parts to the substitution command:

1. **s** &#8594; Substitute

2. **/.../.../** &#8594; Delimiters

3. **aol.com** &#8594; Regular Expression Pattern/Search Pattern

4. **gmail.com** &#8594; Replacement String

**1.** The command character (in this case **s** for substitution) must go on the left side of the first
delimiter.

**2.** The character after **s** is called a delimiter. The delimiters are needed to parse the
command, to seperate the substitution command from the search pattern and seperate the search pattern from
the replacement string. In the case of the above example, the delimiter is a slash, but the delimiter can
be any character you want as long as there are three of them:

```
echo aol.com | sed 's_aol.com_gmail.com_'
```

is equivalent to

```
echo aol.com | sed 's^aol.com^gmail.com^'
```

is equivalent to

```
echo aol.com | sed 'sxaol.comxgmail.comx'
```

and so forth.

Each of these instances will have the same output as the original example.

A missing delimiter while result in a "Unterminated 's' command" error.

**3.** The string you want to search for (i.e. "aol.com" the search pattern) is on the left side of the delimiter sequence.

**4.** The string you want to replace the search pattern with (i.e. "gmail.com") goes on the right side.

Now let&#39;s look at a couple real world instance where substitution would be useful.

You are working on a project that you completed a version of in the year 2012. Upon completing your coding you are left with the task of updating the project year in your README file.
A bad programmer would waste their time manually changing each incorrect year number in their README, but you aren&#39;t a bad programmer. You know that
you can complete this task in a matter of seconds. All you&#39;ll type is a one line into your terminal:

```
sed 's/2012/2014/g' README.md > newREADME.md; cat newREADME.md > README.md; rm newREADME.md
```

**NOTE:** It is important to keep in mind that `sed` will not replace the text in the input file on its own. `sed` will print the modified text to standard output. So in order to capture the
changes, you must use output redirection to copy the modified input file into a new file and then copy the contents of that new file back into the old file. Lastly, you
would delete the file you created to do the file transformation (it is always considered good practice to delete files you don&#39;t need).

Sure, you could argue that the number of year numbers you would have to change wouldn&#39;t be SO big that you couldn&#39;t correct them by hand relatively quickly. But I would say this is
beside the point. The point is that while you are searching through your README looking for the incorrect year, you could be doing something more worthy of your attention.

With that in mind, let&#39;s move on to the next example.

A writer for the entertainment website Variety finished writing an article about the recent Sony Pictures hack. The writer gives their article to an editor upon completing it and goes on their way.
Upon reading over the writer&#39;s article the editor notices that instead of accusing North Korea of the reported hacks, they incorrectly gave South Korea credit. The ordinary editor would have
to go in by hand and correct this issue amongst others, but this is no ordinary editor. This editor minored in computer science back in college and remembers that there is a
quick and painless way for him or her to correct this pervasive error. The writer accesses the html code for the article webpage and copies it to a file in his computer called *draft1*.
The editor opens a `sed` script file he or she wrote to autocorrect the articles he or she&#39;s responsible for and adds a new command to the file:

```
#sed script file *autocorrects Variety articles and for this specific case, will transform "South Korea" to "North Korea"
.
.
.
.
.
.
.
s/[a-zA-Z]* //2
s/South Korea/North Korea/g
```

To apply their sed script to the article, the editor uses the `-f` flag and the name of their sed script in place of a pattern or regular expression:
```
sed -f sedscript draft1 > draft2
```

and now "draft2" holds the edited Sony hack article.

#####2. <a name="Emulation"></a>Emulation
As mentioned eariler, `sed` is especially unique in that it can imitate other bash commands (although it would probably be more straight forward to just use the premade bash commands
sed is copying). We will look at two commands that `sed` can easily imitate: `grep` and `head`.

* `grep`

The `grep` bash command searches a file for specific text. Like `sed`, `grep` takes in a search pattern to compare input to. Once `grep` finds a match, it prints the line with the matching text
to standard output.

In order for `sed` do what `grep` does, it will need two additional things: the "-n" option and the "p" command.

The "-n" turns off `sed`&#39;s printing unless requested with the "p" option, which duplicates the input.

Say an employer wants to make sure "employee45@gmail.com" is included in a file called "workersemail" containing all the emails of their employees. Using `grep`, the employer could search
for the email with,

```
grep "employee45@gmail.com" workersemail
```

or using `sed`, he would search with,

```
sed -n "/employee45@gmail.com/p" workersemail
```

If nothing is returned, then the employer knows "employee45@gmail.com" has not yet been added to the email list. If the email is echoed back to the screen, then the email has already been included in
the file.

* `head`

The `head` bash command prints the first 10 lines of input to standard output.

As explained with `grep`, the "p" `sed` command will duplicate all of the input passed into it, but if you only want to print the first ten lines of the input, you can specify the line
numbers you want printed back to the screen.

The previously mentioned employer wants to employ a new email system that is sorted in alphabetical order by the last name of each employee. The employer has just hired a Scott Adams and has
assigned him with the employee email, "adamsscott@gmail.com". The employer insists on alphabetizing the email list by hand so he must anticipate where on the list he will need to insert this new
email. Instead of opening the file and looking through all the emails, he only wants to look at the beginning of the list since he knows he hasn&#39;t hired many employees with a last name beginning
with "a". So he screens a small amount of emails ten at a time. To do this he can use `head` to print the first ten emails
in the list,

```
head workersemail
```

or with `sed`,

```
sed -n '1,10 p' workersemail
```

Now the employer doesn&#39;t have to strain his eyes to see where to place the new email address.

#### [Back to Top](#Top)

### <a name="Why Should We Ever Use it?"></a>Why Should We Ever Use it?
A good programmer is defined by how he or she spends their time, by how much they value their time, and by how efficiently they use their time. Good programmers don&#39;t waste time on tedious coding that
a program or a simple bash command could accomplish in a fraction of the time he or she would need to do it by hand. `sed` and commands like `sed` exist to encourage this "good programmer" mentality.

So when you find yourself in a position where you&#39;ve forgotten to put a set of parentheses around a recurring conditional statement in a cpp file or you want to change
the name of a project in your project README, you&#39;ll have a choice to make: be a bad programmer and waste valuable time making the corrections yourself or be a good
programmer and have `sed` do it for you.

#### [Back to Top](#Top)

Go to the [`sed`][sed] man page for a full list of the `sed` options and commands.

Go to the [`grep`][grep] man page to learn more about `grep`

Go to the [`head`][head] man page to learn more about `head`

Go [here][regex] to learn how to write regular expressions

Happy Hacking!

[regex]: http://www.regular-expressions.info
[sed]: http://linux.die.net/man/1/sed
[grep]: http://linux.die.net/man/1/grep
[head]: http://linux.die.net/man/1/head
