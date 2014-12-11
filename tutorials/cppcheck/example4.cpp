int foo()
{
	char arr[10];
	// cppcheck-suppress arrayIndexOutOfBounds	
	arr[15] = 1;

}

/*One way to prevent a certain error is by using inline suppression. By 
following the format of `// cppcheck-suppress <ERROR:ID>`, cppcheck will 
recognize this, and will not print out the error. To turn on inline 
suppression, run the command `cppcheck --inline-suppr <FILENAME>`

One can also suppress the error in the command line in the format of 
`cppcheck --suppress=<ERROR:ID> <FILENAME>`*/
