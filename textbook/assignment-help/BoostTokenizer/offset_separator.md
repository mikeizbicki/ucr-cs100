#offset_separator

If you have not yet read the (Boost Library Tokenizer tutorial)[README.md], please read it before continuing.

The `offset_separator` class breaks a string into tokens based on a sequence of integers, known as offsets. 
The `offset_separator` class constructor takes in two iterators, which tell the `tokenizer` where to begin and end the sequence of integer offsets.

For example, if you have the array `int offsets[] = {3, 3, 4}` and you pass in `offsets` and `offsets+3` into the `offset_separator` constructor (acting as iterators), you will have tokens of size 3, 3, and 4. 
Then, if you pass the string `6261234567` into the `tokenizer`, the resulting tokens will be `626`, `123`, and `4567`.
