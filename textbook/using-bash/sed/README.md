### <a name="What is *sed*?"></a>What is sed?

`sed` (stream editor) is a quick and efficient way of changing the contents of a file without having to go in and change things yourself.

#### <a name="Table of Contents"></a>Table of Contents

1. [How Does it Work?](#How Does it Work?)

2. [What Does it Look Like?](#What Does it Look Like?)

3. [What Can We Do With it?](#What Can We Do With it?)

4. [Substitution](#Substitution)

5. [Emulation](#Emulation)

### <a name="How Does it Work?"></a>How Does it Work?

`sed` works by maintaining two data buffers (temporary containers): the active **pattern**
space and the auxiliary **hold** space. Both begin empty.

For our purposes, let&#39;s look at the following `sed` command:

```
sed 's/Hello/Goodbye/' testfile
```

`sed` operates by going line by line of the testfile and placing each line
into the **pattern** space after removing any leading newline characters.

So if we had a file containing,

```
#filename: testfile
Hello World!
This is a test file
Computer Science is fun!
```

`sed` would take the string "Hello World!\n," remove the newline character, and place the string into the pattern space. Once the text is in the pattern space, the provided commands are executed. Now that "Hello World!" is in the pattern space, the `'s/Hello/Goodbye/'` command is applied to it. A command will only execute if the text in the pattern space qualifies for the command, or matches the pattern. Since "Hello" was present in the pattern space, substitution command will swap out "Hello" with "Goodbye."

When the end of the line is reached, the pattern space is output to the output stream (standard output) and has its newline replaced back in. After `'s/Hello/Goodbye/'` has been applied the pattern space, the newline is added back to the string. So the output from the first line will be "Hello World!\n." Another cycle then begins for the next line of text in the file. Next, the string "This is a test file\n" is placed into the pattern space. This time however, "Hello" is not present, so `'s/Hello/Goodbye/'` does not execute, and "This is a test file\n" is simply output to the output stream. The same will occur for the final string. The **pattern** space is emptied out between cycles; however, the **hold** space maintains its data throughout the process. 

This example does not actually need to use the hold space since there was no need for temporary storage. So let&#39;s look at a different example that does use the hold space.

Say we want to capture the line before a line that matches a search pattern. The command,

```
sed -n '/regex/{x;1!p;x}; h'
```

will do this.

Before you can see what this expression is doing, there are a few things you should know.

The `-n` flag turns off `sed`&#39;s printing, unless specified some other command, like `p`. `p` will print the pattern space to standard output and `regex` is simply a stand-in for a regular expression, a search pattern (more on this later). The most important things though are `x` and `h`. `x` swaps the pattern space and the hold space while `h` copies the current pattern space to the hold space.

So the above `sed` command behaves as the previous example right up until the point the string in the pattern space matches the regular expression. The `h` command at the end of the script forwards each line into the hold space. Whenever a line matches the regex expression, `x` swaps the hold space and the pattern space. So the lines that do not match the regular expression, are available to be output to the output stream and the matching string is temporarily stored. The `p` prints the current pattern space, which currently contains the line before the matching line. The second `x` swaps the hold space and the pattern space again so that the script can carry on as normal.

The "1!" in front of the `p` signals `p` to only print all lines that are not the first line.

### <a name="What Does it Look Like?"></a>What Does it Look Like?
`sed` takes the general form,

```
sed options ... [ script ] [ inputfile ... ]
```

* *options* refers to a passed in flag (i.e. `-n` or `-i`)

* *script* refers to a pattern that will be used to filter the input/a regular expression. This is also where you specify which `sed` commands you wish to use (i.e `s` or `p` or `g`)

* *inputfile* refers to the filename of the file you want to modify

*For a full list of the `sed` options and commands visit the [`sed`][sed] man page.*

`sed` can be called in various ways.

For example, say you have a file containing a list of subscriber email addresses (each email address on its own line) and you want to change all of the email domains from "aol.com" to "gmail.com". One way you could very quickly do this and would be to pass your old email list into the `sed` command as such:

```
sed 's/aol.com/gmail.com/' oldlist > newlist
```

or
```
sed -i 's/aol.com/gmail.com/' oldlist      #the '-i' flag modifies the passed in file and puts the newly modified file back into the old one
```

which replaces the first occurrence of "aol.com" on each line of the input source with "gmail.com".

**NOTE:** `sed` can be written with or without single quotations. Although it is better practice to always include them.

Alternatively, you can accomplish the same goal by piping the old email list to `sed`:

```
cat oldlist | sed 's/aol.com/gmail.com/' > newlist
```

If `sed` is called without a source of input:

```
sed 's/aol.com/gmail.com/'
```

`sed` will become "hungup" and will wait for input from standard input (input manually entered from the user) where `sed` will execute its commands as the user passes in new lines for it to analyze.

`sed` commands can also be listed together into a file called a **sed script** (which is used instead of an explicit regular expression or search pattern with the `-f` flag). A `sed` script would look like,

```
# 'sed.sh' replaces digits with their English word
s/0/zero/g
s/1/one/g
s/2/two/g
s/3/three/g
s/4/four/g
s/5/five/g
s/6/six/g
s/7/seven/g
s/8/eight/g
s/9/nine/g
```
You would then take this file and pass it into the `sed` command.

```
sed -i -f sed.sh numbers
```

Each script expression in "sed.sh" will make a pass through "numbers" and make its specific changes. So when the above command finishes, every digit in the file will be converted to its English name.

### <a name="What Can We Do With it?"></a>What Can We Do With it?
`sed` can be used for more than just simple text transformations. With regular expressions, `sed` has potential to handle very complex transformations. You can build an entire program using only `sed` (<i.e./> a script that capitalizes all the vowels in a text file and so forth). You can also make `sed` behave like other commands (i.e. `grep` and `head`).

###<a name="Substitution"></a>Substitution

The meat and potatoes of `sed` is the `s` command (s for substitution).

Here is a simple example of `sed` substitution in action:

```
echo aol.com | sed 's/aol.com/gmail.com/'
```

There are four parts to the substitution command:

1. `s` &#8594; Substitute

2. `/.../.../` &#8594; Delimiters

3. `aol.com` &#8594; Regular Expression Pattern/Search Pattern

4. `gmail.com` &#8594; Replacement String

*1.* The command character (in this case `s` for substitution) must go on the left side of the first
delimiter.

*2.* The character after `s` is called a delimiter. The delimiters are needed to parse the command, to separate the substitution command from the search pattern and separate the search pattern from the replacement string. In the case of the above example, the delimiter is a slash, but the delimiter can be any character you want as long as there are three of them:

```
echo aol.com | sed 's/aol.com/gmail.com/'
```
is equivalent to

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

A missing delimiter will result in a "Unterminated 's' command" error.

*3.* The string you want to search for (i.e. "aol.com" the search pattern) is on the left side of the delimiter sequence.

*4.* The string you want to replace the search pattern with (i.e. "gmail.com") goes on the right side.

Now let&#39;s look at a couple real world instances where substitution would be useful.

You are working on a project that you completed back in 2012. You decide to revisit your project and update it in 2104. Upon completing your coding you are left with the task of updating the project year in your README file. All you would have to type to make these necessary changes is one line into your terminal:

```
sed -i 's/2012/2014/g' README.md
```

**NOTE:** The `-i` flag makes `sed` perform in-text editing. Or, in other words, it reads the file, applies the commands, and places the results back into the original file. **Using the `-i` flag is not reversible so you should consider making a backup of a file before changing it.** In fact, if you add a file extension to `-i`

```
sed -i.backup 's/2012/2014/g' README.md
```

`sed` will create a copy of the "README.md" named "README.md.backup" before the changes are made.

Sure, you could argue that the number of year numbers you would have to change wouldn&#39;t be SO big that you couldn&#39;t correct them by hand relatively quickly. But, I would say this is
beside the point. The point is that while you are searching through your README looking for the incorrect year, you could be doing something more worthy of your attention.

With that in mind, let&#39;s move on to the next example.

The president of the UCR ACM chapter has the 100 new members all enter their phone numbers in his laptop. Everyone enters their number in the form of "##########," which is not easy on the eyes. So after the president gets back home and sees that no one distinguished their area code from the rest of the seven digit phone number, he decides to run a `sed` script to place a set of parentheses around the first 3 digits of every phone number.

Since there is no way for him to anticipate the exact first three numbers for each phone number, the president will have to write a **regular expression** to get the job done. Regular expressions themselves are worthy of their own tutorial, so we will not delve too deep into the intricacies of writing one, but we will use them to demonstrate `sed`&#39;s power. For a detailed introduction to regular expressions, please visit [this][regex] tutorial.

The president&#39;s regular expression will require a `^`, which in a regular expression dictates that the match must begin at the start of the line, a
`[[:digit:]]`, which translates to the first character of a match needing to be a digit, and lastly a `&`, which is a variable that represents the pattern that was matched.

Since the president wants to capture the first three digits of each line, he will need three `[[:digit:]]`&#39;s and since he needs to place parentheses around those first three digits, he will simply put parentheses around the `&` after the second delimiter.

The `sed` command he comes up with looks like this:

```
sed -i 's/^[[:digit:]][[:digit:]][[:digit:]]/(&)/' phonelist
```
Now each phone number in the ACM phone list will have a parenthesis around its three-digit area code.

###<a name="Emulation"></a>Emulation

`sed` can imitate other bash commands (although it would probably be more straightforward to just use the premade bash commands `sed` is copying). We will look at 2 commands that `sed` can easily imitate: `grep` and `head`.

* `grep`

The `grep` bash command searches a file for specific text. Like `sed`, `grep` takes in a search pattern to compare input to. Once `grep` finds a match, it prints the line with the matching text
to standard output.

In order for `sed` to do what `grep` does, it will need two additional things: the "-n" option and the "p" command.

The "-n" turns off `sed`&#39;s printing unless requested with the "p" option, which duplicates the input.

Say a secretary at Google wants to make sure they included "employee45@gmail.com" in a file called "elist" containing all the emails of the employees in the office. Using `grep`, the secretary could search
for the email with,

```
grep "employee45@gmail.com" elist
```

or using `sed`, he would search with,

```
sed -n "/employee45@gmail.com/p" elist
```

If nothing is returned, then the employer knows "employee45@gmail.com" has not yet been added to the email list. If the email is echoed back to the screen, then the email has already been included in
the file.

* `head`

The `head` bash command prints the first 10 lines of input to standard output.

As explained with `grep`, the "p" `sed` command will duplicate all of the input passed into it, but if you only want to print the first ten lines of the input, you can specify the line
numbers you want printed back to the screen.

The previously mentioned secretary is tasked with creating a new list of emails that is sorted in alphabetical order by the last name of each employee. Google has just assigned a Scott Adams to the office and has the employee email, "adamsscott@gmail.com". The secretary insists on alphabetizing the email list by hand so they must anticipate where on the list they will need to insert this new
email. Instead of opening the file and looking through all the emails, they only want to look at the beginning of the list since they know there hasn&#39;t been many new additions to the office with a last name beginning
with "A". So they screen a small amount of emails one at a time. To do this they can use `head` to print the first ten emails in the list,

```
head elist
```

or with `sed`,

```
sed -n '1,10 p' elist
```

Now the secretary doesn&#39;t have to strain their eyes to see where to place the new email address.

The above `sed` command also demonstrates `sed`&#39;s ability to set a range to limit the command on. In the case of the above example `1,10` specifies that the command only be applied to lines 1 through 10. If only a single number limit is included,

```
sed -n '5 p' elist
```

only that *nth* line of the input file will be output. In this case, only the fifth line will be output.

Additionally, if you include `!` with a line range, you will capture the opposite of the line range. So the command,

```
sed -n '5! p' elist
```

will output every line except for the fifth line of the input file.

Happy Hacking!

![Image of Linux Penguin]
(http://pixabay.com/static/uploads/photo/2013/07/13/12/31/penguin-159784_640.png)

[regex]: http://www.regular-expressions.info
[sed]: http://linux.die.net/man/1/sed
