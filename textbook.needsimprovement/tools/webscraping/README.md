## Web scraping

This tutorial covers web scraping with the basic Unix commands: `wget`, `grep`, and `sed`.
In particular, we will be using a site called [allrecipes] (http://allrecipes.com/?prop24=PN_Logo) to illustrate how to web scrape for recipes with chicken as the main ingredient, and then put all the ingredients and directions of the recipe into individual files in `Chicken_Recipes`.

### Web scraping and wget

To download a webpage we use [wget] (http://www.gnu.org/software/wget/manual/wget.html).
First, we want to download the recipes on the website, but we do not want to download irrelevant recipes.
To narrow it down to only chicken recipes, we can specify a [regular expression] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex) in our command.
In the command shown below, `wget` downloads from links that start with `allrecipes.com/Recipe/` and with zero or more characters before and after `Chicken` as indicated by the `.*`.

```wget  -r -c -np -nc --accept-regex allrecipes.com/Recipe/.*Chicken.* allrecipes.com```

Here is a quick rundown of the flags used above:


| Flag              | Description                                                                                                                                                                   |
|-------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `r` (recursive)   | This flag lets `wget` download the current web page and then continues to download any other links on the web page, stopping  when there are no more links to retrieve.             |
| `c` (continue)    | This flag tells `wget` to resume the download from where it was stopped earlier in case the process was stopped.                                |
|  `np` (no parent) | This flag prevents the download of subsequent links that lead to a directory other than the starting directory.                                                               |
| `nc` (no clobber) | This flag prevents `wget` from re-downloading the same file and instead preserves the original if another copy is found on the website.                                       |
| `--accept-regex`  | This flag tells `wget` to download web pages with the specified regular expression as its URL to avoid files we do not want, which saves us both time and resources. |




Running the command specified above will display a download process in the terminal:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/wget.gif)

Websites have a file called [robot.txt] (http://www.gnu.org/software/wget/manual/html_node/Robot-Exclusion.html), which presents a policy that `wget`, and other similar tools, must follow. 
This may prevent `wget` from accessing or downloading from certain links when doing a recursive download.
You can ignore the `robots.txt` by passing in the flag `--execute robots=off` with `wget` to bypass the restrictions.

To run multiple instances of `wget` you may place a `&` at the end, which executes `wget` and places `wget` to run in the background. 
You can execute the command again to run another instance of `wget`, however, running too many instances may stress out the server so it is a good idea to only run a couple.
The time `wget` takes to download is dependent on both the site and your connection.
You can stop the download with `Ctrl + C` to cancel `wget` or  you can run `wget` in the background with `Ctrl + Z` and `bg`.
However, if you add a `&` you must directly kill the process via `pkill -9 wget` to stop it.

Once the download is done, you will have a folder called `allrecipes.com`.
Inside of this folder, it contains another folder named `Recipe`, which has all of the downloaded web content in each of their respective folders as seen here:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/display.png)

### HTML and grep

After downloading all of the files, we need to get rid of the extra text in the files we do not want.
The files we have downloaded contain [HTML](http://en.wikipedia.org/wiki/HTML) code as seen in the `Yummy-Honey-Chicken-Kabobs` recipe file below:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/Yummy.png)

We want a readable text file with information on the name of the recipe, ingredients, and directions on how to make the recipe from all of the downloaded files.

We use [grep] (http://linux.die.net/man/1/grep), a tool used to search for text in files, to traverse through the `allrecipes.com` folder to find the chicken recipe files and output the information we want into a separate text file.
For our purposes, we use `grep` to search for patterns in the HTML code.

HTML consists of tags enclosed in angle brackets like `<html>` and usually come in pairs such as `<h1>` and `</h1>` with text enclosed in the tags.
We can use this to our advantage when using `grep`.
To search for the patterns, we first need to figure out which tags are associated with which parts of the web page and what text the tags enclose.

In the following two gif, we right-click on the web page and click on inspect element to find the HTML code that contain the recipe name, list of ingredients, and the directions.


![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy1.gif)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/yummy2.gif)

In the first gif, we see that the highlighted HTML code in the right window corresponds to the text being highlighted in the web page, which is related to the recipe name. 
In the second gif, we see similar highlighting, but this time it is related to the recipe ingredients.

This code contains the recipe name and ingredients, which we got by inspecting the web page’s HTML code:
- `<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">Yummy Honey Chicken Kabobs</h1>`
- `<span id="lblIngAmount" class="ingredient-amount">1/4 cup</span>`
- `<span id="lblIngName" class="ingredient-name">vegetable oil</span>`

The directions are also formatted similarly to the recipe name and ingredients.
If we take a look at other recipes they have the same tags and the only difference is the text enclosed by the tags.
We can use these tags to construct regular expressions for `grep` to get the recipe names, ingredients, and directions.

Our general pattern in the HTML code looks like this:
- `<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name"> __NAME__ </h1>`
- `<span id="lblIngAmount" class="ingredient-amount"> __AMOUNT__ </span>`
- `<span id="lblIngName" class="ingredient-name"> __INGREDIENT__ </span>`
- `<span class="plaincharacterwrap break"> __DIRECTION__ </span>`

NOTE: The names `__NAME__`, `__AMOUNT__`,  `__INGREDIENT__`, and `__DIRECTION__` are
placeholders for the actual information of that specific recipe.

Here is the command we used to find the lines we want in the file.

```
grep -r '<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">.*</h1>
\|<span id="lblIngAmount" class="ingredient-amount">.*</span>
\|<span id="lblIngName" class="ingredient-name">.*</span>
\|<span class="plaincharacterwrap break">.*</span>' allrecipes.com/Recipe > output.txt

```

Since we have multiple patterns we can append them together with the regular expression OR: `\|`.

By doing a recursive `grep` call with regular expressions as shown in the example above, `grep` goes through all the files in `allrecipes.com/Recipe` to look for the specified regular expressions.
Then, by redirecting the output of `grep` to `output.txt`, we successfully gathered the information we want.

Here is what the output looks like:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep1.jpg)

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummyGrep2.jpg)

### Patterns and sed

After using `grep` to output the lines containing the text we want, we now want to delete all the HTML tags in the file.
This can be done with the help of [sed] (http://www.grymoire.com/Unix/Sed.html), a stream editor for modifying text, which also supports regular expressions.
`sed` also supports regular expressions so we can construct a pattern similar to the one used in `grep` to delete the HTML tags.

In the picture below, we highlighted the information we want with part of the HTML tags enclosing it.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/HighlightedGrep_fix.png)

The information we want is located between `>` and `<` so we want to remove everything except what is between `>` and `<`.
To do that, we construct a regular expression that matches the HTML tags we want to remove.

```sed -n 's/.*>\(.*\)<.*/\1/ p' input.txt > output.txt```

The command above is hard to read at first, so we explain it in detail.

We are looking for any information that is between `>` and `<`, in which `>` and `<` represent the HTML tags.
Then we want to keep all of the information in the escaped parentheses, in which the parentheses are represented by the `\1`, and the information we want are the recipe names and ingredients.
Since we just want the information we are looking for, we use the `-n` flag along with the `/ p` to print only the replaced lines.

After using `sed` on the input file, the output file looks like this.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySedFail.png)

Unfortunately, the directions are excluded from the output file.
Looking back at the input file, we notice that there is a period at the end of each sentence for the directions as shown by the red circles below.

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/RedCircle.png)

This is why the directions are not included in the output file.
We can include the directions by introducing a second pattern into the `sed` command.

`sed -n 's/.*>\(.*\)<.*/\1/ p;s/.*>\(.*\)\.<.*/\1/ p' input.txt > output.txt`

The `;` introduces a second pattern to `sed`.
The first part `sed -n 's/.*>\(.*\)<.*/\1/ p'` is for the recipe name and the list of ingredients and the second part `s/.*>\(.*\)\.<.*/\1/ p'` is for the directions.
We included a period in the second part of `sed` to look for the period at the end of each direction sentence and then remove the period and everything after.
The key to using `sed` is noticing and experimenting with various patterns.

Our final output looks like this:

![my image](https://raw.githubusercontent.com/ktang012/hw4/master/pictures/YummySed.png)

###Tying everything together with a script

Although we finished getting the recipes, the output file is very unorganized.  
We want to be able to see the name of the recipe, the ingredients, and directions very clearly when reading our output file.  
We also do not want to put all of the recipes into a single file, so we are going to give each recipe their own text files which contains the name of the recipe, the ingredients, and the directions.
To do this, we make a bash script. 

This is the format we use to clearly show what our output file is showing: 

```
--------------------------------------------------  
Name 
-------------------------------------------------- 
<NAME> 
-------------------------------------------------- 
Ingredients
--------------------------------------------------  
<AMOUNT OF INGREDIENT NEEDED> 
<INGREDIENT NAME>  
--------------------------------------------------  
Directions 
-------------------------------------------------- 
<DIRECTION> 
--------------------------------------------------

```
First, we make a script file called `recipe_script.sh`.
Then, we create a directory that holds all of our chicken recipes if the directory did not exist before by writing this to the script:

```if [ ! -d Chicken_Recipes ] then mkdir Chicken_Recipes fi``` 

After that, we want to make a for-loop to iterate through all of the recipes and make a file for each one, like this: 

```for i in $(ls allrecipes.com/Recipe); do```

`i` is a folder in the directory `allrecipes.com/Recipe` and, in our case, the folders are named after a recipe.

Then, to automate things, we declare an environment variable called `recipe` for the files containing the HTML code.

```recipe=$(ls allrecipes.com/Recipe/$i | grep "Detail.*" | head -1)```

Now, inside the for-loop, we do the following:

1. `grep` the name.
2. Pipe the result to `sed` to delete the HTML code.
3. Append the result to a file.
4. Repeat steps 1 to 3, but for ingredients and directions. 

To organize the information to the format we want, we append headers and lines to separate the name, ingredients, and directions.

```
    recipe=$(ls allrecipes.com/Recipe/$i | grep "Detail.*" | head -1)
    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"
    echo "Name" >> "Chicken_Recipes/$i.txt"
    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"

    grep '<h1 id="itemTitle" class="plaincharacterwrap fn" itemprop="name">.*</h1>' "allrecipes.com/Recipe/$i/$recipe" |
        sed -n 's/.*>\(.*\)\.<.*/\1/ p;s/.*>\(.*\)<.*/\1/ p' >> "Chicken_Recipes/$i.txt"

    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"
    echo "Ingredients" >> "Chicken_Recipes/$i.txt"
    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"

    grep '<span id="lblIngAmount" class="ingredient-amount">.*</span>\|<span id="lblIngName" class="ingredient-name">.*</span>' \
        "allrecipes.com/Recipe/$i/$recipe" |
        sed -n 's/.*>\(.*\)\.<.*/\1/ p;s/.*>\(.*\)<.*/\1/ p' >> "Chicken_Recipes/$i.txt"

    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"
    echo "Directions" >> "Chicken_Recipes/$i.txt"
    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"

    grep '<span class="plaincharacterwrap break">.*</span>' "allrecipes.com/Recipe/$i/$recipe" |
        sed -n 's/.*>\(.*\)\.<.*/\1/ p;s/.*>\(.*\)<.*/\1/ p' >> "Chicken_Recipes/$i.txt"

    echo "--------------------------------------------------" >> "Chicken_Recipes/$i.txt"
    done

```

And voila, our script is finished.

Now that we finished writing the script, you can run the script with the command `sh recipe_script.sh`. 
Once the script is done running, the `Chicken_Recipes` folder contains all of the the recipe files in the correct format.
We uploaded our [script](./script/create_recipes.sh) and the [result](./Chicken_Recipes)  (WARNING: Contains a large amount of files. Open at your own risk) of `sh recipe_script.sh` for you to compare.

We now have our very own offline cookbook!
We can also use the information we web scrape as an input file for programs like [reciperoulette] (http://www.reciperoulette.tv/) to use.

