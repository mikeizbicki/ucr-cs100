#The Boost Library Tokenizer

A tokenizer extracts a sequence of meaningful substrings from a string.
These substrings are called tokens.
Tokenizing makes life easier when you want to break up a string.
For example, you can tokenize the string `Get thee to a nunnery`, which will be broken up into the tokens: `Get`, `thee`, `to`, `a`, and `nunnery`.

The Boost Tokenizer package uses a `tokenizer` class to tokenize the string that is passed in. 
The `tokenizer` class takes in several template parameters (which you can see in the [Boost Library Documentation](http://www.boost.org/doc/libs/1_57_0/libs/tokenizer/index.html)).
One of these template parameters is a `TokenizerFunc` class.

The `TokenizerFunc` template parameter is a class that determines how a string is broken up into tokens.
The tokenizer class uses four `TokenizerFunction` models, or types: `char_separator`, `escaped_list_separator`, `offset_separator`, and `char_delimiter_separator`.

##How do we use the boost tokenizer?

Let's look at the code from [ex1.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_1.cpp).

The first thing we'll have to do is include the boost tokenizer library and use the boost namespace.

```
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;
```

Then we create the tokenizer object and use iterators to traverse through the tokens.

```
int main() {
    string str = "Don't panic, too much. 12,34";
    tokenizer<> mytok(str);
    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << *it << endl;
    return 0;
}
```

Notice that `mytok` does not have any template parameters.
This means that the default `TokenizerFunc` model, `char_delimiters_separator`, is used.

So now let's compile and run this.

```
$ g++ -std=c++11 ex_1.cpp -o ex_1
$ ./ex_1
Don
t
panic
too
much
12
34
```

However, the way this tokenizer is parsing isn't particularly useful.
The `char_delimiters_separator` class is a ***deprecated*** class, which means that it is dangerous to use or that there is a better alternative.
A deprecated class is going to be deleted from the library, so you should *never* use the `char_delimiters_separator` class.
Instead, you should use the `char_separator` class.
With the `char_separator` `TokenizerFunc`, we can control how the boost tokenizer parses by defining something which is known as a delimiter.

A ***delimiter*** is a sequence of one or more characters that separate tokens, and a tokenizer looks at what delimiters are passed in so that it can know where to separate the tokens.
So for this example, we can say that the default delimiters are white space and all non-letter/number characters.

To explain in detail how this string got parsed, it should be noted that `tokenizer<>` parses by characters.
So this tokenizer will go through each character in the string and it will check to see if it is in the delimiter set.
Once it finds a match, the tokenizer will know that everything up until that character is a token so `Don` becomes a token since it finds `'`, which is a non-letter/number character.
It will then move on to creating the next token and once it finds the space after `t`, it creates the token `t`.
And so this continues on until the tokenizer has gone through the whole string.

###Defining our own delimiters with `char_separator`

It would be better to be able to define our own delimiters, so let's work with the code from [ex_2.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_2.cpp).

```
string str = "Thou&&&&art&as    fat&as&&butter";
char_separator<char> delim("&");
tokenizer< char_separator<char> > mytok(str, delim);
```

The `char_separator<char>` is one of the models of the boost tokenizer library and declaring tokenizer with `char_separator<char>` lets boost know that we're going to use our own delimiters.
Notice how the tokenizer object now has an extra parameter, `delim`, which will be our delimiter set.

In this particular example, our delimiter set contains only `&`, so therefore our tokens will be separated only by this character.

So let's see what happens when we compile and run this code.

```
$ g++ -std=c++11 ex_2.cpp -o ex_2
$ ./ex_2
Original string: Thou&&&&art&as    fat&as&&butter
token: Thou
token: art
token: as    fat
token: as
token: butter
```

Notice how even though there were multiple `&`'s, all of them were not outputted.
But now this doesn't look like something useful since white space isn't part of the delimiter set anymore.

###Multiple characters in our delimiter

The `char_separator<char>` model of boost tokenizer is able to take in multiple characters.
So let's change our delimiter set from the previous example, [ex_2.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_2.cpp), to this:

`char_separator<char> delim(" &");`

Let's compile the code with this change and then execute it:

```
$ g++ -std=c++11 ex_2.cpp -o ex_2
$ ./ex_2
Original string: Thou&&&&art&as    fat&as&&butter
token: Thou
token: art
token: as
token: fat
token: as
token: butter
```

Now this looks better, but keep in mind that this delimiter set does not contain *all* white space.
Try looking up [ASCII character codes](http://www.petefreitag.com/cheatsheets/ascii-codes/) for other types of white space (and other miscellaneous characters that you might need).

###Repeated characters in our delimiter

What if our delimiter set contains reapeated characters?
We explained earlier how a tokenizer will match the text with the delimiters to know where to separate tokens, and because this boost tokenizer deals with only characters, the tokenizer will look in the set and match a character to a character.
So if a character showed up one time in the set, then the tokenizer will know that this marks the separation of tokens.
Any other subsequent appearances of this character won't mean anything since the tokenizer would have already parsed the token after seeing the first one.
This is why we keep referring to the `char_separator<char>` as the delimiter set, since it acts like a set.

So looking at [ex_3.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_3.cpp), we have the string and our delimiter set as:

```
string str = "ls dir || cat file | tr a-z A-Z";
char_separator<char> delim(" ||");
tokenizer< char_separator<char> > mytok(str, delim);
```

If you didn't want to include the pipe `|` in your delimiter, having it contain `||` will *not* be recognized as something distinct to look for in parsing.
We'll output our tokens this time with spaces in between.
So let's compile and run the program to see what we will get:

```
$ g++ -std=c++11 ex_3.cpp -o ex_3 && ./ex_3
ls dir cat file tr a-z A-Z
```

###Default delimiters

What happens though if we didn't put anything into our delimiter set?
The default delimiters for `char_separator<char>` model will contain only white space.
Also, the non-letter/number characters are each treated as a token.
Notice that this is different from `tokenizer<>`.


Using [ex_4.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_4.cpp), we have:

```
string str = "12*34 I, declare a&&thumb    !war";
char_separator<char> delim;
tokenizer< char_separator<char> > mytok(str, delim);
```

where we didn't put anything into our set.
Similarly, we could also opt to not pass in `delim` into our tokenizer like this,

```
tokenizer< char_separator<char> > mytok(str);
```

and achieve the same results.
Let's compile and run ex_4.cpp to see how the tokens will look, where each token will be separated by a space:

```
$ g++ -std=c++11 ex_4.cpp -o ex_4
$ ./ex_4
12 * 34 I, declare a & & thumb ! war
```

##Going beyond with `char_separator`

Here are the basics of making a tokenizer with your own delimiters so far:

 - Create your own delimiter:

  `char_separator<char> delim(DELIMITERS);`

 - Make a tokenizer object:

  `tokenizer< char_separator<char> > mytok(str, delim);`

 - Your delimiter set can take in multiple characters as delimiters.
 - Repeated characters do not make a difference in parsing.

But it might be useful to know that `char_separator<char>` has options for outputting delimiters and empty tokens.
This is where boost tokenizer really differentiates from the `strtok` function since it can do neither of these.

**Note:** If you're unfamiliar with `strtok`, check out this [tutorial](https://github.com/mikeizbicki/ucr-cs100/tree/2015winter/textbook/assignment-help/strtok).

###Kept delimiters

So far, we have been working with the *dropped delimiters* of `char_separator<char>`, which are the delimiters that do not become tokens.
`char_separator<char>` actually has another parameter to specify the *kept delimiters*, which will be the delimiters that do become tokens.
This will look like:

`char_separator<char> delim(DROPPED_DELIM, KEPT_DELIM);`

Looking at [ex_5.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_5.cpp), we have:

```
string str = "I;m test^ing this || out;";
char_separator<char> delim("^| ", ";");
```

which will separate tokens by the delimiters `^| ;` and will also make `;` a token.
The rest of the code in [ex_5.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_5.cpp) will output our tokens in between `( )` to help clarify which are the tokens.

```
cout << "Original string: " << str << endl;
tokenizer< char_separator<char> > mytok(str, delim);
for(auto it = mytok.begin(); it != mytok.end(); ++it)
    cout << "(" << *it << ")" << " ";
```
```
$ g++ -std=c++11 ex_5.cpp -o ex_5
$ ./ex_5
Original string: I;m test^ing this || out;
(I) (;) (m) (test) (ing) (this) (out) (;)
```

###Empty tokens

Recall that when a tokenizer goes through a string it will separate tokens by the delimiters.
But what if there are multiple delimiters right next to each other?

Say we have this string `c&&ar` where our delimiter is `&`.
When the tokenizer reaches the first `&`, it will know that `c` is a token.
Then it will start working on the next token, but it will find another `&` right after and it will think, that's the end of the token.
But there was nothing that was actually put into this token and thus we have an **empty token**.

Tokenizers such as `strtok` will not output these empty tokens but maybe it might be useful to know where these empty tokens are, so the boost tokenizer gives us this option.
In order to do this, `keep_empty_tokens` must be passed in as the third paramter for `char_separator<char>.`
Let's use the previous example, ex_5.cpp, and change our delimiter to:

`char_separator<char> delim("^| ", ";", keep_empty_tokens);`

Compiling and running with this change will give us:

```
Original string: I;m test^ing this || out;
(I) (;) (m) (test) (ing) (this) () () () (out) (;) ()
```
where the parentheses with nothing in between them are our empty tokens.

Now that we know how to use the `char_separator`, let's move on to the `escaped_list_separator` model. 

###Using the `escaped_list_separator` model

The `escaped_list_separator` model, like the `char_separator` model, tokenizes a string using delimiters.

In the `escaped_list_separator model, tokens are separated by delimiters, which we can see using [ex_6](src/ex_6.cpp):

```
string str = ",Flappy;Bird:All good,";
escaped_list_separator<char> sep("", ",;:", "");
tokenizer<escaped_list_separator<char>> mytok(str, sep);
```

The delimiter set is contained in the string of the second parameter of the `escaped_list_separator`.
In this example, we have set the delimiter set to include `,`, `;`, and `:`. 
For now, the other two parameters do not affect the inputted string.

Now, let's compile this and see what gets outputted.

```
$ g++ -std=c++11 ex_6.cpp -o ex_6
$ ./ex_6
Original String: ,Flappy;Bird:All good,
Token: 
Token: Flappy
Token: Bird
Token: All good
Token: 
```

Just like with the `char_separator` model, tokens are separated by delimiters and we can choose what our delimiters are.
However, we can not choose whether to keep or drop delimiters.
Also, notice that empty tokens are not discarded.

####Quote charaters
One important feature of the `escaped_list_separator` model is the quote character.
Quote characters make it so that delimiters are not interpreted.
If you want a delimiter character to be included in the token, you should put quote characters around the substring containing the delimiter character.
Like for delimiters, you can choose a set of quote characters to use.

To see the quote character in use, let's look at [ex_7](src/ex_7.cpp).

```
string str = "Whiskers,Cat,\"Whiskers is very, very healthy\"\nBuddy,Dog,'Buddy is healthy & strong'";
escaped_list_separator<char> sep("", ",&\n", "\"'");
tokenizer<escaped_list_separator<char>> mytok(str, sep);
```

The third parameter contains the set of quote characters.
In this case, the `"` and `'` characters are the quote characters.
Also, the delimiter set contains the `,`, `&`, and `\n` characters.

Let's see what happens when we compile and run it.

```
$ g++ -std=c++11 ex_7.cpp -o ex_7
$ ./ex_7
Original String: Whiskers,Cat,"Whiskers is very, very healthy"
Buddy,Dog,'Buddy is healthy & strong'
Token: Whiskers
Token: Cat
Token: Whiskers is very, very healthy
Token: Buddy
Token: Dog
Token: Buddy is healthy & strong
```

As you can see, the delimiters outside of the quote characters behave as they normally do.
However, the delimiters `,` and `&` are inside the quote characters, so they are not interpreted as delimiters.

####Escape characters
Another important feature of the `escaped_list_separator` model is the escape character.
Like other escape characters, the Boost Tokenizer's escape character will result in alternative interepretations of certain characters.
There are three ways to use Boost Tokenizer's escape character:
1. If you have the escape character before a quote character, the quote character will be printed out rather than being interpreted as a quote character.
2. If you have the escape character before an `n`, a newline will be printed.
3. If you have the escape character before another escape character, the escape character will be printed. 
Like the quote character and the delimiter character, you can choose the characters inside the escape character set.

To understand the how the escape character works, let's look at [ex_8](src/ex_8.cpp).

```
string str = "Whiskers,Cat,\\\"Whiskers is very, very healthy\\\"\\nBuddy,Dog,'Buddy is healthy\\\\strong'";
escaped_list_separator<char> sep("\\", ",\n", "\"");
tokenizer<escaped_list_separator<char>> mytok(str, sep);
```

In this example, we have `,` and `\n` as delimiters, `"` as the quote character, and `\` as the escape character.

Let's see what we get when we compile and run it.

```
$ g++ -std=c++11 ex_8.cpp -o ex_8
$ ./ex_8
Original String: Whiskers,Cat,\"Whiskers is very, very healthy\"\nBuddy,Dog,'Buddy is healthy\\strong'
Token: Whiskers
Token: Cat
Token: "Whiskers is very
Token:  very healthy"
Buddy
Token: Dog
Token: 'Buddy is healthy\strong'
```
As you can see, there are several instances of the escape character being used.

Firstly, the quote character is escaped twice. 
Since `\"` is in the original string, the `"` character is printed rather than being interpreted by the tokenizer.

Secondly, `\n` is used to escape the `n` character, causing a newline to be printed.
Notice that when `n` is escaped, it is not considered a delimiter, even though `\n` is in the set of delimiters.
This is because `\` and `n` are each considered a separate character.
However, when looking for delimiters, the Boost Tokenizer is looking for the newline character.

Lastly, the escape character is used to escape itself. 
`\\` in the original string results in the `\` character being printed.

###Default `escaped_list_separator`
What happens if you do not put any arguments into `escaped_list_separator`? 
The default characters for the escape character, the delimiter character, and the quote character are `\`, `,`, and `"`, respectively.

Let's look at the default `escaped_list_separator` in [ex_9](src/ex_9.cpp).

```
string str = "\\\"Octocat\\\",\"Half cat, half octupus\",Github's official mascot";
escaped_list_separator<char> sep;
tokenizer<escaped_list_separator<char>> mytok(str, sep);
```

As you can see, the `escaped_list_separator` does not have any arguments, so it is using the default arguments.

Let's see what we get when we compile and run this example.

```
$ g++ -std=c++11 ex_9.cpp -o ex_9
$ ./ex_9
Original String: \"Octocat\","Half cat, half octupus",Github's official mascot
Token: "Octocat"
Token: Half cat, half octupus
Token: Github's official mascot
```

First, let's look at `\`, the escape character.
In the original string, there are two places where `\` is used.
Both cases have the escape character before a quote.
In those cases, instead of the `"` character being interpreted, it is printed.

Now let's look at the delimiter character.
As you can see, the commas in the original string break it up into the tokens.

Finally, we can see that the `,` between two `"` characters is is not interpreted as a delimiter.

Now that we know how to use the `escaped_list_separator` model, let's move on to the `offset_separator` model.

###Using the `offset_separator` model

Unlike the other three `TokenizerFunc` models, the `offset_separator` model does *not* create its tokens based on delimiters.
Instead, it separates a string into substrings using a sequence of integer lengths.
The sequence of integer lengths is stored inside a data structure, such as an array or a vector.
Then, two addresses or iterators are passed into the `offset_separator` to decide which integers to use.
The first address or iterator is the integer sequence we want to start at.
The second address or iterator is one spot past the end of the sequence we want to use.

To understand this let's look at [ex_10](src/ex_10.cpp):

```
string str = "626123456790912345678";
int offsets[] = {3, 3, 4, 1, 2, 3};
offset_separator sep(offsets, offsets+3);
tokenizer<offset_separator> mytok(str, sep);
```

The `offset_separator` takes in two arguments, `offsets` and `offsets+3`.
`offsets` is the address of the first index of the array `offsets`.
Therefore, the sequence of integers starts at the first index of the array `offsets`.
`offsets+3` is the address of the fourth index of the array `offsets` and the address that is one spot past the end of the sequence.
Using these arguments, our sequence is `{3,3,4}`.

Let's see what gets outputted.

```
$ g++ -std=c++11 ex_10.cpp -o ex_10
$ ./ex_10
Original String: 626123456790912345678
Token: 626
Token: 123
Token: 4567
Token: 909
Token: 123
Token: 4567
Token: 8
```

As you can see, the original string is split into tokens with the lengths of 3, 3, and 4, which are the numbers in our sequence.
Once the integers in our sequence are all used, the length of the tokens starts over at the beginning of the sequence.
Notice that the last token has a length of 1, since we are out of characters to put into tokens.

Now let's look at an `offset_separator` that uses a vector and iterators. 
We can see an example of this in [ex_11](src/ex_11.cpp).

```
string str = "626123456790912345678";
vector<int> offsets = {3, 3, 4};
offset_separator sep(offsets.begin(), offsets.end());
tokenizer<offset_separator> mytok(str, sep);
```

The sequence of integers begins at the iterator `offsets.begin()` and goes up to, but does not include, `offsets.end()`.
Therefore, the sequence of integers is `{3,3,4}`, which is the same sequence as the previous example.
Since the original string and the sequence of integers are both the same as the previous example, the output should be the same as well.

```
$ g++ -std=c++11 ex_11.cpp -o ex_11
$ ./ex_11
Original String: 626123456790912345678
Token: 626
Token: 123
Token: 4567
Token: 909
Token: 123
Token: 4567
Token: 8
```

As you can see, the output is exactly the same as the last example.
Whether you use an array of offsets or a vector of offsets, you can achieve the same results.

##Bringing it all together

The Boost Tokenizer package uses three `TokenizerFunc` models to provide a variety of ways to make parsing much easier for almost any project.

For example, let's say you are making a program that reads and interprets user input commands and options separated by whitespace.
To filter out the whitespace to find each command or option, all you have to do is add whitespace to the delimiter set of either the `char_separator` model or the `escaped_list_separator` model.

What if you want a certain character to connect two commands?
One possible solution is to add the character to the set of kept delimiters, using the `char_separator` model, and having the program react appropriately when finding the kept delimiter.

Now let's say you want to consider a substring inside a pair of quotes as one command, even if there is whitespace between the quotes. 
With `escaped_list_separator`, all you have to do is add the `"` character to the quote character set.

Unlike the other two models, the `offset_separator` model is limited to situations where you know how long tokens should be.
For example, one use of this model is to separate the numbers in phone numbers or dates, assuming that there is no punctuation.
