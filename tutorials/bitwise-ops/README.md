Bitwise Operator Tutorial
===

Hey you! Yea, you! Do you want to learn about bitwise operators? Well, it doesn't matter what you want because you're going to learn them anyway!

Bitwise operators allow programmers like you and I to manipulate bits, despite writing in a high-level language. At first, this might not seem useful, but you'll realize that there are a lot of system calls and functions that become a lot simpler when using bitwise operators (and we'll even show you a few of these functions). These operators are even useful for storing information, which we will also give examples for).

If you don't understand what binary numbers are, or you need a quick review, head down to the **Binary Numbers** section just below! Otherwise, just skip straight to the operators!

Binary Numbers
---

If you're already familiar with counting in binary, feel free to skip this section!

Welcome to Binary 101! Today, we are going to talk about binary numbers! Binary numbers are composed of binary digits, just like decimal numbers - the counting system we use normally - are made up of decimal digits! However, there is one key difference: binary digits can only be either 0 or 1, while decimal digits can be any number between 0-9!

Here are a few examples to help out with visualizing counting in binary:

```
 0 = 0
 1 = 1
```

The first two are easy! They're just the same! But this next part is where things get a *bit* hairy.

```
 2 = 10
```

Wait what? 2 = 10? This guy must be nuts! 
This might look weird if it's your first time with binary, but it's really quite simple. Remember how, in adding two decimal numbers, you would carry over to the next digit if it went over 9? This is the exact same thing, only that you have to carry it over if the digit goes over 1! So if you were to add two binary digits equal to 1:

```
     1
 +   1
 -----
    10
```

Notice how the bit carried over? That was the most complicated part. Everything else behaves in exactly the same way.

```
 3 = 11
 4 = 100
 5 = 101
 6 = 110
 7 = 111
 8 = 1000
```

And so on! Congratulations! You're at the end of Binary 101! On to the operators!

Bitwise AND
---

The bitwise AND operator is a single ampersand: `&`. Bitwise AND works the same way the logical AND works! However, rather than operating only two boolean variables, the bitwise AND operates on every bit pair between the two given values!

The usage of bitwise AND is:

`expression & expression`

The truth table for the AND operation is:

```
 |---------------------------|
 |   a   |   b   |  a  &  b  |
 |---------------------------|
 |   0   |   0   |     0     |
 |---------------------------|
 |   0   |   1   |     0     |
 |---------------------------|
 |   1   |   0   |     0     |
 |---------------------------|
 |   1   |   1   |     1     |
 |---------------------------|
```

For example, we select two integers 5 and 9 and use AND on them.
First, we will need to convert the two into binary:

```
 0 1 0 1  // 5
 1 0 0 1  // 9
```

The bitwise AND works by comparing each column of bits. It may be more helpful if you think of the 0 as FALSE and the 1 as TRUE.

```
    0 1 0 1  // 5
 &  1 0 0 1  // 9
 ----------
    0 0 0 1  // 1
```

Thus, `5 & 9 = 1`. Pretty simple right? There isn't much to bitwise AND other than what we've already talked about, so you can safely say that you know how to bitwise AND two values together!


I know what you're thinking! "This is really exciting and I can't wait to keep learning more about bitwise operations!" That's really great to hear because we still have five more operators. Woohoo the fun doesn't end!

Bitwise OR
---

The bitwise OR operator is a single pipe: `|`. And just like with bitwise AND, bitwise OR functions in the same way logical OR does, only it compares each bit between the two values.

The usage of bitwise OR is:

`expression | expression`

The truth table for the OR operation is:

```
 |---------------------------|
 |   a	 |   b   |  a  |  b  |
 |---------------------------|
 |   0   |   0   |     0     |
 |---------------------------|
 |   0   |   1   |     1     |
 |---------------------------|
 |   1   |   0   |     1     |
 |---------------------------|
 |   1   |   1   |     1     |
 |---------------------------|
```

Now, let's use the bitwise OR operator on a pair of values!

```
    0 1 0 1 // 5
 |  0 0 1 1 // 0
 -----------
    0 1 1 1 // 7
```

Bitwise NOT
---

The bitwise NOT operator is a single tilde: `~`. Bitwise NOT looks at the binary representation of the expression and negates each bit value. This means that all bits with the value 0 become 1, and all bits with the value 1 become 0.

The usage of bitwise NOT is:

` ~expression `

The truth table for the NOT operation is:

```
 |---------------|
 |   a   |  ~a   |
 |---------------|
 |   0   |   1   |
 |---------------|
 |   1   |   0   |
 |---------------|
```

When bitwise NOT acts on an operand of an integral data type, it performs no coercion and returns a value of the same data type as the operand.

For example, if we select an integer 7, the process should look like:

```
 ~  0 1 1 1  // 7
 -----------
    1 0 0 0  // -8
```

When doing bitwise NOT of 7, we get the number -8. This happens because in the computer, binary numbers are read as 2's complement numbers. This means that, instead of every number being positive, the sign of the number is determined by the leftmost bit: 1 means negative and 0 means positive. However, since C++ is a high level language, you don't need to worry too much about the 2's complement. 

You're not dead from all this excitement are you? Good! This is the halfway point! Congrats on being excited all the way up until this point!

Bitwise XOR
---

The bitwise exclusive OR operator `^` - get it? EXclusive OR. XOR! - compares each bit between the two given operands, returning 1 only when neither of the compared bits is 1. 

The bitwise XOR expressions looks like:

`expression ^ expression`

The truth table for the XOR operation is:

```
 |---------------------------|
 |   a	 |   b   |  a  ^  b  |
 |---------------------------|
 |   0   |   0   |     1     |
 |---------------------------|
 |   0   |   1   |     0     |
 |---------------------------|
 |   1   |   0   |     0     |
 |---------------------------|
 |   1   |   1   |     0     |
 |---------------------------|
```

Bitwise Left-Shift
---

The left-shift operator shifts the bits of the operand a number of times to the left. This number is determined by the value the user passes in. Sounds a little bit confusing right? Don't worry, it's not actually that complicated! Also, we'll provide some visual examples later in this section.

The bitwise left-shift expression looks like:

`expression<<value`

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

There we go. Super simple right? Also notice how that values are doubling? That's what left-shifting essentially does! It doubles the size of your value! Of course, this operator doesn't have much value in C++, as we can just multiply by two. But it's nice to have in mind!

If you're tired, don't worry! You're on the home stretch!

Bitwise Right-Shift
---

The right-shift operator works in the same way the left-shift operator does, only in the complete opposite direction! That means, you guessed it, it shifts all the bits to the right! And, since it's shifted the other way, it means that the values get divided by two! Bring out the examples!

The syntax for the right-shift operator is nearly the same as the left-shift one too:

`expression>>value`

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

Same exact concept as the left-shift operator. And that's all there is to it! We've covered the bitwise operators! You're at the almost finish line! There's still one more section left...

Practical Uses
---

Under construction!








