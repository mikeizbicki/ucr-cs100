## Web scraping

This tutorial covers web-scraping with the basic Unix programs: `wget`, `grep`, and `sed`. 
By combining all of these relatively simple programs we can collect, parse, and use the data in more complicated programs.

### What is Wget?

Wget is a program that downloads the HTML code of websites.
It has several features making it a go-to program for web-scraping due to its flexibility and simplicity.

### Using Wget

To download a web page do: `wget [url]` and view the web page’s content with an editor.
Wget supports recursive downloading and use of regular expression.
- See the [wget manual page] (http://www.gnu.org/software/wget/manual/wget.html) for more information on wget.
- See the [regular expressions tutorial] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) for more information on regex.

### Web scrapping and Wget

In our example, we’ll be web scrapping for chicken recipes on [allrecipes.com] (allrecipes.com).

First we will need to download all the recipes off the site, but that’s *a lot* of recipes to
download as well as other irrelevant content.
To narrow it down to only chicken we can do specify the regex in our command.

`wget -q -r -c -np -nc --accept-regex allrecipes.com/Recipe/.*Chicken.* allrecipes.com &`

Here’s a quick rundown of the flags used above:
- `-q` (quiet) will stop the output
- `-r` (recursive) does recursive downloading
- `-c` (continue) will resume downloading if it was stopped earlier
- `-np` (no-parent) prevents downloading from parent links
- `-nc` (no-clobber) prevents the downloading of the same web file
- `--accept-regex` will only follow web pages with the specified regular expression as its url

The `&` at the end runs the program in the background, which allows multiple instances of Wget to be run to speed up the download time.
The time it takes is dependent on both the site and your connection.
It should take around an hour to download all chicken recipes from the site.
Once it is done, you will have a folder `allrecipes.com` and inside of it should contain another folder `Recipe` which contains the web content of all chicken recipes found on the site.

