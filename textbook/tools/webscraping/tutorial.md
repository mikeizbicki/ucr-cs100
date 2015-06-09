## Web scraping

This tutorial covers web-scraping with the basic Unix commands: `wget`, `grep`, and `sed`.
By combining all of these simple programs we can create a web scraper. 
In particular, we will be using a site called allrecipes.com to illustrate how to webscrape. 
We will scrape for recipes that has chicken as the main ingredient.

### Web scraping and wget

To download a webpage we use [wget] (http://www.gnu.org/software/wget/manual/wget.html) and view the downloaded content with an editor.
In our example, we will be searching for chicken recipes on [allrecipes.com] (allrecipes.com) and compiling it into a single file.
First, we need to download all of the recipes off the website, but that is *a lot* of recipes to download as well as other irrelevant content.
To narrow it down to only chicken we can specify the regular expression ([regex] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex)) in our command.

```wget -q -r -c -np -nc --accept-regex allrecipes.com/Recipe/.*Chicken.* allrecipes.com```

Here is a quick rundown of the flags used above:
- `-q` (quiet) will block the output to avoid cluttering your terminal.
- `-r` (recursive) does recursive downloading so we can traverse the entire website instead of just the given url page. 
This will allow us to look for our chicken recipes throughout the whole site.
- `-c` (continue) will resume downloading from where it was stopped earlier in the cases where the process was stopped.
- `-np` (no-parent) prevents downloading from parent links which allows us to download every file in the current path and its childs. This will be fail-safe to prevent downloading files we don’t need.
- `-nc` (no-clobber) prevents the overwriting of the same web file if it is run with the `-r` flag thus preserving the original. 
This will help us decrease the time it will take for the process to finish because it only downloads the file one time.
- `--accept-regex` will only follow web pages with the specified regular expression as its url to avoid downloading files we do not want which would save us both time and resources.

If you ran the command without the `-q` flag you should get something like this:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/wget.gif)

On some occasions, you will be unable to access or download from certain links when doing a recursive download or if you are running multiple instances of `wget`.
Some websites block tools like `wget` with a `robots.txt` which tells `wget` what it can and cannot follow.
You can have `wget` ignore `robots.txt` with the flag `--execute robots=off` to bypass the restrictions.
To run multiple instances of `wget` you may place a `&` at the end, to execute it and place it in the background and run the command again for as many times as you want.
However, running too many instances may stress out the server so it’s a good idea to run only a couple.
The time it takes to download is dependent on both the site and your connection.
You can stop the download with `Ctrl + C` to cancel it and run it again later or run it in the background with `Ctrl + Z` and `bg`.
However, if you have added a `&` you must directly kill the process via `pkill -9 wget` to stop it.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/display.png)

Once it is done, you will have a folder `allrecipes.com`.
Inside of it should contain another folder `Recipe` which contains all the web content downloaded, each in their respective folders.

### HTML and grep

After downloading hundreds to thousands of files we will need to get rid of all the clutter in the files we don’t want.
In our case, we just want anything that have to do with chicken recipes so we only want information on the name of the recipes, the ingredients needed, and the direction on how to make it.
Most of the files we have downloaded are in HTML ([HyperText Markup Language](http://en.wikipedia.org/wiki/HTML)) which is used to create web pages.
HTML consists of tags enclosed in angle brackets like `<html>` and usually come in pairs such as `<h1>` and `</h1>` with content enclosed in the tags.
We can use this to our advantage when using [grep] (http://linux.die.net/man/1/grep).
To do this, we will need to figure out which tags are associated with which part of the web page and the data the tags enclose.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy1.gif)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy2.gif)

To find which part of the web page is associated with which HTML tag simply right-click and inspect element on the web page as shown.
By looking at the tags that enclose the data you want to extract, you can get an idea of what the pattern looks like, which can be used to build a regex for `grep`.
Let’s take a look at what the file in `Yummy-Honey-Chicken-Kabobs` looks like.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/Yummy.png)

There are a few thousand lines of text in the files and we obviously do not want to look through all that to find a pattern.
Thankfully, we already know what it looks like when we inspected the web page earlier.
By looking at the tags that enclose the data you want to extract, you can get an idea of what the pattern looks like, which can be used to build a regex for `grep`.
In our case we’ll be trying to find the following tags:
- `<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name"> __NAME__ </h1>`
- `<span id="lblIngAmount" class="ingredient-amount"> __AMOUNT__ </span>`
- `<span id="lblIngName" class="ingredient-name"> __INGREDIENT__ </span>`
- `<span class="plaincharacterwrap break"> __DIRECTION__ </span>`

The names `__NAME__`, `__AMOUNT__`,  `__INGREDIENT__`, and `__DIRECTION__` are
simply placeholders for the actual values for that certain recipe.
Since we have multiple patterns we can append them together with the regex OR: `\|`.

Example:

```grep -r '<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">.*</h1>\|<span id="lblIngAmount" class="ingredient-amount">.*</span>\|<span id="lblIngName" class="ingredient-name">.*</span>\|<span class="plaincharacterwrap break">.*</span>' allrecipes.com/Recipe | cat > output.txt```

By doing a recursive `grep` call with multiple regexes as shown in the example above, we have `grep`  go through all the files in `allrecipes.com/Recipe`.
Then by piping `grep`’s output to `cat` and redirecting it to `output.txt` we’ve compiled all the information we want into the file.

### Patterns and sed

Now we need to clean up all the extra HTML tags in our file.
The command [sed] (http://www.grymoire.com/Unix/Sed.html) can help us find and remove those HTML patterns.
`sed` also supports regex, and depending on the patterns, it may get a bit messy when constructing it.

NOTE: The green highlighting indicates the information we want, while the yellow highlighting indicates the HTML code we want to remove in the file located in `Yummy-Honey-Chicken-Kabobs`.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep1Marked.png)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep2Marked.png)

We will need to find a pattern that matches what we are trying to remove.

`sed -n 's/.*>\(.*\)<.*/\1/ p’ input.txt | cat > output.txt`

The texts we want are located in between `>` and `<` so the pattern above aims to remove everything BUT the texts in between the angle brackets which are enclosed in parenthesis.
It's a bit hard to read at first so we will run through the command.

- the first pattern is what we will be finding; the parenthesis capture whatever is inside of `.*>` and `<.*`
- the `\1` refers to the escaped parenthesis which we will be keeping

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySedFail.png)

Oops! We were not able to include the directions.
Notice that there are several angle brackets that enclose the text for directions.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep2MarkedPeriod.png)

We can get the directions by including a second pattern into the sed command.

`sed -n 's/.*>\(.*\)<.*/\1/ p;s/.*>\(.*\)\.<.*/\1/ p’ input.txt | cat > output.txt`

The `;` will introduce the second pattern to sed.
The `__DIRECTION__` section did not show up in the previous command because there is a difference in the pattern, more specifically, it is the period at the end of each sentence in the directions section, which can be seen in the picture above in red circles.
So we included a period in the second pattern and had it remove the period and everything after it.
The key to using `sed` is noticing and experimenting with various patterns.
Finally we get this as our output!

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySed.png)

We can now feed this data to another program for other applications.

### Resources
- [Wget manual page] (http://www.gnu.org/software/wget/manual/wget.html) for
 more information on wget.
- [Grep manual page] (http://linux.die.net/man/1/grep) for more information on grep.
- [Sed tutorial] (http://www.grymoire.com/Unix/Sed.html) for more information on sed.
- [Regular expressions tutorial] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) for more
information on regex.





