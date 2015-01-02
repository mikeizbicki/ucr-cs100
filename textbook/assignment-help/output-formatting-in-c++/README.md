#Output Formatting in C++
In this tutorial, we are going to explore some of the obscure text formatting tools that are available in C++. By the end, you will understand how to print lists into columns, print integers in multiple bases, and manipulate various attributes of your terminal's font using ANSI codes.

##iomanip
*iomanip* is a library dedicated to miscellaneous input and output manipulations. Let's get into some of them.

###setbase()
`setbase()` is a function that allows the user to pick what number system is used to output integers. Specifically, it can be set to decimal, octal, or hexadecimal. Here's an example.

code:
```
cout << setbase(16) << 26 << endl;
cout << setbase(10) << 26 << endl;
cout << setbase(8) << 26 << endl;
```
output:
```
1a
26
32
```
The above code will output the number 26 three times. Once in hexadecimal, once in decimal, and once in octal. This is a really simple function that might not be screaming usefullness, but does come in handy every now and then. For example, when dealing with bitwise shifting, it can be helpful to display the integer that is being shifted in octal or hexadecimal. Another common use is file permission manipulation. File permisions are stored in integers but they aren't really usefull unless they are represented in octal.

###setw()
`setw()` is a really usefull fuction when dealing with columns of output. In terms of a spreadsheet, `setw()` essentially sets the width of a cell. Here's an example.

code:
```
cout << setw(10) << "apple";
cout << setw(10) << "orange";
cout << setw(10) << "cherry" << endl;
cout << setw(10) << "plum";
cout << setw(10) << "pumpkin";
cout << setw(10) << "grape" << endl;
```
output:
```
     apple    orange    cherry
      plum   pumpkin     grape
```
The above code prints out a table of six elements into two rows and three columns. Each element can be up to 10 characters long. If any element is longer than 10 characters, it will cause the rest of the line to shift. `setw()` does not permenently set the new width. It is only set for the next bit of text being printed. That is why it is called before every line of output in the given code.

There are a couple more things you can do with `setw()`. First of all, you can set the justification. This is also wonderfully simple. Here's how you would left justify the last example:

code:
```
cout << left;
cout << setw(10) << "apple";
cout << setw(10) << "orange";
cout << setw(10) << "cherry" << endl;
cout << setw(10) << "plum";
cout << setw(10) << "pumpkin";
cout << setw(10) << "grape" << endl;
```
output:
```
apple     orange    cherry    
plum      pumpkin   grape     
```
All I had to do was add `cout << left;` before the text I wanted to justify. Unlike, `setw()` the justfication only has to be set once and all of the following output will adhere to it until it is set to something else. The three justification options are `left`, `right`, and `internal`. The first two are pretty obvious. `internal`, on the other hand left justifies the signs of numbers and right justifies the magnitude of number. For example, `cout setw(5) << internal << -57` could output `-  57`. According to the documentation, this is aparently usefull for accounting documents. So here's to you, accountants out there!

The last thing I want to discuss regarding `setw()` is `setfill()`. `setfill()` allows you to set what character is used in the empty spaces that appear when using `setw()`.

code:
```
cout << left << setfill('.');
cout << setw(10) << "apple";
cout << setw(10) << "orange";
cout << setw(10) << "cherry" << endl;
cout << setw(10) << "plum";
cout << setw(10) << "pumpkin";
cout << setw(10) << "grape" << endl;
```
output:
```
apple.....orange....cherry....
plum......pumpkin...grape.....
```
Pretty straight forward again, just pick a character and that's what `setw()` will fill into the empty spaces.

*iomanip* has a few more interesting functions that I'm just going to skip for now. Feel free to look them up in the C++ documentation for [*iomanip*](http://www.cplusplus.com/reference/iomanip/).

##ANSI
Now I'm going to get into using ANSI codes to further format our output. After this, you will be able to set the foreground and background colors of, underline, and bold your output.

###Colors
Using ANSI codes in C++ is pretty funky so let's start with an example.
```
cout << "\033[41;33mHello World!" << endl";
```
This code outputs "Hello World!" with yellow font and red highlighting.

The important part is `\033[41;33m`. This is how ANSI codes are formatted. First, `\033[` must always start your ANSI code. Next comes a list of numbers separated by semicolons. In this case, 41 and 33 mean red highlighting and yellow font. This list is the fun part. You can implement any of the ANSI formatting options by simply inserting the corresponding numbers into it. In this example, only two options are used, but you can add as many as you want. Finally, `m` ends the ANSI code. After the ANSI code, everything prints according to the new formatting until a new ANSI code is encountered.

Font color can be set using codes 30 - 37. Highlighting can be set using codes 40 - 47. Other formatting options, such as underlining, bolding, etc. each have a corresponding number that can be added to the list. For a full list, check out this [table](http://ascii-table.com/ansi-escape-sequences.php).

A cleaner way to incorporate ANSI codes is to store each code in a separate strings. Like this:
```
string black = "\033[30m";
string red = "\033[31m";
string green = "\033[32m";
string yellow = "\033[33m";
string blue = "\033[34m";
string purple = "\033[35m";
string teal = "\033[36m";
string white = "\033[37m";

string reset = "\033[0m";//special ANSI code that resets to the terminal's default colors

cout << black << "Hello World!" << reset << endl;
cout << red << "Hello World!" << reset << endl;
cout << green << "Hello World!" << reset << endl;
cout << yellow << "Hello World!" << reset << endl;
cout << blue << "Hello World!" << reset << endl;
cout << purple << "Hello World!" << reset << endl;
cout << teal << "Hello World!" << reset << endl;
cout << white << "Hello World!" << reset << endl;
```
This code prints "Hello World!" in every color available in ANSI. Storing the codes in string makes them much more readable. This can be done for any of the other formatting setting. Another useful option is to make functions that take strings as parameters and return the same strings with ANSI codes added.
```
string redFont(string in){
	string red = "\033[31m";
	string reset = "\033[0m";
	return red + in + reset;
}
```
The function returns `in` with the ANSI code for red added to its beginning and the ANSI code for resetting the terminal colors to its end. Once again, this concept can be extended to any of the ANSI formatting options.

###Misc Formatting
Some other attributes you can set with ANSI codes include underlining and bolding. These are just as simple to set as the colors are. The number 4 corresponds to underlining and 1 corresponds to bolding. So, to add these to colored and highlighted text, we simply add two new strings to hold the new ANSI codes, `underline` and `bold`. Here's what that will look like:
```
string red = "\033[31m";
string yellowHL = "\033[43m";

string underline = "\033[4m";
string bold = "\033[1m";

cout << underline << bold << red << yellowHL << "Hello World!" << endl";
```
This will print "Hello World!" in red, withc yellow highlighting, underlined, and bolded.

So thats a small taste of what you can do with ANSI. If you followed this tutorial and cannot get the ANSI formatting to work, it is possible you are using a console that does not support those features. I am using the default terminal that comes with Debian and everything works fine. The console that comes with Code::Blocks on Windows however, does not support ANSI. A common symptom of a console that does not support ANSI is junk characters being printed.

I've included a header file called *ANSIfontUtils.h* that contains strings for all of the ANSI codes for font coloring and highlighting, underlining, bolding, and resetting colors to terminal defaults. It also contains functions that apply those ANSI codes to strings automatically. Feel free to use it to spice up your output!

