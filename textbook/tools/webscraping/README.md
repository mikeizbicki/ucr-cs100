## Web scraping

This tutorial covers web-scraping with the basic Unix programs: `wget`, `grep`, and `sed`.
By combining all of these simple programs we can create a webscraper.
Webscrapers are used to extract information from websites which can be used in other programs.

### Web scraping and Wget

To download a webpage do: `wget [url]` and view the downloaded content with an editor.
In our example, we’ll be searching for chicken recipes on [allrecipes.com] (allrecipes.com) and compiling it into a single file.
First we’ll need to download all of the recipes off the website, but that’s *a lot* of recipes to
download as well as other irrelevant content.
To narrow it down to only chicken we can specify the regular expression (regex) in our command.

```wget -q -r -c -np -nc --accept-regex allrecipes.com/Recipe/.*Chicken.* allrecipes.com```

Here’s a quick rundown of the flags used above:
- `-q` (quiet) will block the output to avoid cluttering your terminal
- `-r` (recursive) does recursive downloading so we can traverse the entire website and download all the files we need
- `-c` (continue) will resume downloading from where it was stopped earlier in the cases where the process was stopped
- `-np` (no-parent) prevents downloading from parent links which allows us to download every file in the current path and its childs.
This will be fail-safe to prevent downloading files we don’t need
- `-nc` (no-clobber) prevents the overwriting of the same web file if it is run with the `-r` flag thus preserving the original
- `--accept-regex` will only follow web pages with the specified regular expression as its url to avoid downloading files we do not want which would save us both time and resources

If you ran the command without the `-q` flag you should get something like this
![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/wget.gif)

On some occasions, you will be unable to follow certain pages when doing a recursive download.
Some websites block tools like `wget` with a `robots.txt` which tells `wget` what it can and cannot follow.
You can have `wget` ignore `robots.txt` with the flag `--execute robots=off` to bypass the restrictions.
To run multiple instances of `wget` you may place a `&` at the end, to execute it and place it in the background and run the command again for as many times as you want.
However, running too many instances may stress out the server so it’s a good idea to run only a couple.
The time it takes to download is dependent on both the site and your connection.
You can stop the download with `Ctrl + C` to cancel it and run it again later
or run it in the background with `Ctrl + Z` and `bg`.
However, if you have added a `&` you must directly kill the process via `pkill -9 wget` to stop it.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/display.png)

Once it is done, you will have a folder `allrecipes.com`.
Inside of it should contain another folder `Recipe` which contains all the
web content downloaded, each in their respective folders.

### HTML and Grep

After downloading hundreds to thousands of files we will need to get rid of all the clutter in the files we don’t want.
Most of the files we’ve downloaded are in HTML, HyperText Markup Language, which is used to create web pages.
HTML consists of tags enclosed in angle brackets like `<html>` and usually come in pairs such as `<h1>` and `</h1>` with content enclosed in the tags.
We can use this to our advantage when using `grep`.
To do this, we will need to figure out which tags are associated with which part of the web page and the data the tags enclose.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy1.gif)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy2.gif)

To find which part of the web page is associated with which HTML tag simply right-click
and inspect element on the web page as shown.
By looking at the tags that enclose the data you want to extract, you can get an idea of
what the pattern looks like which can be used to build a regex for `grep`.
In our case we’ll be trying to find the following tags:
- `<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name"> __NAME__ </h1>`
- `<span id="lblIngAmount" class="ingredient-amount"> __AMOUNT__ </span>`
- `<span id="lblIngName" class="ingredient-name"> __INGREDIENT__ </span>`
- `<span class="plaincharacterwrap break"> __DIRECTION__ </span>`

The names `__NAME__`, `__AMOUNT__`,  `__INGREDIENT__`, and `__DIRECTION__` are
simply placeholders for the actual values there for that certain recipe.
Since we have multiple patterns we can append them together with the regex OR: ‘\|’.

Example:
```grep -r '<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">.*</h1>\|<span id="lblIngAmount" class="ingredient-amount">.*</span>\|<span id="lblIngName" class="ingredient-name">.*</span>\|<span class="plaincharacterwrap break">.*</span>' allrecipes.com/Recipe | cat > output.txt```

By doing a recursive `grep` call with multiple regexes, we have `grep`  go through all the files in `allrecipes.com/Recipe`.
Then by piping the `grep`’s output to `cat` and redirecting it to `output.txt` we’ve compiled all the information we want.

### Patterns and Sed

Now we need to clean up all the extra HTML tags in our file.
`sed` can help us find and remove those HTML patterns.
`sed` also supports regex, and depending on the patterns, it may get a bit messy when constructing it.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep1Marked.png)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep2Marked.png)

We will need to find a pattern that matches what we’re trying to remove.

`sed -n 's/.*>\(.*\)<.*/\1/ p’`

We can see that the text we want are located in between `>` and `<` so the pattern above aimsto remove everything BUT the text in between the angle brackets.
It's a bit hard to read at first so we'll run through the command.

- the first pattern is what we will be finding; the parenthesis capture whatever is inside of `.*>` and `<.*`
- the `\1` refers to the escaped parenthesis which we will be keeping

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySedFail.png)

Oops! We weren’t able to include the directions.
Notice that there are several angle brackets that enclose the text for directions.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep2MarkedPeriod.png)

We can get the directions by including a second pattern into the sed command.

`sed -n 's/.*>\(.*\)\.<.*/\1/ p;s/.*>\(.*\)<.*/\1/ p'`

The `;` will introduce the second pattern to sed.
The `__DIRECTION__` section did not show up in the previous command because there is a difference in the pattern, more specifically the period in the directions section.
So we included a period in the pattern and had it remove the period and everything after.
The key to using `sed` is noticing and experimenting with the patterns.
Finally we get this as our output!

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySed.png)

### Resources
- [Wget manual page] (http://www.gnu.org/software/wget/manual/wget.html) for
 more information on wget.
- [Grep manual page] (http://linux.die.net/man/1/grep) for more information on grep.
- [Sed tutorial] (http://www.grymoire.com/Unix/Sed.html) for more information on sed.
- [Regular expressions tutorial] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) for more
information on regex.
