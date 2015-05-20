#How to webscrape using bash script

##WGET
After finishing reading this repo, you will be able to webscrape a website to look for specific content! Also while some commands like wget can be used for windows and OS, we will focus on using linux.Some important bash commands we will be explaining to you in order to accomplish this are wget, sed, and grep. Also we will teach you how to make a script that contains those commands because no one wants to type out the commands over and over again for different websites.

First command we will go over is wget. Wget is a an important part of webscraping because the command can recursively download websites given the correct flags! There are a lot of flags for wget but we will focus on  -r, -nc, and --domains. The -r flag will allow wget to download the website recursively. This means that it will go into the link on the current page that was given and down those and the links within those link as well. If you only want to download of the the front page then don’t use -r and use -O which will download the current page and output it. This can be use with the output redirection “>” to put the content of the page into a file. The flag -nc means no clobber which is usually paired with the flag -r. This -nc flag allows us to “clobber” or overwrite pages or files that has already been downloaded before during the recursion into the same file name. --domains is use to specific wget to only download from the given website. An example is --domains bbc.com. This means that only download from bbc.com and if any links leads to outside of bbc.com will not be downloaded.
script:
First we need to make a script file which can be called anything. 
touch script.sh
and then we have to allow the script to be run with chmod
 chmod u+x script.sh
go into the script.sh and input the commands to downloads entire website. We will be using a food site to show how to get specific recipes from the site.

wget -r -nc --domains allrecipes.com allrecipes.com/Recipe
once the it finish downloading the whole website, which can take awhile, there will be a folder called allrecipe.com. We now want to see what type of food we want to eat and I’m feeling chicken so we can add this command in the script
	
	ls -R | grep “chicken”
ls -R allows use to dive through the folder recursively and grep will output everything related to chicken. Once the everything is listed you can now choose to either open the website or view the page on your computer without the html code by using sed. 
if view website
	(any web browser) firefox (recipe file name) chicken_parmesian.html
if view on computer
	cat < (recipe file name) chicken_parmesian.html | sed ‘s/<[^>]*>//g’ > filename
the sed ‘s/<[^>]*>//g’ will get rid of the html tags and “>” will put the content in the file.
After downloading our desired web pages with wget we will have to search through them with grep. Grep uses regex, regular expressions, for a more detailed tutorial on regex go to [link]. By using regex we can get the data we want. First we would need to take a look in the HTML of the webpage we downloaded. By just inspecting one or two web pages, by right-clicking on the web page and clicking on “inspect element,” we can understand how it is structured.

[picture example of looking at HTML and it’s corresponding part in the webpage]

HTML elements consists of tags which are enclosed in angle brackets. By looking the these tags and the which parts of the web page it corresponds to we can use grep on the files we’ve downloaded. However, we don’t have the time to manually use grep on each file we’ve downloaded. By piping wget and grep we make things a lot easier.

[example code of using wget  directory | grep -r directory]

##GREP
Grep searches through the files and try to match the pattern it is given. Using regex we can make some sort of template for grep to match to. Grep has several flags that can be passed in, however, for web scraping we only a few.

The -e flag allows us to specify the pattern explicitly when our pattern begins with a `-`, otherwise we can use `”` for our pattern.

By default grep interprets the pattern as a basic regex.

The -r flag allows us to traverse each and every directory we’ve included and grep those files. This can be useful if you’ve downloaded the web pages and later want to grep them.

The -H flag prints the filename of where the expression was found, which gives us an idea of where we’re extracting our data from.

The -c flag flags the number of matching lines for each input file. Useful for counting how much data we’ve gathered.

There are a bunch of other flags you can go look up on the man page, but you really only need to be familiar with regex to grep the web pages.

Going back to HTML, we can see that tags enclose the elements on the webpage, and that each have a matching beginning and ending tag. Tags such as `<div class =”NAME”>_</div>` gives us an idea of where certain data are located.  The NAME variable above gives indicates the specific label of what we’re looking for.

For example, let’s say we want to log every post on a reddit thread and find keywords. Of course, we can always use Ctrl + F, copy the data, etc, but we’re lazy people and sometimes the information we want is too general for us to target down. First let’s inspect the HTML on the webpage for a comment on a thread. When we look into the nested `<div>` tags we see
`<div class=”md”> <p> MESSAGE </p> </div>` Even thoguh the message can be about anything, every comment has the same tags. By doing `grep ‘<div class=”md”>.*?(?= </div>’` we can match the content on multiple spaces and record it for later use. The `.*?` means that anything can be in here and it can be optional. The `?=` means that it is a “positive ahead” meaning `</div>` must exist somewhere after our MESSAGE, and if it doesn’t it is not a match. Refer to https://www.autohotkey.com/docs/misc/RegEx-QuickRef.htm for more detail on regex.

Now that we’ve collected all the data we want, we would need to put it into a much cleaner and readable format using sed.

##SED
Once you download a webpage and used grep to find what you are looking for, you can use the sed command to further focus the scope to get what you are looking for. The sed (stream editor) command can be used to remove the unnecessary HTML code to get the information you want. 

To simply remove text with sed you can do this:

sed ‘s/hello//’

If the file is called file.txt and it contains:

hello world! hello

Using sed ’s/hello//’ file.txt, we will get :

 world! hello 

What this will do is that it will remove the first instance of hello in a line. To make it work for multiple lines, you can add the /g flag to the end such as:

sed ‘s/hello//g’

Using the previous example, we would get:

 world!

Now, to remove the HTML code we do not need, we can do something like this:

sed ‘s/<div>//g’

This will remove all instances of <div> from the HTML of the downloaded webpage.

Not only can we remove lines, we can also use sed to visually show where the matched string is. To do that we can use &. & represents the matched string, such as <div>.

sed ‘s/<div>/{&}/g’

This will add curly braces to all matches of <div>. So it will look something like this {<div>}.
This is especially useful when you are looking for specific words, in our case, it is for looking up specific ingredients in the recipe webpage. 

We can also use the -n flag and the /p flag to show only the lines that are being replaced. The /p flag will print out the replaced lines, however that will make sed print the replaced lines twice. What -n will do is that it will remove the duplicate printing.

Example:
sed -n ‘s/<div>//p’ 

We can also use sed like grep doing this:

sed -n ‘ /<div>/  p’

This will look for <div> and prints out lines containing it.
