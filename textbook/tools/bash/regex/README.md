#Regular Expressions


This is a general overview on regular expressions, commonly shortened to "regex".

This tutorial will cover the basics of regex, but more specifically, **POSIX regex**.

If you would like to practice regex, we have developed a tool for you to use. Check [down below](#practice).

<a name="top"/>
##Table of Contents
[1. What is it?](#what)    
[2. Regex Practice program](#practice)    
[3. Basic characters/Literal characters](#literal)    
[4. Special/Metacharacters](#meta)    
[5. Escaped literals](#escaped)    
[6. POSIX specific syntax](#posix)    
[7. Additional resources](#resources)    

<a name="what"/>
###What is Regex?

A regular expression is a pattern of letters and symbols which can represent a search pattern. The most common usage is using this search pattern to search through strings in a document or files. For example, if you wanted to find all the emails in a webpage, regex would be a good solution to use to quickly parse all the text on the page. Depending on the environment these strings are parsed in, you can match multiple instances or a single instance of a pattern. Regular regex returns the **first** matching string that it finds. Regex is most commonly used for searching and replacing string patterns, and while this may not be the only use, it is very powerful because of the syntax behind regex.

One of the many uses of regex is pattern matching for `sed` and `grep`, two Linux commands for which are used for searching and replacing text or just searching for strings respectively.

[Back to table of contents](#top)

<a name="practice"/>
##Regex Practice
Our practice program is [located here](http://github.com/Liniarc/regexProgram). Instructions for running this practice program is located in that repository.

[Back to table of contents](#top)

<a name="literal"/>
###Basic Characters aka Literal Characters

Any letter or character `a-z`, `A-Z`, `0-9` by itself will match a single instance of that character. There are a few extra symbols which do not follow this rule but we'll get to that in a bit.

####Example
<table>
 <tr>
  <th>Example</th>
 </tr>
 <tr>
  <td><pre><code>$ echo 'cat patch dog' | grep 'a'
c<em><strong>a</em></strong>t p<em><strong>a</strong></em>tch dog</code></pre></td>
 </tr>
</table>

See also: [Literal Characters](http://www.regular-expressions.info/characters.html)

[Back to table of contents](#top)

<a name="meta"/>
###Special Characters aka Metacharacters

These characters are special and cannot be used to match for that character. However, if you need to match the literal character you need to use an escape character, `\`, in front of the metacharacter.

See also: [Special Characters](http://www.regular-expressions.info/characters.html)

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'Array[5]' | grep '\['
Array<strong><em>[</em></strong>5]</code></pre>
    </td>
    <td>
    <pre><code>$ echo 'C:\Windows' | grep '\\'
C:\Windows
C:<strong><em>\</em></strong>Windows</code></pre>
    </td>
  </tr>
</table> 

Here are all the metacharacters:
<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>\^$.*[]</code></pre>
    </td>
    <td>
    <pre><code>\^$.|?*+()[]{}</code></pre>
    </td>
  </tr>
</table> 

+ `\` - The escape character. You'll need it if you want to match the literal character for all of the next few symbols.

+ `[ ]` - Indicates a group of characters to match. Adding a `^` in front of the characters indicates not those characters.

<table>
  <tr>
    <th>Example</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'pan fan tan man par tap fat' | grep '[pft]a[^rtp]'
<strong><em>pan fan tan</em></strong> man par tap fat</code></pre>
    </td>
  </tr>
</table>  

NOTE: The brackets can use ranges, which is what they are commonly used for.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'abcdefgABCDEFG' | grep '[A-Z]'
abcdefg<strong><em>ABCDEFG</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ echo '012345678abcdefghi' | grep '[2-5c-g]'
01<strong><em>2345</em></strong>678ab<strong><em>cdefg</em></strong>hi</code></pre>
    </td>
  </tr>
</table>   

See also: [POSIX brackets](http://www.regular-expressions.info/posixbrackets.html)    
See also: [Character classes](http://www.regular-expressions.info/charclass.html)

+ `.` - The period, or dot, matches any character.

<table>
  <tr>
    <th>Example 1</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'abcDEF123!@#[]' | grep '.'
<strong><em>abcDEF123!@#[]</em></strong></code></pre>
    </td>
  </tr>
</table>

See also: [The dot](http://www.regular-expressions.info/dot.html)

+ `^` - The caret matches at the beginning of a string or line.  `$` - The dollar sign matches at the end of a string or line.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'heavyhanded' | grep '^he'
<strong><em>he</em></strong>avyheaded</code></pre>
    </td>
    <td>
    <pre><code>$ echo 'successful success' | grep 'cess$'
successful suc<strong><em>cess</em></strong></code></pre>
    </td>
  </tr>
</table>

See also: [Anchors](http://www.regular-expressions.info/anchors.html)

+ `*` - Indicates **zero or more repetitions** of a character (or group). `+` - Indicates **one or more repetitions** of a character (or group).

<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'shell fees' | grep 'el*s'
sh<strong><em>ells</em></strong> fe<strong><em>es</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ echo 'hi this hiss' | egrep 'is+'
hi th<strong><em>is</em></strong> h<strong><em>iss</em></strong></code></pre>
    </td>
  </tr>
</table>

See also: [Repeating character classes](http://www.regular-expressions.info/charclass.html)

+ `?` - Indicates an optional character (or group). It is extended posix only. Use `\{0,1\}` in standard posix.

<table>
  <tr>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo | 'color colour' egrep 'colou?r'
<strong><em>color colour</em></strong></pre>
    </td>
  </tr>
</table>

See also: [Repeating character classes](http://www.regular-expressions.info/charclass.html)

+ `|` - The pipe. Or logical OR. Best used inside of `(` and `)`. You must escape these in standard Posix, but not in extended Posix.
<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'I like cats and dogs' | grep 'cat\|dog'
I like <strong><em>cat</em></strong>s and <strong><em>dog</em></strong>s</code></pre>
    </td>
    <td>
    <pre><code>$ echo 'today or tomorrow' | egrep 'to(day|morrow)'
<strong><em>today</em></strong> or <strong><em>tomorrow</em></strong>
    </td>
  </tr>
</table>

See also: [Alternation](http://www.regular-expressions.info/alternation.html)

+ `{ }` - A specified number of repetitions

`{n}` - Matches exactly n repetitions    
`{n,}` - Matches n or more repetitions    
`{n, m}` - Matches no more than `m` repetitions but no less than `n` repetitions    
The brackets must be escaped in standard regex.

<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'wee' | grep 'we\{3\}'
<em><strong>weee</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ echo 'yaaaay' | egrep 'ya{2,5}y'
<em><strong>yaaaay</em></strong></code></pre>
    </td>
  </tr>
</table>

See also:

+ `(` and `)` - Captures variables and creates character groups.    
The parenthesis must be escaped in standard Posix

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'Image012.jpg' | grep '\(.*\)\.jpg'
<em><strong>Image012.jpg</em></strong>
#Image012 is in capture group 1</code></pre>
    </td>
    <td>
    <pre><code>$ echo 'a1a2a3' | egrep '(a.)+'
<em><strong>a1a2a3</em></strong></code></pre>
    </td>
  </tr>
</table>

See also: [Grouping](http://www.regular-expressions.info/brackets.html)

+ `\n` - refers back to the nth capture group. This does not exist in Extended Regex.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'abc abc' | grep '\(...\) \1'
<em><strong>abc abc</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ echo 'ago ag a OR amend amen men' | grep '\(a\(.+\)\)d \1 \2'
<em><strong>ago ag a</em></strong> OR <em><strong>amend amen men</em></strong></code></pre>
    </td>
  </tr>
</table>


<table>
  <tr>
    <th>sed Example</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo '"head" "body"' | sed 's/"\([^"]*\)"/&lt;\1>/g'
&lt;head> &lt;body></code></pre>
    </td>
  </tr>
</table>

See also: [Backreferences](http://www.regular-expressions.info/backref.html)

[Back to table of contents](#top)

<a name="escaped"/>
###Table of Character classes

These are used to indicate special characters or characteristics. They work in conjunction with bracket expressions, so you need to add a second set of bracket around them. **These are POSIX specific.**

   Symbol     | Explanation
--------------|-------------
 `[:alnum:]`  |  Any letter or number
 `[:alpha:]`  |  Any letter
 `[:digit:]`  |  Any number
 `[:upper:]`  |  Any uppercase letter
 `[:lower:]`  |  Any lowercase letter
 `[:punct:]`  |  Any punctuation character
 `[:space:]`  |  Any whitespace character
 
 <table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ echo 'abcABC123' | grep '[[:alpha:]]*'
<em><strong>abcABC</em></strong>123</code></pre>
    </td>
    <td>
    <pre><code>$ echo '0xA13F98B' | grep '0x[[:digit:]A-F]*'
<em><strong>0xA13F98B</em></strong></code></pre>
    </td>
  </tr>
</table>

 See also: [Free-spacing](http://www.regular-expressions.info/freespacing.html)

[Back to table of contents](#top)

<a name="posix"/>
##POSIX Specific Syntax

There are a few key differences POSIX standard says that the **longest** match is returned. Normal regex usually stops with the **first** match found. However, it will still match the **leftmost** result.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
Match: GetStatus<br>
String: GetStatus Get<br>
Use: <code>Get</code><br>
Result: <em><strong>GetStatus</strong></em> Get   
    </td>
    <td>
Match: SetStatus<br>
String: Set SetStatus<br>
Use: <code>(Set|SetStatus)</code><br>  
Result: Set <strong><em>SetStatus</em></strong>
    </td>
  </tr>
</table> 


See also: [POSIX](http://www.regular-expressions.info/posix.html)

[Back to table of contents](#top)

<a name="resources"/>
##Additional Resources
http://regexone.com is an excellent learning tool which provides an interactive tutorial which walks through the basics of regex.    
http://www.regular-expressions.info has many pages dedicated to both quickly learning regex and POSIX specific regex. This resource has also been linked throughout this document.

[Back to table of contents](#top)


