## Introduction to Bitwise Operators

Hey you! Yea, you! Do you want to learn about bitwise operators? Well, it doesn't matter what you want because you're going to learn them anyway! And do you know why? It's so you can do stuff like this:

```
 int fd = open("filename", O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
```
Whoa what's the vertical bar thing? That's the bitwise `OR` operator, one of the bitwise operators you will learn about! Here, we pass in multiple flags to the `open` [system call](http://linux.die.net/man/2/open). "But it only takes in 2 `int` values. How did you pass in more than one flag/macro each?" The secret is the `OR` operator: the `OR` operator combines the flags into one value that we then pass in.

But wait! Did you notice how `open` had `int` parameters? That's right, these flags and macros are nothing more than a bunch of integers! This means that we could actually just memorize the number for every single flag combination in every library. Then we wouldn't need to use bitwise operators! Of course, that's super impractical, which is why we have the bitwise operators. We just need to look up the macro names, and the bitwise operators can take care of the rest, no memorization needed. Let's get started!

For bitwise operators, you're going to need more than just the regular decimal
counting system. We'll assume you already know binary, but if you need a guide
or refresher on binary, click  [here!](http://www.mathisfun.com/binary-number-system.html)
Although, binary is used in these bit calculations, we'll need to learn the octal and the hexadecimal number systems too.
Don't worry, we'll teach you those!

## Practical Uses

The two most used bitwise operator in C/C++ are the `OR` and `AND` operators, as the others are simply not as useful for accessing information. But we will still cover them just in case!

Earlier, we learned that `OR` is able to store multiple flags into a single value. Well, how useful would that be if we don't know what we actually stored right? That's why we have the `AND` operator! We can use `AND` to check if a value contains a certain flag, like so:

```c++
 #include <fcntl.h>
 #include <sys/stat.h>

 struct stat buf;
 int fd = open("filename", O_RDONLY);
 if (fstat(fd, &buf) == 0)
 {
 	if (buf.st_mode & S_IFDIR)
	{
		cout << "filename is a directory" << endl;
	}
 }
```
Here, we want to check if `filename` is a directory or not, which we can used the macro `S_IFDIR` to do. Utilizing bitwise `AND`, we are able to see if the value holding all the flags, `buf.st_mode`, contains `S_IFDIR`. If it does, then we know it's a directory!

Of course, we'll go more into detail on `AND` later on, but hopefully you've grasped that bitwise operators aren't something that you'll stop using.
As long as you're coding in C/C++, you're bound to use these operators often!

Before we go on to how these operators work on different number systems, we'll discuss a way to organize our numbers.

## Digit Separators
Digit separators are a small addition to the C++ standard introduced in C++14.
A single-quote character can be used arbitrarily as a digit separator in numeric literals.
For example it can be used to separate digits into thousands:
```c++
auto int_lit = 1000000;             // this is an example of an integer literal
									// with bo digit separators

auto int_lit_digseps = 1'000'000;   // this is the same number ad the one
									// but this one uses digit separators
```
Here, both `int_lit` and `int_lit_digseps` contain the same exact number only `int_lit_digseps` uses single quotes as digit separators and `int_lit` does not.


Digit separators work for floating point literals as well and, in general, work for all number literal types like octal, hex, and even binary numeral systems.
Below is an example of how digit separators can be used in floating point representations of numerals:
```c++
auto float_lit = 0.000153;
auto float_lit_digseps = 0.000'153;
```
And binary representations of numbers:
```c++
auto bin_lit = 0b010011000110;
auto bin_lit_digseps = 0b0100'1100'0110;
```

In general digit separators are intended to improve code readability they generally make numbers easier for human eyes to read since we are all used to seeing digits separated by thousands but they can be used arbitrarily and in no specific pattern.
For example:
```
auto tenmilli = 10000000;
auto tenmilli_digseps = 1'0'0'000'00;
```
Here, form of digit separating follows known convention for separating digits.
In General, Digit Separators are meant to improve aesthetic readability.
They do not affect the numeric value.

We'll be organizing all of our numbers in this write-up using the newly added C++14 digit separators in order to make the numbers easier to read.

## Binary Formats

#### Binary Literals

Binary literals specified using the prefixes `0b`or `0B` are now supported in the language.
These prefixes can be used interchangeably.
```c++
int AM = 0b11111001010;     // the number 1994 in binary using the 0b prefix
int CB = 0B11111000111;     // the number 1991 in binary using the 0B prefix
```
Not specifying the prefix will result in the compiler defaulting to decimal.
For example:
```c++
int x = 1101;
```
Since no prefix indicating a numeral system is specified, the value of `1101` defaults to decimal.
This means that x stores the value `1101` and not `13`
This applies to all numeral systems.

Binary literals can be used wherever an constant integral type is expected.
The following code compares two binary numbers:
```c++
cout << "100101 = " << 0b100101 << endl;
cout << "11001 = " << 0b11001 << endl;
if(0b100101 > 0b11001) {
	cout << "TRUE" << endl;
}
else {
	cout << "FALSE" << endl;
}
```
It prints to screen TRUE if the first is larger and FALSE otherwise.

#### Octal

Octal is the base-8 number system, which means its digits can only have 8 different values, ranging from 0 to 7. This means that whenever a digit exceeds 7, we must carry over the value to the next digit.

For example:

```
   17
 +  1
 ----
   20
```

To find the decimal equivalent, you would need to multiply the value of each digit by 8<sup>n</sup>, where n represents which digit it is. (N starts at 0 and counts from the right)

Note that to denote an octal value in C/C++, we precede it with `0`!

```
 Given 084,
 (8 * 8^1) + (4 * 8^0) = 68
 Therefore, 084 = 68.
```

Quick! Recall the example we showed with `AND`. Remember that it involved us using `AND` to search for the `S_IFDIR` flag? Well that flag is contained in the `sys/stat.h` library! Here's a snippet of that and some other flags defined:

```
 #define S_IFDIR 0040000
 #define S_IRUSR 0000400
 #define S_IWUSR 0000200
 #define S_IFREG 0100000
```

And would you look at that! They're octal values! Good thing we know how octal values work! And now, we understand how to read some of the flags set in our previous examples! But we have to learn about hexadecimal first, so let's put octal on hold.

#### Hexadecimal

Hexadecimal is a little more difficult to see, compared to decimal, octal, and binary. Hexadecimal is the base-16 number system. Now, you might be wondering what we use to represent values past 9. Well it's simple really - hexadecimal values range from 0-F. That's right! We use the first 6 letters of the alphabet! Here are a couple of examples of hex math:

Note that to represent a hexadecimal value in C++, we precede it with `0x`!
```
	  0x9		  0xA		  0x1F
	+ 0x1		+ 0x3		+ 0x11
	----		----		-----
	  0xA		  0xD		  0x30
```

And to convert it to a decimal number, we use the same method as in octal, only we multiply by 16<sup>n</sup> instead!

```
 Given 0x26
 (2 * 16^1) + (6 * 16^0) = 38
 Therefore, 0x26 = 38
```

Looking back at the two examples we gave for `OR` and `AND`, you can see we utilized the flags `O_WRONLY`, `O_APPEND`, and `O_RDONLY`. These flags are defined in the `fcntl.h` library. And guess what? They're actually hexadecimal values!

##### fcntl.h
```
 #define O_RDONLY	0x0000
 #define O_WRONLY	0x0001
 #define O_RDWR		0x0002
 #define O_APPEND	0x0008
 #define O_CREAT	0x0200
```
[Take a look at the other values!](http://unix.superglobalmegacorp.com/Net2/newsrc/sys/fcntl.h.html)

Right away, we've seen that there was a point to learning these number systems. We can read the bits of these values! This sets us up to be able to do the bitwise operations on these values, and we'll finally be able to know the full picture behind the two examples.

Here's a table of corresponding values:

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
		<TD>124</TD>
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

## Bitwise Operators

#### Bitwise OR

The bitwise OR operator is a single pipe: `|`. Bitwise OR functions in the same way logical OR does, only it compares each bit between the two values.

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

    First, let's use the binary representations:

    111'100
  | 110'100
  ---------
    111'100

    //Now, converting it back to octal:
    = 074
    Therefore, 074 | 064 = 074
```

That's the basics of Bitwise OR! Now, with that understood, let's look back at the very first line we gave you:
```
 int fd = open("filename", O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
```

Using the macros defined earlier (We'll rewrite them):
```
 #define O_WRONLY 0x0001
 #define O_APPEND 0x0008

    (O_WRONLY | O_APPEND) == (0x0001 | 0x0008)
    0001 //We can ignore the first 3 digits as they're just 0s and will
  | 1000 //just cause clutter
  ------
    1001
    = 0x0009

 #define S_IRUSR 0000400
 #define S_IWUSR 0000200

    (S_IRUSR | S_IWUSR) == (0000400 | 0000200)
    100'000'000
  | 010'000'000
  -------------
    110'000'000
    = 0000600
```

So, as our calculations show, we could actually rewrite our example as:
```
 int fd = open("filename", 0x0009, 0000600);
```
Like we mentioned earlier, we could just pass in these numbers. But that's a huge hassle, since we can just look up the names associated with each value and use `OR`. But now you've seen how the bitwise `OR` truly works with the flags!

#### Bitwise AND

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

For example, lets bitwise AND the decimal values 5 and 9:

```
    5 & 9 //Use & on their binary representations

    0101  // 5
 &  1001  // 9
 -------
    0001  //And change it back
    = 1
```

Thus, `5 & 9 = 1`. Pretty simple right? Good! Now let's try it on the example from before:
```
 if (buf.st_mode & S_IFDIR)
```
Let's assume that `buf.st_mode` has a value of 0100644. Now, using what we know about `S_IFDIR`:
```
    (buf.st_mode & S_IFDIR) == (0100644 & 0040000)
    001'000'000'110'100'100
  & 000'100'000'000'000'000
  ---------------------
    000'000'000'000'000
    = 0000000
```
We receive a resulting value of 0, our file is NOT a directory! However, can we determine what kind of file this is? Let's try a different macro this time:
```
    (buf.st_mode & S_IFREG) == (0100644 & 0100000)
    001'000'000'110'100'100
  & 001'000'000'000'000'000
  -------------------------
    001 000 000 000 000 000
    = 0100000
```
Would you look at that? The resulting value was not 0, meaning `buf.st_mode` contains this flag. And this flag tells us that it's just a simple regular file! Cool! (There are still other flags in `buf.st_mode`! See if you can figure out what they say!)

Phew, that's a lot of learning. I know what you're thinking. "This is really exciting and I can't wait to keep learning more about bitwise operations!" That's really great to hear because we still have four more operators. Woohoo the fun doesn't end!

#### Bitwise XOR

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

Looks like it's time for another example! Let’s perform the XOR operation on 015 and 023:
```
    015 ^ 023 //Ah yes, use their binary representations!

    001'101
  ^ 010'011
  ---------
    011'110 //And convert it back! Woohoo!
    = 036

    Therefore, 015 ^ 023 = 036!
```
There isn't much daily use for the `XOR` operator. However, as far as we've found, you can use it for encryption! In our previous example, `015 ^ 023` turned into `036`. What happens when we `XOR` it with `023`?
```
    036 ^ 023

    011'110
  ^ 010'011
  ---------
    001'101
    = 015
```
We got the same value as before! If you use `XOR` with the same value twice, you'll receive the value you originally had! So we could potentially `XOR` a value with many different numbers to encrypt them and then `XOR` them again to decrypt them! However, security systems generally use number encryptions instead of bit encryptions, so you won't find much use. But it's still good information to have!

#### Bitwise Leftshift

The left-shift operator shifts the bits of the operand a number of times to the left. This number is determined by the value the user passes in. Sounds a little bit confusing right? Don't worry, it's not actually that complicated! Also, we'll provide some visual examples later in this section.

The bitwise left-shift expression looks like:

```
expression<<value
```

Now, let's do the operations on the 8-bit representation of 1! Remember what the 8-bit representation for 1 is? That's okay you can scroll all the way back up to find out! But because we're nice guys, we'll show it right here: '0000 0001'. You're welcome. Anyway, let's see what shifting left once looks like:

```
 Given 0000'0001 (1)
 1<<1 evaluates to
 0000'0010 (2)
```

Notice how that one bit on the far right moved to the left? And then a 0 was added to where it once was? That's how left shifting works! Let's do some more examples!

```
 Base Value: 1 = 0000 0001
 1<<0 = 0000'0001 (1) That's right! You can still left-shift by 0!
 1<<2 = 0000'0100 (4)
 1<<3 = 0000'1000 (8)
 1<<4 = 0001'0000 (16)
 .
 .
 .
 1<<7 = 1000'0000 (128)
```

There we go. Super simple! Also notice how that values are doubling? That's what left-shifting essentially does! It doubles the size of your value! Of course, this operator doesn't have much value in C++, as we can just multiply by two. But it's nice to have in mind!

If you're tired, don't worry! You're on the home stretch!

#### Bitwise Rightshift

The right-shift operator works in the same way the left-shift operator does, only in the complete opposite direction! That means, you guessed it, it shifts all the bits to the right! And, since it's shifted the other way, it means that the values get divided by two! Bring out the examples!

The syntax for the right-shift operator is nearly the same as the left-shift one too:

```
expression>>value
```

And here's some right-shift in action:

```
 Base Value: 128 = 1000 0000
 128>>0 = 1000'0000 (128)
 128>>1 = 0100'0000 (64)
 128>>2 = 0010'0000 (32)
 128>>3 = 0001'0000 (16)
 .
 .
 .
 128>>7 = 0000'0001 (1)
```

## Conclusion

You've finally made it! You now know about all the bitwise operators! While you may not be comfortable with octal, hexadecimal, and the operators yet, don't worry! There's a lot of time to get used to them through practice, such as doing sample calculations like we did in our examples. Also, test a lot of these operators in whatever IDE you'd like and output them! That way you can see them in action yourself! (Don't forget that the output is usually in decimal though!)

Hope you enjoyed this tutorial!
