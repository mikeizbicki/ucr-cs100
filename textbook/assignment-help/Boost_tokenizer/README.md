The boost library `tokenizer` , takes a sequence such as a string, and parses it into tokens or substrings.  For example, you can take this string,

    string str = "Don't panic, too much."
 which will be broken up into the tokens:

    Don
    t
    panic
    too
    much

 Notice how the `'` `,`and the `.` were ignored.

**So how do we do this?** 
 First, in order to use the tokenizer we'll have to declare a few things:
 

    #include <boost/tokenizer.hpp>
    using namespace boost;
    
So now that we have what we need, let's start coding.

    #include <iostream>
    #include <string>
    #include <boost/tokenizer.hpp>
    using namespace std;
    using namespace boost;
    
    int main() {
	    string str = "Don't panic, too much.";
	    tokenizer<> tok(str);
	    for(auto it = tok.begin(); it != tok.end(); ++it)
		    cout << *it << endl;
		return 0;
	}
Once compiled we will get the output that was shown above where the `'` `,` and the `.` were ignored.  In this example, in order to call the tokenizer, we declare `tokenizer<> tok(str)`, where `str` is the parameter that you pass in, and `tok` is the name of your tokenizer.  And don't worry about what goes in <>, we'll get to that later.

> Note: When compiling, you'll want to compile with `g++ -std=c++11` since we're using the `auto` feature that is included in the c++11 standard.  `auto`will automatically decide what data type your variable should be and since we have `auto it = tok.begin()`, `it` will become an iterator since `tok.begin() `returns an iterator.  
> 
> If your compiler doesn't handle c++11 then you would have to replace `auto` with `tokenizer::iterator it`. Typing that all out kind of sucks, so I suggest using `auto` because it's pretty useful.
 
So here's another example of tokenizer to really drive it home:

    #include <iostream>
    #include <string>
    #include <vector>
    #include <boost/tokenizer.hpp>
    using namespace std;
    using namespace boost;
    
    int main() {
	    string str = "I'm getting pretty good at this.";
	    vector<string> v;
	    tokenizer<> tok(str);
	    
	    for(auto it = tok.begin(); it != tok.end(); ++it) {
		    v.push_back(*it);
		    cout << *it << ' ';
		}
		cout << endl;
	    return 0;
	}
The output for this will be:

    I m getting pretty good at this
You should have a feel for how the boost tokenizer works by now, but this doesn't seem very useful since it's parsing your string like this.  By default, the tokenizer will ignore white space and non-letter/number characters.  But we can control what the tokenizer ignores by defining something which is known as the *delimiter.*

**So what's a delimiter and why is it useful?**
A delimiter is a set of one or more characters that separate text.  We can specify what our delimiter is for the tokenizing function so that we can control how our string will get parsed.

So here's another example we can work with:

    string str = "CS&100&is&really        amazing.";

This is where we'll have to declare our tokenizer a little differently.  The tokenizer will need to know that we want to use our own delimiter so we first start by defining:

    typedef tokenizer< char_separator<char> > tok;

> Note: `typedef` is another useful tool that we can use to make declaring variables easier.  For example, we might want to record data for the mpg of different cars and we could declare variables:
> `int mpg_2001BMW;
> int mpg_2007Honda;`
> Instead, we could declare `typedef int mpg` where mpg is just another name for the data type `int`. So now we can have:
> `mpg 2001BMW;
> mpg 2007Honda;`
This is pretty much what we're doing with the `typedef` for `tok`. We just don't want to keep typing that long definition all the time.

So now that we have our `tok` declared, we need to make our delimiter.  The delimiter is that new thing we put into our tokenizer: `char_separator<char>`.  So we declare this and give it a name:

    char_separator<char> delim("&");
So let's see how this would work in code:

    #include <iostream>
    #include <boost/tokenizer.hpp>
    #include <string>
    using namespace std;
    using namespace boost;
    
    typedef tokenizer< char_separator<char> > tok;
    
    int main() {
	    string str = "CS&100&is&really        amazing.";
	    char_separator<char> delim("&");
	    tok mytok(str, delim);
	    
	    for(auto it = mytok.begin(); it != mytok.end(); ++it) 
		    cout << "token: " << *it << endl;
	
	    return 0;
	}
Output:

    token: CS
    token: 100
    token: is
    token: really        amazing.

Woah, so what in the world is going on!

(FIX ME!
Stuff to add:
	-explain this code, what exactly is going on
	-go over multi-character delimiters