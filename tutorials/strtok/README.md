#How to Use Strtok

###What is Strtok?

  The `strtok` function lets you take a character array and break it up into
  smaller substrings, with each one being separated by a specified character.

  What this means is that you, the user, can take the word
  ```
  char example_0[] = "behold+the+power+of+strtok!";
  ```
  and split it up into smaller components that are separated by the character `+`
  ```
  cout << strtok(example_0, "+") << endl;
  cout << strtok(NULL, "+") << endl;
  cout << strtok(NULL, "+") << endl;
  cout << strtok(NULL, "+") << endl;
  cout << strtok(NULL, "+") << endl;
  ```
  to get output like this
  ```
  behold
  the
  power
  of
  strtok!
  ```

####Why You Should Care

  When used appropriately, strtok can make string parsing very easy to do, which
  saves you time and sanity.

###The Way of Strtok
####One Small Step for String (Parsing once)

  The example above does not make it clear exactly how `strtok` is used. Looking at how the function 
  is set up may show some clues. Accesseing the man page for `strtok` shows the function is set up like
  this.
  ```
  #include <string.h>
  char *strtok(char *str, const char *delim);
  ```
  So the function takes two arguments, the string that is to be parsed, `str`, and what is known as 
  the **delimiter**, `delim`. It returns what is called a **token**, which is the first substring
  in `str` that does not contain `delim`.

  Let's look at another example and break down what is going on

  	char example_1[] = Rootabega;
 	char *first_token = strtok(example_1, "a");

  Here we are parsing the string "Rootabega". The deliminator is the letter "a". So we are looking for
  the first substring in "Rootabega" that does not have the letter "a" in it. From this we see that 
  `first_token` will be assigned the word "Root", the first token of the string.

	char *first_token = strtok(example_1, "a");
	//is the same as
  	char *first_token = "Root";

####Gaze into the NULL (Parsing multiple times)

  We now know the basics of how `strtok` works, but still do not have an explanation for why, in the 
  first example, `NULL` was used in subsequent uses of `strtok` when parsing out the next several tokens.
  What were to happen if we did not do that? Look at this program 

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

  Based on what has been learned from how the `strtok` is set up you would expect the output to look like this
  ```
  Token 1: Root
  Token 2: beg
  ```
  However when the program is compiled and executed, the output you get is this
  ```
  Token 1: Root
  Token 2: Root
  ```
  Why does this happen? The answer is whenever something is passed into the `str` argument for`strtok`,
  the function assumes that this is a new string to parse. The way `strtok` works is that whenever it finds a t
  oken, it removes that token and the following deliminator from the string being looked at. It then holds on to 
  the rest of the string to be use as the "default" if no string is passed in the next time `strtok` is called. 
  In the above program, both calls recieved a new string to parse, overriding the default value.

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
  In the first call to `strtok`, the first token is found to be "Root". The function then removes the token and
  the delimiter from the `str` argument and saves this new string for later use.
  ```
  char *first_token = strtok(example_2, "a");
  //first_token = "Root"
  //"Roota" is removed from "Rootabeganot" to get "beganot", which is saved for later
  ```
  In the second call to `strtok`, a new value was passed into the `str` argument, overriding the previous saved
  string. The function then runs like before; getting the token, removing it and the delimiter and saving the new 
  string for later.
  ```
  char *first_copy = strtok(example_2, "a");
  //a new str argument was given, so the saved string from before, "beganot", is ignored
  //first_copy = "Root"
  //"Roota" is removed from "Rootabeganot" to get "beganot", which is saved for later
  ```
  In the third call to `strtok`, no new argument is given, since `NULL` means nothing, so the previous saved 
  string is used for the `str` argument and the function runs as before.
  ```
  char *second_token = strtok(NULL, "a");
  //NULL, or nothing, is passed in to the str argument
  //find first token from "beganot"
  //second_token = "beg"
  //"bega" is removed from "beganot" to get "not", which is saved for later
  ```
  So we know now why `NULL` is used in strtok. However, looking at this example raises the question of what would
  happen if we wanted to get the third token? This also brings up another question, what would happen if we tried 
  to go beyond that?

####The Last Token and Beyond! (Rules of the delimiter)
  In the previous example we took the string "Rootabeganot" and used the `strtok` function to extract the first
  two tokens of this string using "a" as the delimiter. Looking at what remains after getting the tokens, "Root"
  and "beg", we see that the string "not" still remains. The delimiter "a", however, is nowhere to be found. 
  So what would happen if we ran `strtok` again? What if we ran it after that?

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
		char *second_token = strtok(NULL, "a");
		char *third_token = strtok(NULL, "a");
		char *fourth_token = strtok(NULL, "a");

		//display the tokens
		cout << "Token 1: " << first_token << endl
	     	<< "Token 2: " << second_token << endl
			<< "Token 3: " << third_token << endl
			<< "Token 4: " << fourth_token << endl;
  		return 0;
  	}
  ```
  Running this program gives us the following output
  ```
  Token 1: Root
  Token 2: beg
  Token 3: not
  Token 4:
  ```
  From this we see that `strtok` was able to get the last token, even though the delimiter was not in it, and
  that the function was able to handle the case of an empty string. Why is that?

  In **One Small Step for String** it was stated that to get the token, `strtok` looks for the first substring
  in the `str` argument that does not contain the deliminator `delim`. So, if the delimiter is not in the `str`
  argument, then the entire argument is considered to be the token.
  ```
  char example_3[] = "This is the entire token";
  char *first_token = strtok(example_3, "A");
  //Look for the first occurence of "A"
  //"A" was not found
  //first_token = "This is the entire token";
  ```
  In the case when there is nothing left to look at, or if nothing was initially passed to the `str` argument,
  `strtok` returns `NULL`. This enables the use of `while` loops for parsing a string.
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
	//Output:
	//See how
	// the modulo blade
	//slices 
	// through 
	// this string
  ```
  We know now what happens when the delimiter is not in the `str` argument. What if, however, the delimiter
  were at the beginning and or end of the it? What about if the delimiter was chained together multiple times?

  In the case of the delimiter appearing at the ends of the `str` argument, `strtok` simply ignores them.
  ```
  char example_6[] = "@ What happens@to delimiters@ at the ends@";
  char *token = strtok(example_6, "@");
  //in strtok
  //@ What happens@to delimiters@ at the ends@ 
  //is seen as
  // What happens@to delimiters@ at the ends
  ```
  For the case where the deliminator is chained together multiple times, each instance where that happens is
  the same as if the deliminator was only placed once.
  ```
  char example_7[] = "@@ What @@happens to @ chained @@@@@ delimiters";
  char *token = strtok(example_7, "@");
  //in strtok
  //@@ What @@happens to @ chained @@@@@ delimiters 
  //is the same as
  //@ What @happens to @ chained @ delimiters
  //which is then seen as
  // What @happens to @ chained @ delimiters
  ```

  So far we have only been using examples where the delimiter is only one letter or character. The `strtok`
  function can actually take in multi-character strings as its delimiter. However, when this is done, the
  function doesn't look for the first occurence of the exact sequence; it looks for the first occurence of 
  any of the characters passed into the `delim` argument.
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
	//Output:
	//Testing 
	// to 
	// find 
	// many 
	// delims
	// in a 
	// string
  ```

  It should also be noted that in subsequent calls to `strtok` when parsing a string, you can change what the
  delimiter is to get different tokens.
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
	//Output:
	//I have
	//changed
	//my delimiter
	//partway through
  ```

###The Hidden _r (Parsing multiple strings)

  All that was discussed so far only went over parsing a single string for its contents. However, there will
  be times when you will have to parse multiple strings, be it one after the other or at the same time. Are we
  still able to use `strtok` for this?

  Let's look at the case where we parse one string after the next
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
	//Output:
	//Tokens of string_1:
	//Parse
	//all
	//the
	//things!
	//
	//Tokens of string_2:
	//Let's
	//do
	//it
	//again!
  ```
  Looking at the output of this program we see that `strtok` is able to correctly parse multiple strings if
  each is parsed completely before the next one.

  Now let's look at the case where we parse multiple strings simultaneously. What this means is we begin to 
  parse a string while another string is being parsed, like what is happening in the program below.
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
	//Output:
	//Tokens of string_1:
	//Parse
	//all
	//   Tokens of string_2:
	//   If
	//   I
	//   may
	//   interrupt.
  ```
  Looking at the output of the program, we see that only part of `string_1` was partly parsed before `string_2`
  was fully parsed. However, after that the output ceased. From looking at the program and from what we know of
  `strtok`, it is easy to see why this ouput occurs.

  Within the outer loop the program parses through `string_1` until `i` is 1.
  ```
  	//first use of strtok, outside of the loop
	token = strtok(string_1, " ");
		//token = "Parse"
		//remaining string to parse = "all the things!"
	//enter for loop 
		//first iteration
		token = strtok(NULL, " ");
			//i = 0, don't go into while loop
			//token = "all"
			//remaining string to parse = "the things!"
		//second iteration
			//i = 1, begin parsing string_2
			//remaining string to parse = "the things!"
  ```
  The program then completely parses through `string_2` in the inner loop before going back to the outer loop.
  ```
	//get first token
	token = strtok(string_2, " ");
		//remaining string to parse, "the things!", is not used and replaced with string_2
		//token = "If"
		//remaining string to parse = "I may interrupt."
	//enter while loop
		//first iteration
		token = strtok(NULL, " ");
			//token = "I"
			//remaining string to parse = "may interrupt."
		//second iteration
		token = strtok(NULL, " ");
			//token = "may"
			//remaining string to parse = "interrupt."
		//third iteration
		token = strtok(NULL, " ");
			//token = "interrupt."
			//remaining string to parse = ""
		//fourth iteration
		token = strtok(NULL, " ");
			//token = NULL
			//remaining string to parse = ""
			//exit while loop
	//finished parsing string_2
  ```
  As you can see, the result of parsing `string_2` carried over into the parsing of `string_1 `, leaving nothing 
  left to parse. This caused each successive call to `strtok` to only return NULL. What we need to do to is
  somehow keep track of where we are in each string that we are parsing if this is to work. Unfortunately this
  is just not possible with the `strtok` function.

  As it turns out, `strtok` has a brother called `strtok_r` who does exactly the same thing as `strtok`, follows
  all the same rules as `strtok`, but does one more thing that `strtok` doesn't; it keeps track of where you
  are in the string with something it calls **saveptr**. Here is the function declaration for `strtok_r`, found
  on the man page for `strtok`.
  ```
  #include <string.h>
  char *strtok_r(char *str, const char *delim, char **saveptr);
  ```
  It looks exactly the same as that for `strtok`, except that it takes in an additional argument, `saveptr`. The
  `str` and `delim` arguments function for `strtok_r` work the same way they do for `strtok`. The `saveptr` 
  argument, as stated before, serves as a way to keep track of what is left to be parsed in `str`.
  
  Let's use it in the previous program and walk through what is happening..
  ```
	#include <iostream>
	#include <string.h>
	using namespace std;

	int main()
	{
		char string_1[] = "Parse all the things!";
		char string_2[] = "If I may interrupt.";
		char *token, *save_1, *save_2;

		//parse string_1
		token = strtok_r(string_1, " ", &save_1);
		cout << "Tokens of string_1:" << endl;
		for(int i = 0; token != NULL; i++)
		{
			cout << token << endl;
			if(i == 1)
			{
				//parse string_2
				token = strtok_r(string_2, " ", &save_2);
				cout << "   Tokens of string_2:" << endl;
				while(token != NULL)
				{
					cout << "   " << token << endl;
					token = strtok_r(NULL, " ", &save_2);
				}
			}
			token = strtok_r(NULL, " ", &save_1);
		}
		return 0;
	}
	//Output:
	//Tokens of string_1:
	//Parse
	//all
	//   Tokens of string_2:
	//   If
	//   I
	//   may
	//   interrupt.
	//the
	//things!
  ```
  Within the outer loop the program parses through `string_1` until `i` is 1.
  ```
  	//first use of strtok, outside of the loop
	token = strtok_r(string_1, " ", &save_1);
		//token = "Parse"
		//save_1 = "all the things!"
		//save_2 = nothing
	//enter for loop 
		//first iteration
		token = strtok_r(NULL, " ", &save_1);
			//i = 0, don't go into while loop
			//token = "all"
			//save_1 = "the things!"
			//save_2 = nothing
		//second iteration
			//i = 1, begin parsing string_2
			//save_1 = "the things!"
			//save_2 = nothing
  ```
  The program then completely parses through `string_2` in the inner loop before going back to the outer loop.
  ```
	//get first token
	token = strtok_r(string_2, " ", &save_2);
		//remaining string to parse, "the things!", is not used and replaced with string_2
		//token = "If"
		//save_1 = "the things!"
		//save_2 = "I may interrupt."
	//enter while loop
		//first iteration
		token = strtok_r(NULL, " ", &save_2);
			//token = "I"
			//save_1 = "the things!"
			//save_2 = "may interrupt."
		//second iteration
		token = strtok_r(NULL, " ", &save_2);
			//token = "may"
			//save_1 = "the things!"
			//save_2 = "interrupt."
		//third iteration
		token = strtok_r(NULL, " ", &save_2);
			//token = "interrupt."
			//save_1 = "the things!"
			//save_2 = ""
		//fourth iteration
		token = strtok_r(NULL, " ");
			//token = NULL
			//save_1 = "the things!"
			//save_2 = ""
			//exit while loop
	//finished parsing string_2
  ```
  From this we see that the saveptrs, `save_1` and `save_2`, keep track of what is left to parse in `string_1`
  and `string_2` respectively.

  As a general rule, only use `strtok` when parsing a single string and use `strtok_r` whenever you parse multiple
  strings.

###Recap (And for those who didn't want to read everything else)

  * `strtok` can be used to parse strings
  * function setup for `strtok`

  ```
  #include <string.h>
  char *strtok(char *str, const char *delim);
  ```
  * when continuing to parse the same string, `str` should be `NULL` in each subsequent call to `strtok`
  * if there is nothing left to parse, `strtok` returns `NULL`
  * rules of `delim`, the delimiter
    * this must always be specified when using `strtok`
    * is ignored when at the beginning or end of the `str` argument
    * `strtok` looks for the first occurrence of any character in `delim`, not the exact pattern that was
    passed in
  * strtok_r is used to parse multiple strings at once
  * function setup for `strtok_r`
  	
  ```
  #include <string.h>
  char *strtok_r(char *str, const char *delim, char **saveptr);
  ```
  * `strtok_r` follows the same rules as `strtok` with the addition of the `saveptr` argument
    * the `saveptr` argument keeps track of what is left after the first token is found

