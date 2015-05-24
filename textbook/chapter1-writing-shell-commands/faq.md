
#hw1 FAQs

Below are some simple answers to the most frequently asked questions on hw1, with links to the issues they are referenced from.

##git

Why is `git push` giving me an error?  
In case you didn't encounter this error [last homework assignment](../chapter0-unix-shell-basics/faq.md)
, you should first check that cs100 settings are on, and that your repository is up-to-date.

##ls

What is the meaning of "total" when `ls -l` is run?  
This is the number of blocks used by the files in the current directory, which [sometimes varies.](https://github.com/mikeizbicki/ucr-cs100/issues/1467)

Are columns a set size? How long should a column be?  
For best results, [columns should be as wide as the longest file name.](https://github.com/mikeizbicki/ucr-cs100/issues/394)
 
Does `ls` need to list in alphabetical order?  
[Yes](https://github.com/mikeizbicki/ucr-cs100/issues/920)
, but you have [some flexibility](https://github.com/mikeizbicki/ucr-cs100/issues/928) 
as to how to approach this.

Should `ls` be able to handle flags in front and behind the file or folder name?  
[Yes, it should.](https://github.com/mikeizbicki/ucr-cs100/issues/1449)



##valgrind

When running valgrind, it reports some bytes may be "possibly lost" or other. Is this a problem?  
No, as long as there aren't any ["definitely lost" bytes](https://github.com/mikeizbicki/ucr-cs100/issues/987)
or [errors](https://github.com/mikeizbicki/ucr-cs100/issues/922)
, it is acceptable.


