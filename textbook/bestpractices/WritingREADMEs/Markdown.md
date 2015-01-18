Markdown Quick Reference Guide
===
This is a quick reference guide for various Markdown syntax that I found useful throughout cs100. Please enjoy!

Flavors
---
There are a variety of Markdown "flavors". These "flavors" are different implementations of Markdown with varying syntax. Entities such as [Github](https://help.github.com/articles/github-flavored-markdown/), [Reddit](http://www.reddit.com/wiki/commenting), and [Stack Exchange](http://stackoverflow.com/editing-help) have their own flavors of Markdown. Recently there has been a push for a standard implementation of Markdown, you can read more about that [here](http://blog.codinghorror.com/standard-flavored-markdown/), but for the time being there are multiple implementations that must be recognized. The following tutorial is guaranteed to interpret correctly as Github flavored Markdown. But, the same results cannot be guaranteed when interpreted as any other flavor of Markdown.

Creating a Markdown Document
---
Markdown files can be created using the ```.md``` file extension.

Example usage:

    touch README.md

Headings
---
Prefix ```#``` to what you want your heading to be, the more ```#``` prefixed the smaller the heading will be. Headers can also be established by using ```=``` or ```-``` underneath the header.

Example usage:

    # Header one
    ## Header two
    ### Header three
    #### Header four

    Header one
    ====
    Header two
    ---

Italics, Bold, and Crossed out.
---
Specific words or whole sentences can be italicized by wrapping it in ```*``` or ```_```, bolded by wrapping it in ```**``` or ```__```, or crossed out by wrapping it in ```~~```. These effects can be combined.

Example usage:

    Those words are *italicized*.
    Those words are **bolded**.
    Those words are **_bolded and italicized_**.
    I think ~~your~~ you're bad at grammar.
    
Result:
Those words are *italicized*.
Those words are **bolded**.
Those words are **_bolded and italicized_**.
I think ~~your~~ you're bad at grammar.
    
Lists and nested lists
---
Lists can either be ordered or unordered. To create an ordered list begin the list item with ```n.``` where ```n``` is the number of the list item. To create an unordered list begin each item with an ```*```. Lists can be nested by using white space to indent the nested items.

Example usage:
    
    1. Lather
    2. Rinse
    3. Repeat
    
    * Milk
    * Eggs
    * Cheese

    1. Lather
        * with milk
    2. Rinse
        * the eggs
    3. Repeat
        * and eat the cheeses
        
Result:

1. Lather
    * with milk
2. Rinse
    * the eggs
3. Repeat
    * and eat the cheeses

Block Quotes
---
Block quotes can be used by appending ```>``` to anything that should be within the block quote.

Example usage:

    > This is inside of the quote.
    > And so is this.
    > Also this.

Code
---
To insert code into your Markdown document surround the code with at least 1 `` ` `` on each side. Being able to use varying amounts of ``` ` ``` means that  ``` ` ``` can be used to escape ``` ` ```. You can indicate syntax highlighting specific to a language by adding the name of the language after the opening `` ` ``, for this to work you must use at least 3 `` ` ``. 

Example usage:
    
    `` `These `'s won't be interpreted!` ``

    ``cout << "Hello, world!" << endl;``
    
    ```python
    x = "Hello, world!"
    print x
    ```
    
Links and Images
---
Links can be embedded through the syntax ```[word or words](the link)``` and images can be inserted with the syntax ```![alt text](url or path of image)```.

Example usage:

    [This link will take you to a website!](https://google.com)
    
    Only the last word will take you to a [website](https://google.com)
    
    ![alt text](http://upload.wikimedia.org/wikipedia/en/c/c8/Alan_Turing_photo.jpg)

Result from ```Only the last word will take you to a [website](https://google.com)```:

Only the last word will take you to a [website](https://google.com)

Escaping
---
A character can be escaped by appending ```\``` to it.

Example usage:
    
    \` This will not appear as code! \`

HTML
---
* Raw HTML can be placed directly into your Markdown document.

Example usage:

    <table>
        <tr>
            <th>Dogs</th>
            <th>Cats</th>
        </tr>
        <tr>
            <td>not enough</td>
            <td>too many</td>
        </tr>
    </table>
    
Result:

<table>
    <tr>
        <th>Dogs</th>
        <th>Cats</th>
    </tr>
    <tr>
        <td>not enough</td>
        <td>too many</td>
    </tr>
</table>

