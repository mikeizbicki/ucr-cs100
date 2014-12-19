Bitwise Operator Tutorial
===

Hey you! Yea, you! Do you want to learn about bitwise operators? Well, it doesn't matter what you want because you're going to learn them anyway!

Bitwise operators allow us to manipulate bits. At first, this might not seem useful, but you'll realize that there are a lot of system calls and functions that become a lot simpler when using bitwise operators. Also, you can store a lot of information if you utilize the individual bits of a value!  

[If you need a quick review of binary, click me!](http://www.mathsisfun.com/binary-number-system.html)

However, we will go over the octal and hexadecimal number systems, as they are commonly used alongside bitwise operators. 

### Table of Contents

 **[Practical Uses](#practical-uses)**<br> 
 **[Octal](#octal)**<br>
 **[Hexadecimal](#hexadecimal)**<br>

#####Bitwise Operators:<br>
 **[AND](#bitwise-and)**<br>
 **[OR](#bitwise-or)**<br>
 **[NOT](#bitwise-not)**<br>
 **[XOR](#bitwise-xor)**<br>
 **[Left-Shift](#bitwise-left\-shift)**<br>
 **[Right-Shift](#bitwise-right\-shift)**<br>

Practical Uses
---

We know why you're really here... you want to know what bitwise operators can be used for. Well look no further, we're going to slap you in the face with it first! But if I'm wrong, and you actually want to become the master of bitwise operators, feel free to come back to this section after learning about each operator! (Psst, use the table of contents. It's cool)

For those brave or foolish, prepare to get slapped.

#####fcntl.h
```
 #define O_RDONLY	0x0000
 #define O_WRONLY	0x0001
 #define O_RDWR		0x0002
 #define O_APPEND	0x0008
 #define O_CREAT	0x0200
```

The fcntl.h library contains macros for open and fcntl. Many of the macros allow us to manipulate files. For example, using O_RDONLY in the open function opens the file with only read permissions.

[Take a look at the source code!](http://unix.superglobalmegacorp.com/Net2/newsrc/sys/fcntl.h.html)

#####errno.h
```
 #define ENOENT		2
 #define EBADF		9
 #define EACCES		13
 #define ENOTDIR	20
```

The errno.h library holds a ton for macros used for errno! That way, you can utilize bitwise operators to tell exactly which error caused a system call to fail!

[There are a lot more error macros!](http://unix.superglobalmegacorp.com/Net2/newsrc/sys/errno.h.html)

#####sys/stat.h
```
 #define S_IRUSR	0000400
 #define S_IWUSR	0000200
 #define S_IXUSR	0000100
 #define S_IFDIR	0040000
 #define S_IFLNK	0120000
```

The macros in sys/stat.h are used in the system calls stat, fstat, and lstat. Many of these macros help us determine what type of file we are stat-ing. For example, we can use S_IRUSR to see if the user has read permissions for the file.

[These will definitely be useful in the future!](http://unix.superglobalmegacorp.com/Net2/newsrc/sys/stat.h.html) (wink wink)

As you may have noticed in the snippets of the libraries, these macros are simply just numbers. So, by using bitwise operators, we are able to store many many flags into a single int value. Theoretically, we could achieve the same results by memorizing the values for each flag/macro! However, by creating these macros and using the bitwise operators, we can use the necessary values with greater convenience. 

Check out these macros in action!

```
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <errno.h>
 
 //Other necessary code

 int fd = open("testfile", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

   /*
   Through the use of bitwise OR operator, we are able to combine macros together
   into a single value, which we then pass into open
   
   Similarly, for the third parameter, we are able to OR two different macros
   together to pass into the file
   */

 if (fd == -1) //Open fails
 {
 	if ((errno & EACCES) != 0) // errno contains EACCES
	//This bitwise & allows us to check if errno contains the EACCES flag
	{
		perror("open");
	}
	//Other errors
 }
 errno = 0;

 //Other code
 if (fstat(fd, &buf) == -1)
 {
 	if (errno & EBADF) //If fd is invalid - which means open failed
	//This bitwise & allows us to check if errno has the EBADF flag
	{
		perror("fstat");
	}
	//Other errors
 }

 //Other code 
``` 

Now that we've given you a taste of the possibilities, lets get to the basics!

Octal
---

Octal is the base-8 number system, which means its digits can only have 8 different values, ranging from 0 to 7. This means that whenever a digit exceeds 7, we must carry over the value to the next digit. 

For example: 

```
   17
 +  1
 ----
   20
```

To find the decimal equivalent, you would need to multiply the value of each digit by 8<sup>n</sup>, where n represents which digit it is. (N starts at 0 and counts from the right)

```
 Given 084,
 8 * 8^1 + 4 * 8^0 = 68
 Therefore, 084 = #68.
```

Note that to denote an octal value, we precede it with `0`!
Also, recall that we can represent decimal values by preceding it with `#`

Hexadecimal
---

Hexadecimal is a little more difficult to see, compared to decimal, octal, and binary. Hexadecimal is the base-16 number system. Now, you might be wondering what we use to to represent values past 9. Well it's simple, really - hexadecimal values range from 0-F. That's right! We use the first 6 letters of the alphabet! Here are a couple of examples of hex math:

```
	  x9		  xA		  x1F 
	+ x1		+ x3		+ x11
	----		----		-----
	  xA		  xD		  x30
```

Note that to represent a hexadecimal value, we precede it with an `x`!

<TABLE WIDTH="100%">
	<TR>
		<TH COLSPAN="11">
			<H4>Number equivalents</H4>
		</TH>
	</TR><TR>
		<TH>Decimal</TH>
		<TD>0</TD>
		<TD>1</TD>
		<TD>2</TD>
		<TD>8</TD>
		<TD>10</TD>
		<TD>16</TD>
		<TD>84</TD>
		<TD>160</TD>
		<TD>234</TD>
		<TD>400</TD>
	</TR><TR>
		<TH>Binary</TH>
		<TD>0</TD>
		<TD>1</TD>
		<TD>10</TD>
		<TD>1000</TD>
		<TD>1010</TD>
		<TD>10000</TD>
		<TD>1010100</TD>
		<TD>10100000</TD>
		<TD>11101010</TD>
		<TD>110010000</TD>
	</TR><TR>
		<TH>Octal</TH>
		<TD>0</TD>
		<TD>1</TD>
		<TD>2</TD>
		<TD>10</TD>
		<TD>12</TD>
		<TD>20</TD>
		<TD>128</TD>
		<TD>240</TD>
		<TD>352</TD>
		<TD>620</TD>
	</TR><TR>
		<TH>Hexadecimal</TH>
		<TD>0</TD>
		<TD>1</TD>
		<TD>2</TD>
		<TD>8</TD>
		<TD>A</TD>
		<TD>10</TD>
		<TD>54</TD>
		<TD>A0</TD>
		<TD>EA</TD>
		<TD>190</TD>
	</TR>
</TABLE>
		
Bitwise AND
---

The bitwise AND operator is a single ampersand: `&`. Bitwise AND works the same way the logical AND works! However, rather than operating only two boolean variables, the bitwise AND operates on every bit pair between the two given values!

The usage of bitwise AND is:

```
expression & expression
```

The truth table for the AND operation is:

			
<TABLE ALIGN="center">
	<TR>
		<TH>a</TH>
		<TH>b</TH>
		<TH>a  &  b</TH>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>0</TD>
		<TD>0</TD>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>1</TD>
		<TD>0</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>0</TD>
		<TD>0</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>1</TD>
		<TD>1</TD>
	</TR>
</TABLE>
			
For example, lets bitwise AND the decimal values 5 and 9!

```
    #5 & #9 //Convert both to bits!

    0101  // 5
 &  1001  // 9
 -------
    0001  //And change it back!
    = 1

```

Thus, `#5 & #9 = #1`. Pretty simple right? There isn't much to bitwise AND other than what we've already talked about, so you can safely say that you know how to bitwise AND two values together!


I know what you're thinking! "This is really exciting and I can't wait to keep learning more about bitwise operations!" That's really great to hear because we still have five more operators. Woohoo the fun doesn't end!

Bitwise OR
---

The bitwise OR operator is a single pipe: `|`. And just like with bitwise AND, bitwise OR functions in the same way logical OR does, only it compares each bit between the two values.

The usage of bitwise OR is:

```
expression | expression
```

The truth table for the OR operation is:

<TABLE>
	<TR ALIGN="center">
		<TH>a</TH>
		<TH>b</TH>
		<TH>a | b</TH>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>0</TD>
		<TD>0</TD>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>1</TD>
		<TD>1</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>0</TD>
		<TD>1</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>1</TD>
		<TD>1</TD>
	</TR>
</TABLE>

Now, let's use the bitwise OR operator on a pair of octal values!

```
    074 | 064 

    First, convert these values into bits!

    111 100
  | 110 100		
  ---------
    111 100

    //Now, converting it back to octal:
    = 074
    Therefore, 074 | 064 = 074!
```

Bitwise NOT
---

The bitwise NOT operator is a single tilde: `~`. Bitwise NOT looks at the binary representation of the expression and negates each bit value. This means that all bits with the value 0 become 1, and all bits with the value 1 become 0.

The usage of bitwise NOT is:

``` 
~expression
```

The truth table for the NOT operation is:

<TABLE ALIGN="center">
	<TR ALIGN="center">
		<TH>a</TH>
		<TH>~a</TH>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>1</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>0</TD>
	<TR>
</TABLE>

For example, if we select hexadecimal A1, the process should look like:

```
	~(xA1) //Convert this to bits!

	~ 1010 0001
	-----------
	  0101 1110 // And convert it back!
	
	= x5E
	Therefore, ~(xA1) = x5E!
```

When doing bitwise NOT of 7, we get the number -8. This happens because in the computer, binary numbers are read as 2's complement numbers. This means that, instead of every number being positive, the sign of the number is determined by the leftmost bit: 1 means negative and 0 means positive. However, we won't ever have to worry about 2's complement in most cases 

You're not dead from all this excitement are you? Good! This is the halfway point! Congrats on being excited all the way up until this point!

Bitwise XOR
---

The bitwise exclusive OR operator `^` - get it? EXclusive OR. XOR! - compares each bit between the two given operands, returning 1 only when one of the compared bits equals 1.

The bitwise XOR expressions looks like:

```
expression ^ expression
```

The truth table for the XOR operation is:

<TABLE ALIGN="center">
	<TR ALIGN="center">
		<TH>a</TH>
		<TH>b</TH>
		<TH>a ^ b</TH>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>0</TD>
		<TD>0</TD>
	</TR><TR ALIGN="center">
		<TD>0</TD>
		<TD>1</TD>
		<TD>1</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>0</TD>
		<TD>1</TD>
	</TR><TR ALIGN="center">
		<TD>1</TD>
		<TD>1</TD>
		<TD>0</TD>
	</TR>
</TABLE>

Looks like it's time for another example! Lets perform the XOR operation on 015 and 023!

```
    015 ^ 023 //Ah yes, time to convert to bits again!

    001 101
  ^ 010 011
  ---------
    011 110 //And convert it back! Woohoo!
    = 036

    Therefore, 015 ^ 023 = 036!
```

Bitwise Left-shift
---

The left-shift operator shifts the bits of the operand a number of times to the left. This number is determined by the value the user passes in. Sounds a little bit confusing right? Don't worry, it's not actually that complicated! Also, we'll provide some visual examples later in this section.

The bitwise left-shift expression looks like:

```
expression<<value
```

Now, let's do the operations on the 8-bit representation of 1! Remember what the 8-bit representation for 1 is? That's okay you can scroll all the way back up to find out! But because we're nice guys, we'll show it right here: '0000 0001'. You're welcome. Anyway, let's see what shifting left once looks like:

```
 Given 0000 0001 (1)
 1<<1 evaluates to
 0000 0010 (2)
```

Notice how that one bit on the far right moved to the left? And then a 0 was added to where it once was? That's how left shifting works! Let's do some more examples!

```
 Base Value: 1 = 0000 0001
 1<<0 = 0000 0001 (1) That's right! You can still left-shift by 0! 
 1<<2 = 0000 0100 (4)
 1<<3 = 0000 1000 (8)
 1<<4 = 0001 0000 (16)
 .
 .
 .
 1<<7 = 1000 0000 (128)
```

There we go. Super simple right? Also notice how the values are doubling? That's what left-shifting essentially does! It doubles the size of your value! Of course, this operator doesn't have much value in C++, as we can just multiply by two. But it's nice to have in mind!

If you're tired, don't worry! You're in the home stretch!

Bitwise Right-Shift
---

The right-shift operator works in the same way the left-shift operator does, only in the complete opposite direction! That means, you guessed it, it shifts all the bits to the right! And, since it's shifted the other way, it means that the values get divided by two! Bring out the examples!

The syntax for the right-shift operator is nearly the same as the left-shift one too:

```
expression>>value
```

And here's some right-shift in action:

```
 Base Value: 128 = 1000 0000
 128>>0 = 1000 0000 (128)
 128>>1 = 0100 0000 (64)
 128>>2 = 0010 0000 (32)
 128>>3 = 0001 0000 (16)
 .
 .
 .
 128>>7 = 0000 0001 (1)
```

Conclusion
---

You've finally made it! You now know about all the bitwise operators! While you may not be comfortable with octal, hexadecimal, and the operators yet, don't worry! There's a lot of time to get used to them through practice, such as doing sample calculations like we did in our examples. Also, test a lot of these operators in whatever IDE you'd like and output them! That way you can see them in action yourself! (Don't forget that the output is usually in decimal though!)

Hope you enjoyed this tutorial! If you didn't, oh well too bad! 
