Using Bash and saving Time

In this tutorial you will learn a few things that can be done using bash commands to save you time and patience.

The ideology of this document is "If you are doing it manually, you are doing it in the wrong way".

Some of the content here you might think it isn't useful, but always remeber that you could apply the concept of it in other tasks you like making your life easier!

Before starting here it goes my first tip: FORGET THE MOUSE!

Good programmers are more efficient spending more time with their hands only on the keyboard than switching it to grab the mouse.

1. Navigate

	Explanation & Tips:
	-
	-
	-
	-
	-


2. Pipe the commands

	Explanation & Tips:
	-
	-
	-
	-
	-


3. Converting Pictures

	Converting pictures are a very simple task, now imagine that you need to convert a whole directory...

	Use the command 'convert' to convert one simple image:

		convert lion.jpg lion.png

	Now put it inside a loop:

		for f in *.jpg; do
		  convert ./"$f" ./"${f%.jpg}.pdf"
		done

	Explanation & Tips:
	-
	-
	-
	-
	-

4. Replacing words

	Pretend that you messed up your resumee with a mispelled word.

	Use 'sed' to switch mistakes:
	
		cat < resumee | sed 's/old/new/'

	Explanation & Tips:
	-
	-
	-
	-
	-

5. Network around

	
	Explanation & Tips:
	-
	-
	-
	-
	-
