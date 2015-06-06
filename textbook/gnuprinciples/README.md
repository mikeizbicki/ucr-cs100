# The Unix principles
## writing clear code the GNU way

Eric Raymond's *The Art of Unix Programming* introduces 17 software design rules
meant to make developers more productive and less frustrated when maintaining each other's code.
You probably don't talk much about these rules in any CS course,
and following them is by no means a requirement for CS100.
But your future co-workers will probably like you better
if you understand how to apply them in your own work.

We're going to look at some of these principles from the perspective of GNU/Linux,
one of the largest open-source projects in the world.

###Rule of Modularity
*Programs should be made up of small, simple parts*

If you've ever seen a thousand-line `main()`,
you understand why this rule exists.
At its simplest, the Rule of Modularity means
that your program should be broken up into functions.
Ideally, these functions shouldn't be tailor-made to your project
-- they should be general-purpose bits of code with many potential uses.

For example, GNU's **echo** defines a `hextobin()` function
that takes a single hexadecimal character, like 'A' or '3' or '0',
and converts it to an integer.
**echo** has a single specific use for this function:
it allows the user to echo any byte to the screen.
But because converting from hex digits to actual numbers is very common in console applications,
the authors of **echo** created a function so that other projects would have access to it.

###Rule of Clarity
*Write for developers first, computers second*

###Rule of Economy
*Your own clock cycles are more precious than your computer's clock cycles*

These two rules tie into each other often:
new programmers trying to optimize performance
end up writing an ugly mess that's impossible for others to read and maintain.

Let's look at `hextobin()` again, more closely this time.
Here's the function's definition;
it assumes you're only feeding it valid hex digits (0-9 or A-F):

    static int
    hextobin (unsigned char c)
    {

        switch (c)
        {
        default: return c - '0';
        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
        }
    }

Switch-case statements? Who uses those?
You'd probably get a more efficient conversion by doing this:

    static int
    hextobin_fast (unsigned char c)
    {
        return (c & 223 >= 'A') ? ((c & 223) + 9-'A') : (c - '0');
    }

Is it clear what this function is doing? It's mostly the same:
if c is a letter, return 10-15; if it's a numeral, return 0-9.
But if you wrote this, it'd take a few minutes for someone else to understand it.
Clear, legible code is more important than one or two nanoseconds of processing time.

###Rule of Silence
*If nothing is wrong, don't say anything*

When you run **cp**, **rm**, or similar programs,
watch what gets printed to the screen.
Normally, you'll get something like this:

    $ cp README.md READMETOO.md
    $

No output means **cp** worked correctly.
This is in contrast to GUI applications,
where progress bars and little spinning cursors tell you that your computer's doing something.
This is important because it's not just you reading the terminal output
-- other programs care about it too.
This brings us to the next rule...

###Rule of Composition
*Programs should communicate with each other*

In Unix, everything is text.
You may think that's just Linux users being arrogant purists,
but there's a good reason for the text-based interface:
it allows programs to talk to each other.

Imagine an **ls** program that printed filenames in huge ASCII art letters
so they could be read more easily.
If we tried to **grep** the output of that program, we'd be unable to search files by name.

###Rule of Repair
*If something is wrong, be obnoxious about it*

A good program doesn't report failure unless it absolutely cannot continue,
and if it does report failure, it should explain exactly what caused the failure.

Let's try echoing some text to a file:

    $ cat helloworld.txt >> finalproject.txt
    $

Because **cat** didn't print an error message, we assume that finalproject.txt has the correct information in it.
But what if **cat** had failed for some reason,
such as a permission error or a mistyped filename?
When we try to use the file elsewhere, we could get unexpected errors,
which may not be detected until days after the fact.

###Rule of Extensibility
*Design for the future*

A good program will be used and expanded upon for years.
If your program can't be expanded upon easily,
users will eventually get fed up and try something else.

GNU **echo** accepts only three flags,
and arguably could still work with no flags at all.
But it still uses the same flag-parsing code as the other GNU programs,
so that future developers can define new flags if the need arises.

##

I've included the sources for GNU **echo** and **cp** so you can see them in action.
I hope this brief look at the Unix principles makes you a better programmer,
or at least makes other programmers like you more.
