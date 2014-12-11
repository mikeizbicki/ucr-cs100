Markdown Quick Reference Guide
===
This is a quick reference guide for various Markdown syntax that I found useful through out cs100. Please enjoy!

Flavors
---
* There are a variety of Markdown "flavors". Which, put simply, are different implementations of Markdown. 
* Recently there has been a push for a standard implementation of Markdown, but for the time being there are multiple          implementations that must be recognized.
* The following tutorial is guaranteed to interpret correctly as Github flavored Markdown. But, the same results can not be    guaranteed when interpreted as any other flavor of Markdown.

Creating a Markdown Document
---
* To create a Markdown document you would create it the same way you would any other file but the file extension would be ```.md```

Example usage:

    touch README.md

Headings
---
* Prefix ```#``` to what you want your heading to be, the more ```#``` prefixed the smaller the heading will be.
* Headers can also be established by using ```=``` or ```-``` underneath the header.

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
* Specific words or whole sentences can be italicized by wrapping it in ```*``` or ```_```.
* Specific words or whole sentences can be bolded by wrapping it in ```**``` or ```__```.
* Specific words or whole sentences can be crossed out by wrapping it in ```~~```. 
* These effects can be combined.

Example usage:

    Those words are *italicized*.
    Those words are **bolded**.
    Those words are **_bolded and italicized_**.
    I think ~~your~~ you're bad at grammar.
Lists and nested lists
---
* Lists can either be ordered or unordered.
* To create an ordered list begin the list item with ```n.``` where ```n``` is the number of the list item.
* To create an unordered list begin each item with an ```*```.
* Lists can be nested by using white space to indent the nested items.

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

Block Quotes
---
* Block quotes can be used by appending ```>``` to anything that should be within the block quote.

Example usage:

    > This is inside of the quote.
    > And so is this.
    > Also this.

Code
---
* To insert code into your Markdown document surround the code with at least 1 `` ` `` on each side.
* You can indicate syntax highlighting specific to a language by adding the name of the language after the opening `` ` ``, for this to work you must use at least 3 `` ` ``.
* Being able to use varying amounts of ``` ` ``` means that  ``` ` ``` can be used to escape ``` ` ```.

Example usage:
    
    `` `These `'s won't be interpreted!` ``

    ``cout << "Hello, world!" << endl;``
    
    ```python
    x = "Hello, world!"
    print x
    ```
    
Links and Images
---
* Links can be embedded through the syntax ```[word or words](the link)```.
* Images can be inserted with the syntax ```![alt text](url or path of image)```.

Example usage:

    [This link will take you to a website!](https://google.com)
    
    Only the last word will take you to a [website](https://google.com)
    
    ![alt text](http://upload.wikimedia.org/wikipedia/en/c/c8/Alan_Turing_photo.jpg)

Escaping
---
* A set amount of predetermined characters can be escaped by adding a ```\``` before it.
* Those characters are as follows: `\`, `` ` ``, `*`, `_`, `{}`, `[]`, `()`, `#`, `>`, `+`, `-`, `.`, and `!`.

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
