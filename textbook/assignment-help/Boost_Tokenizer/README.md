The boost library `tokenizer` , takes a sequence such as a string, and parses it into tokens or substrings.  This makes life easier when you want to break up a string.  For example, you can take this string,

    string str = "Don't panic, too much."
 which will be broken up into the tokens:

    Don
    t
    panic
    too
    much

 Notice how the `'` `,`and the `.` were ignored.

**So how do we do this?** 
 First, in order to use the tokenizer we'll have to include the boost tokenizer library:
 

    #include <boost/tokenizer.hpp>
    using namespace boost;
    
Of course, this is assuming you have boost downloaded onto your computer.  If you're using the hammer.cs.ucr.edu server it's already there, but otherwise check out [boost.org's getting started guide](http://www.boost.org/doc/libs/1_57_0/more/getting_started/unix-variants.html).

So now that we have what we need, let's start coding.

    #include <iostream>
    #include <string>
    #include <boost/tokenizer.hpp>
    using namespace std;
    using namespace boost;
    
    int main() {
	    string str = "Don't panic, too much.";
	    tokenizer<> mytok(str);
	    for(auto it = mytok.begin(); it != mytok.end(); ++it)
		    cout << *it << endl;
		return 0;
	}
Once compiled we will get the output that was shown above where the `'` `,` and the `.` were ignored.  In this example, in order to call the tokenizer, we declare `tokenizer<> mytok(str)`, where `str` is the parameter that you want to parse, and `mytok` is the name of your tokenizer.  And don't worry about what goes in <>, we'll get to that later.

> Note: When compiling, you'll want to compile with `g++ -std=c++11` since we're using the `auto` feature that is included in the c++11 standard.  `auto`will automatically decide what data type your variable should be and since we have `auto it = tok.begin()`, `it` will become an iterator since `tok.begin() `returns an iterator.  
> 
> If your compiler doesn't handle c++11 then you would have to replace `auto` with `tokenizer<>::iterator it`. Typing that all out kind of sucks, so I suggest using `auto` because it's pretty useful.  Don't worry, if you're using the CS100 machines, c++11 should work. 
 
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

    string str = "CS&&&&100&is&really        amazing.";

This is where we'll have to declare our tokenizer a little differently.  The tokenizer will need to know that we want to use our own delimiter so this is where the `<>` comes in:

    typedef tokenizer< char_separator<char> > tok;

> Note: `typedef` is another useful tool that we can use to make declaring variables easier.  It's just a way to give a data type a new name.  Check out the [wiki page](http://en.wikipedia.org/wiki/Typedef) for `typedef` if you want to know more.

So notice how we put `char_separator<char>` So now that we have our `tok` data type declared, we need to make our delimiter.  The delimiter is that  new thing we put into our tokenizer: `char_separator<char>`.  So we declare this and give it a name:

    char_separator<char> delim("&");
Now, we can make our own tokenizer function.  However, making our own delimiter will require an extra parameter for our tokenizer function:

    tok mytok(str, delim);
where `mytok`is the name of our tokenizer, `str` is the thing we want to parse, and `delim` contains the stuff we want to ignore when parsing.
 
So let's see how this would work in code:

    #include <iostream>
    #include <boost/tokenizer.hpp>
    #include <string>
    using namespace std;
    using namespace boost;
    
    typedef tokenizer< char_separator<char> > tok;
    
    int main() {
	    string str = "CS&&&&100&is&really        amazing.";
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
Notice how even though there were multiple `&`'s, all of them were ignored.  But wait, this still isn't exactly what we wanted, because now it's not ignoring spaces.  Recall that our delimiter was:

    char_separator<char> delim("&");
We can actually put multiple characters into our delimiter.  So to get rid of spaces we would write: 

    char_separator<char> delim(" &");
 And so our output would look like:
 

    token: CS
    token: 100
    token: is
    token: really
    token: amazing.


Now this is something useful.  Remember, this is not ignoring *all* white space, so you'll have to type in the [ASCII character codes](http://www.petefreitag.com/cheatsheets/ascii-codes/) for other types of white space.  

So now we know that the delimiter can have multiple characters, but what about repeated characters? Turns out that it won't make a difference. So try `char_separator<char> delim(" &&&");` on your own if you don't believe us.

**Why is this better than strtok?**
If you haven't already looked, check out the [strtok tutorial](https://github.com/mikeizbicki/ucr-cs100/tree/2015winter/textbook/assignment-help/strtok) so that you can get a better understanding of it.  As with everything, there are always its pros and its cons, and you'll find that `strtok` might not be as intuitive as the boost tokenizer.  

In `strtok`, we have to pass in two parameters and from the other tutorial, we see that there's this whole issue with having to pass in `NULL` so as to continue parsing with the same string. However, with boost the entire string is already parsed and we use iterators to look through them.

`strtok` also cannot move backwards while tokenizing.  Once `strtok` is called, the substring before the token is dropped and cannot be accessed any more unless you pass in the original string again.

FIX ME: add summary?