#The Boost Library Tokenizer

A tokenizer extracts meaningful substrings from a string.
These substrings are called tokens.
Tokenizing makes life easier when you want to break up a string.
For example, you can tokenize the string `Get thee to a nunnery`, which will be broken up into the tokens: `Get`, `thee`, `to`, `a`, and `nunnery`.

##How do we do use the boost tokenizer?

Let's look at the code from [ex1.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_1.cpp).

The first thing we'll have to do is include the boost tokenizer library and use the boost namespace.

```
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;
```

Then we call the tokenizer function and use iterators to traverse through the tokens.

```
int main() {
    string str = "Don't panic, too much. 12,34";
    tokenizer<> mytok(str);
    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << *it << endl;
    return 0;
}
```

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
But we can control how the boost tokenizer parses by defining something which is known as a delimiter.

A ***delimiter*** is a sequence of one or more characters that separate tokens, and a tokenizer looks at what delimiters are passed in so that it can know where to separate the tokens.
So for this example, we can say that the default delimiters are white space and all non-letter/number characters.

To explain in detail how this string got parsed, it should be noted that `tokenizer<>` parses by characters.
So this tokenizer will go through each character in the string and it will check to see if it is in the delimiter set.
Once it finds a match, the tokenizer will know that everything up until that character is a token so `Don` becomes a token since it finds `'`, which is a non-letter/number character.
It will then move on to creating the next token and once it finds the space after `t`, it creates the token `t`.
And so this continues on until the tokenizer has gone through the whole string.

###Defining our own delimiters with char_separator

It would be better to be able to define our own delimiters, so let's work with the code from [ex_2.cpp](https://github.com/vgarc018/cs100hw4/blob/master/src/ex_2.cpp).

```
string str = "Thou&&&&art&as    fat&as&&butter";
char_separator<char> delim("&");
tokenizer< char_separator<char> > mytok(str, delim);
```

The `char_separator<char>` is one of the models of the boost tokenizer library and declaring tokenizer with `char_separator<char>` lets boost know that we're going to use our own delimiters.
Notice how the tokenizer function now has an extra parameter, `delim`, which will be our delimiter set.

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

**Note:** There are other separators that can be used, but for this particular tutorial we're going to work with `char_separator<char>`.
But check [the other separators](http://www.boost.org/doc/libs/1_57_0/libs/tokenizer/index.html) out if you want to see what else you can do with boost tokenizer.

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
Similarly, we could also opt to not pass in `delim` into our function like this,

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

##Going beyond with char_separator

Here are the basics of making a tokenizer with your own delimiters so far:

 - Create your own delimiter:

  `char_separator<char> delim(DELIMITERS);`

 - Make a tokenizer function:

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

##Bringing it all together

The Boost tokenizer provides an easy way to parse through a string.

Do not forget to declare these things before using the tokenizer:

```
#include <boost/tokenizer.hpp>
using namespace boost;

//if you want to declare a delimeter instead of the default
char_separator<char> delim("&");
tokenizer< char_separator<char> > mytok(str, delim);

//else just declare it like this
tokenizer<> mytok(str);
```

Our `char_separator<char>` model also has extra features that other tokenizing functions such as `strtok` do not have.

The model has the parameters set like this:

```
explicit char_separator(const char* dropped_delims,
                        const char* kept_delims = "",
                        empty_token_policy empty_tokens = drop_empty_tokens)
```

The `dropped_delim` parameter should always be passed in but if it wasn't, boost tokenizer will still parse the string.  Otherwise `kept_delims` and `empty_tokens` are already set to defaults and are optional traits.
In order to use `kept_delims`, we simply pass in what delimiters we want to keep, and in order to use empty tokens we pass in `keep_empty_tokens` for `empty_tokens`.

References:

[Boost Library Documentation](http://www.boost.org/doc/libs/1_57_0/libs/tokenizer/index.html)
