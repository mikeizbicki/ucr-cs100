##Introduction To strtok

String tokenization is the process of breaking a string up into smaller substrings, with each substring being separated by a specified character. When used appropriately, string tokenization can make parsing commands a simple task.

In this tutorial, we will cover the use and nuances of the `strtok` function. Let's take a look at the example below.

```
char example_0[] = "behold the power of strtok!";
```
If we wanted to split it up into smaller components that are separated by the space character `' '`, we would do something like this:
```
cout << strtok(example_0, " ") << endl;
cout << strtok(NULL, " ") << endl;
cout << strtok(NULL, " ") << endl;
cout << strtok(NULL, " ") << endl;
cout << strtok(NULL, " ") << endl;
```
Which would give us output like this:
```
behold
the
power
of
strtok!
```

####The Basics

The example above does not make it clear exactly how `strtok` is used. Looking at how the function is set up may show some clues. Accessing the [man](http://linux.die.net/man/3/strtok) page for `strtok` shows the function prototype.
```
#include <string.h>
char *strtok(char *str, const char *delim);
```
The function takes two arguments, the string that is to be parsed (`str`) and what is known as the **delimiter** (`delim`). It returns what is called a **token**, which is the first substring in `str` that does not contain `delim`.

Let's look at another example and break down what is going on
```
char example_1[] = Rootabega;
char *first_token = strtok(example_1, "a");
```
Here we are parsing the string "Rootabega". The deliminator is the letter "a". So we are looking for the first substring in "Rootabega" that does not have the letter "a" in it. From this we see that `first_token` will be assigned the word "Root", the first token of the string.
```
char *first_token = strtok(example_1, "a");
//is the same as
char *first_token = "Root";
```
####The NULL Argument

We now know the basics of how `strtok` works, but still do not have an explanation for why, in the first example, `\0` was used in subsequent uses of `strtok` when parsing out the next several tokens.

What would happen if we did not do that? Look at this program 
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_2[] = "Rootabeganot";
	
	//get the first two tokens
	char *first_token = strtok(example_2, "a");
	char *second_token = strtok(example_2, "a");

	//display the first two tokens
	cout << "Token 1: " << first_token << endl
		<< "Token 2: " << second_token << endl;
	return 0;
}
```
Based on what has been learned from the `strtok` prototype you would expect the output to look like:
```
Token 1: Root
Token 2: beg
```
But when the program is compiled and executed, you get:
```
Token 1: Root
Token 2: Root
```
Why does this happen? The answer is whenever something is passed into the `str` argument for`strtok`, the function assumes that this is a new string to parse. The way `strtok` works is that whenever it finds a token, it removes that token and the following deliminator from the string being looked at. It then holds on to the rest of the string to be use as the "default" if no string is passed in the next time `strtok` is called. In the above program, both calls received a new string to parse, overriding the default value.

With this in mind let's change the above program and walk through what is happening.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_2[] = "Rootabeganot";

	//get the first two tokens
	char *first_token = strtok(example_2, "a");
	char *first_copy = strtok(example_2, "a");//changed variable name
	char *second_token = strtok(NULL, "a");   //added this new command

	//display the first two tokens
	cout << "Token 1: " << first_token << endl
		<< "Token 2: " << second_token << endl;
	return 0;
}
```
In the first call to `strtok`, the first token is found to be `Root`. The function then removes the token and the delimiter from the `str` argument. This new string is then saved for later use.
```
char *first_token = strtok(example_2, "a");
//first_token = "Root"
//"Roota" is removed from "Rootabeganot" to get "beganot", which is saved for later
```
In the second call to `strtok`, a new value was passed into the `str` argument, overriding the previous saved string. The function then runs like before; get the token, remove it and the delimiter, then save the new string for later.
```
char *first_copy = strtok(example_2, "a");
//a new str argument was given, so the saved string from before, "beganot", is ignored
//first_copy = "Root"
//"Roota" is removed from "Rootabeganot" to get "beganot", which is saved for later
```
In the third call to `strtok`, no new argument is given, since `\0` (which is `NULL`) means nothing, so the previous saved string is used for the `str` argument and the function runs as before.
```
char *second_token = strtok(NULL, "a");
//NULL, or nothing, is passed in to the str argument
//find first token from "beganot"
//second_token = "beg"
//"bega" is removed from "beganot" to get "not", which is saved for later
```
So we know now why `\0` is used in strtok. However, looking at this example raises the question of what would happen if we wanted to get the third token? This also brings up another question, what would happen if we tried to go beyond that?

##Failure And Edge Cases

####Failure
In the previous example we took the string "Rootabeganot" and used the `strtok` function to extract the first two tokens of this string using "a" as the delimiter. Looking at what remains after getting the tokens, "Root" and "beg", we see that the string "not" still remains. The delimiter "a", however, is nowhere to be found. So what would happen if we ran `strtok` again? What if we ran it after that?

Let's modify the program from before and find out
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_2[] = "Rootabeganot";

	//get the tokens
	char *first_token = strtok(example_2, "a");
	char *second_token = strtok(NULL, "a");     //removed variable first_copy
	char *third_token = strtok(NULL, "a");      //added variable third_token
	char *fourth_token = strtok(NULL, "a");     //added variable fourth_token

	//display the tokens
	cout << "Token 1: " << first_token << endl
		<< "Token 2: " << second_token << endl
		<< "Token 3: " << third_token << endl  //display third_token
		<< "Token 4: " << fourth_token << endl;//display fourth_token
	return 0;
}
```
Running this program gives us: 
```
Token 1: Root
Token 2: beg
Token 3: not
Token 4:
```
From this we see that `strtok` was able to get the last token, even though the delimiter was not in it, and that the function was able to handle the case of an empty string. Why is that?

In the previous section [The Basics](#the-basics), it was stated that to get the token, `strtok` looks for the first substring in the `str` argument that does not contain the deliminator `delim`. So, if the delimiter is not in the `str` argument, then the entire argument is considered to be the token.
```
char example_3[] = "This is the entire token";
char *first_token = strtok(example_3, "A");
//Look for the first occurrence of "A"
//"A" was not found
//first_token = "This is the entire token";
```
In the case when there is nothing left to look at, or if nothing was initially passed to the `str` argument, `strtok` returns `\0`. This enables the use of `while` loops for parsing a string.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_4[] = "See how% the modulo blade%slices % through % this string";
	char *token;
	token = strtok(example_4, "%");
	//prints out each token in example_4
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, "%");
	}
	return 0;
}
```
When you compile and execute this code, you get:
```
See how
 the modulo blade
slices 
 through 
 this string
```

####Delimiters At The Ends And Chained Delimiters

We know now what happens when the delimiter is not in the `str` argument. What if, however, the delimiter
was at the beginning and or end of the argument? What about if the delimiter was chained together multiple 
times?

Let's modify the above program to see if the output changes when the delimiter appears at the ends of the 
`str` argument.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_5[] = "%See how% the modulo blade%slices % through % this string%"; 
	//added the delimiter % to the beginning and end of the string to be parsed
	char *token;
	token = strtok(example_5, "%");
	//prints out each token in example_5
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, "%");
	}
	return 0;
}
```
When you compile and execute this code, you get:
```
See how
 the modulo blade
slices 
 through 
 this string
```
When you compare this output to the output of the previous program, you see that they are the same. It's as
if adding the delimiters to the ends of the `str` argument **had no effect at all** on the output.

What about the case for chained delimiters? Will the output stay the same as before like it did when we added
delimiters to the ends? Let's modify the program one more time and see what happens.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_6[] = "%%%See how%%% the modulo blade%%%%%%slices %%% through %% this string%%%%%%%";
	//added instances of consecutive delimiters
	char *token;
	token = strtok(example_6, "%");
	//prints out each token in example_6
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, "%");
	}
	return 0;
}
```
When you compile and execute this code, you get:
```
See how
 the modulo blade
slices 
 through 
 this string
```
Just like before, it appears that chaining the delimiter multiple times did not affect the output. What is
`strtok` doing to handle these cases?

Let's look at another example and walk through what is happening
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_7[] = "@@@Green eggs@@@and ham@@@@";
	char *token_1 = strtok(example_7, "@");
	char *token_2 = strtok(NULL, "@");
	//prints out each token in example_7
	cout << token_1 << endl
		<< token_2 << endl;
	return 0;
}
```
Before `strtok` looks for tokens, it checks if any of the end characters in the string are delimiters
and removes them if they are.
```
char example_7[] = "@@@Green eggs@@@and ham@@@@";
char *token_1 = strtok(example_6, "@");
//example_7[0] == '@'
//example_7[size-1] == '@'
//the first and last character are delimiters, so remove them
//example_7 = "@@Green eggs@@@and ham@@@"
```
The `strtok` function keeps running this check until neither the first or last character in 
the `str` argument are deliminators.
```
//example_7[0] = '@'
//example_7[size-1] = '@'
//the first and last character are delimiters, so remove them
//example_7 = "@Green eggs@@@and ham @@"

//example_7[0] = '@'
//example_7[size-1] = '@'
//the first and last character are delimiters, so remove them
//example_7 = "Green eggs@@@and ham@"

//example_7[0] = 'G'
//example_7[size-1] = '@'
//only the last character is a delimiter, so remove it
//example_7 = "Green eggs@@@and ham"

//example_7[0] = 'G'
//example_7[size-1] = 'm'
//neither the first or last character is a delimiter, proceed to find the first token

//token_1 = "Green eggs"
//"Green eggs@" is removed from "Green eggs@@@and ham" to get "@@and ham" which is saved for later
```
In other words, **`strtok` ignores any delimiters that are at the ends of the string being parsed**. 

This is also how `strtok` handles chained delimiters. Back in the section
[The NULL Argument](#the-null-argument) above it was stated that each time `strtok` found a token, 
it would remove that token and the delimiter from the string being parsed. Note that the delimiter was only 
one character, so if the delimiter was chained together many times, the string that is saved for later would
have at least one delimiter character at the start. 
By running the check for delimiters at the ends, `strtok` removes those extra delimiters. 
```
char *token_2 = strtok(NULL, "@");
//NULL, or nothing, is passed into the str argument
//find first token from leftover = "@@and ham"

//leftover[0] = '@'
//leftover[size-1] = 'm'
//only the first character is a delimiter, so remove it
//leftover = "@and ham"

//leftover[0] = '@'
//leftover[size-1] = 'm'
//only the first character is a delimiter, so remove it
//leftover = "and ham"

//leftover[0] = '@'
//leftover[size-1] = 'm'
//neither the first or last character is a delimiter, proceed to find the second token

//token_2 = "and ham"
```
In other words, **`strtok` treats chained delimiters as single delimiters**.

####Multi-Character And Changing Delimiters
So far we have only been using examples where the delimiter is only one letter or character. The `strtok`
function can actually take in multi-character strings as its delimiter. Doing this, however, raises an
important question; is the delimiter that `strtok` searches for the exact pattern entered or something else?
Let's test it to find out.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_8[] = "Testing 1 to 2 find 12 many 21 delims 121 in a 212 string";
	char *token;
	token = strtok(example_8, "12");
	//prints out each token in example_4
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, "12");
	}
	return 0;
}
```
When we compile and execute this program, we get:
```
Testing 
 to 
 find 
 many 
 delims
 in a 
 string
```
From this we see that `strtok` did not look for the first occurrence of the exact sequence; it looked for the
first occurrence of any of the characters passed into the `delim` argument.

Another thing we have not discussed is changing the delimiter in subsequent calls to `strtok`. There is
nothing really significant about this other than the fact that you can do it. The following
program is an example of changing the delimiter in subsequent calls of `strtok`.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char example_9[] = "I have/changed my delimiter?partway through";
	char *token;
	token = strtok(example_9, "/");
	cout << token << endl;
	token = strtok(NULL, " ");
	cout << token << endl;
	token = strtok(NULL, "?");
	cout << token << endl;
	token = strtok(NULL, "+");
	cout << token << endl;
	return 0;
}
```
When you compile and execute the program, you get:
```
I have
changed
my delimiter
partway through
```

##Parsing Multiple Strings

All that was discussed so far only went over parsing a single string for its contents. However, there will
be times when you will have to parse multiple strings, be it one after the other or at the same time. Are we
still able to use `strtok` for this?

Let's look at the case where we parse one string after the next. In this example, we first use `strtok` to 
completely parse through the first string, displaying its tokens as we get them. We then use `strtok` to
completely parse through the second string, again displaying its tokens as we get them.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char string_1[] = "Parse all the things!";
	char string_2[] = "Let's_do_it_again!";
	char *token;

	//parse string_1
	token = strtok(string_1, " ");
	cout << "Tokens of string_1:" << endl;
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, " ");
	}

	//parse string_2
	token = strtok(string_2, "_");
	cout << "\nTokens of string_2:" << endl;
	while(token != NULL)
	{
		cout << token << endl;
		token = strtok(NULL, "_");
	}

	return 0;
}
```
When you compile and execute this program, you get:
```
Tokens of string_1:
Parse
all
the
things!

Tokens of string_2:
Let's
do
it
again!
```
The output here is not surprising, since we don't give `strtok` a new string to parse until after the 
first one has been parsed completely.

Now let's look at the case where we parse multiple strings simultaneously. What this means is we begin to 
parse a string while another string is being parsed. In the following program, we get the first two tokens
of `string_1` before parsing all of `string_2`. The program is then supposed to continue parsing `string_1`.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char string_1[] = "Parse all the things!";
	char string_2[] = "If I may interrupt.";
	char *token;

	//parse string_1
	token = strtok(string_1, " ");
	cout << "   Tokens of string_1:" << endl;
	for(int i = 0; token != NULL; i++)
	{
		cout << "   " << token << endl;
		if(i == 1)
		{
			//parse string_2
			token = strtok(string_2, " ");
			cout << "\nTokens of string_2:" << endl;
			while(token != NULL)
			{
				cout << token << endl;
				token = strtok(NULL, " ");
			}
		}
		token = strtok(NULL, " ");
	}
	return 0;
}
```
When you compile and execute this program, you get:
```
Tokens of string_1:
Parse
all
   Tokens of string_2:
   If
   I
   may
   interrupt.
```
Looking at the output of the program, we see that `string_1` was partly parsed before `string_2`
was fully parsed. After that, the output stops. We actually have seen something similar to this back 
in the section [The NULL Argument](#the-null-argument) above. There we discussed that in order to parse
a string using `strtok`, the `str` argument must be `\0` in subsequent calls to `strtok`, otherwise the string
being parsed will be reset. That is what happens in the program here; in the middle of parsing `string_1`
the parsed string is reset to `string_2`.

What we need to do to is somehow keep track of where we are in each string that we are parsing so we can go 
back to where we left off. Unfortunately this is just not possible with the `strtok` function. Enter the function
**`strtok_r`**.

The function `strtok_r` is essentially the same as `strtok`, and follows the same rules with regards to
subsequent calls for parsing the same string and the different cases for the delimiter. However, unlike `strtok`,
`strtok_r` is able to record how much is left to parse in a string. How does it do that? Let's look at the 
function prototype for `strtok_r`, found on the man page for `strtok`.
```
#include <string.h>
char *strtok_r(char *str, const char *delim, char **saveptr);
```
It looks exactly the same as that for `strtok`, except that it takes in an additional argument, `saveptr`. The
`str` and `delim` arguments function for `strtok_r` work the same way they do for `strtok`. The `saveptr` 
argument is how `strtok_r` keeps track of what is left to be parsed in `str`.
  
Let's use `strtok_r` in the previous program and walk through what is happening.
```
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char string_1[] = "Parse all the things!";
	char string_2[] = "If I may interrupt.";
	char *token, *save_1, *save_2;				//added two saveptrs: save_1 and save_2

	//parse string_1
	token = strtok_r(string_1, " ", &save_1);		//replaced strtok with strtok_r
	cout << "Tokens of string_1:" << endl;
	for(int i = 0; token != NULL; i++)
	{
		cout << token << endl;
		if(i == 1)
		{
			//parse string_2
			token = strtok_r(string_2, " ", &save_2);//replaced strtok with strtok_r
			cout << "   Tokens of string_2:" << endl;
			while(token != NULL)
			{
				cout << "   " << token << endl;
				token = strtok_r(NULL, " ", &save_2);//replaced strtok with strtok_r
			}
		}
		token = strtok_r(NULL, " ", &save_1);		  //replaced strtok with strtok_r
	}
	return 0;
}
```
We first begin by parsing `string_1`. Here the token is found to be `Parse`. Like `strtok`, `strtok_r` removes
the token and the delimiter from the `str` argument. Unlike `strtok`, `strtok_r` saves the remaining string
in `save_1`.
```
token = strtok_r(string_1, " ", &save_1);
//token = "Parse"
//"Parse " is removed from "Parse all the things!" to get "all the things!"
//save_1 = "all the things!"
```
In the second call to `strtok_r`, no new argument was given for `str`. This causes `strtok_r` to look at the
value of the `saveptr` that was passed in to it and get the token from there. It then runs as before; getting
the token, removing it and the deliminator from the `saveptr` value, then storing this new string in that same
`saveptr`, overriding its old contents.
```
token = strtok_r(NULL, " ", &save_1);
//nothing is passed into the str argument
//find the first token from the string stored in save_1, which in this case is "all the things!"
//token = "all"
//"all " is removed from "all the things!" to get "the things!"
//save_1 = "the things"
```
Notice that the procedure described here is very similar to the one discussed in the section 
[The NULL Argument](#the-null-argument) above, with the difference being that the string 
saved for later is stored in a `saveptr` rather than within `strtok_r`.

In the next call to `strtok_r` we begin parsing `string_2`. We will skip the step by step walkthrough and move
on to where we try to pick up where we left off with `string_1`. Keep in mind that the things left to parse in
`string_2` were stored in `save_2`.

When we were using `strtok`, we found that we couldn't continue parsing `string_1`. This is because when we 
began parsing `string_2`, `strtok` threw away what remained to parse of `string_1` and began to store what 
remained to parse of `string_2`. When we finished parsing `string_2` to continue with `string_1`, `strtok`
still held on to what was left to parse of `string_2`.

When using `strtok_r`, the remaining things to parse in `string_2` were stored in `save_2`, just as the remaining
things to parse in `string_1` was stored in `save_1`. So when we go back to continue parsing `string_1` we simply
need to call the `saveptr` that holds what is left of `string_1`.
```
token = strtok_r(NULL, " ", &save_1);
//nothing is passed into the str argument
//find the first token from the string stored in save_1, which in this case is "the things!"
//token = "the"
//"the " is removed from "the things!" to get "things!"
//save_1 = "things"
```
Continue on with the program and you get:
```
Tokens of string_1:
Parse
all
   Tokens of string_2:
   If
   I
   may
   interrupt.
the
things!
```
As a general rule, only use `strtok` when parsing a single string and use `strtok_r` whenever you 
parse multiple strings. Also, you must always specify what `saveptr` you are using when using `strtok_r`.

Here is a quick cheat sheet that summarizes the features we covered:
* `strtok` can be used to parse strings
* function setup for `strtok` and `strtok_r`

```
#include <string.h>
char *strtok(char *str, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
  ```
* when continuing to parse the same string, `str` should be `\0` in each subsequent call to `strtok`
* if there is nothing left to parse, `strtok` returns `\`
* rules of `delim`, the delimiter
  * this must always be specified when using `strtok`
  * is ignored when at the beginning or end of the `str` argument
  * `strtok` looks for the first occurrence of any character in `delim`, not the exact pattern that was
  passed in
* strtok_r is used to parse multiple strings at once
* `strtok_r` follows the same rules as `strtok` with the addition of the `saveptr` argument
  * the `saveptr` argument keeps track of what is left after the first token is found


