#escaped_list_separator

If you have not yet read the [Boost Library Tokenizer tutorial](README.md), please read it before continuing.

The `escaped_list_separator` class is a TokenizerFunction class that separates a string into fields. 
The default separator is the `,` character, but you can choose to have different separators or more separators.

If you would like to keep a separator character in a field, rather than have it act as a separator, you should put quotes around the substring in which you would like to keep the separators.
The default quote character is the `"` character; however, just like separator characters, you can change the quote characters.

Finally, the escape character helps you interpret another character differently. 
By default, this character is `\`.
In the `escaped_list_separator` class, there are three different ways to use the escape character. 
1. <escape><quote>
	* Putting an escape character before a quote character allows the quote character to be included in a field.
2. <escape>n
	* Putting an escape character before the `n` character puts a newline character in a field.
3. <escape><escape>
	* Putting an escape character before another escape character allows that character to be in a field.

For example, if the default separator, quote, and escape characters are used, the string `GNU,"Stallman, Richard",\"Free software\"` would result in the fields `GNU`, `Stallman, Richard`, and `"Free software"`.
