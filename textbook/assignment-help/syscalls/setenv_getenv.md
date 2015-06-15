##setenv:

[man page - setenv](http://linux.die.net/man/3/setenv)

**includes:** `#include <stdlib.h>`

**declaration:** `int setenv(const char *v_name, const char *v_value, int overwrite);`

**returns:** If successful returns zero, otherwise returns -1, with errno set to indicate the cause of the error.

##getenv:

[man page - getenv](http://linux.die.net/man/3/getenv)

**includes:** `#include <stdlib.h>`

**declaration:** `char *getenv(const char *name)`

**returns:**  If successful returns a pointer to the value in the environment, or NULL if there is no match.

##Examples

``char *ppath`` is used as a variable in the following examples.

Example 1: This example shows what happens when the `overwrite` parameter is a non-zero and `v_name` has a value.

    ppath = getenv("PWD");                  //puts the environment of $PWD into ppath
    if(ppath == NULL)                       //error checking
      perror("getenv");   
    cout << "$PWD = " << ppath << endl;     //prints the environment of $PWD 

Output of this code is `$PWD = /class/classes/username/CS100` this is because the char variable `ppath` is getting the
environment from `getenv("PWD")` and the environment of `$PWD` is `/class/classes/username/CS100`. Therefore `ppath` points to that 
environment. There is also proper error checking to make sure that `$PWD` has a environment and if it does not `perror` 
is called. 

    ppath = getenv("HOME");                 //gets the environment of the $HOME
    if(ppath == NULL)                       //error checking
      perror("getenv");
    cout << "$HOME = " << ppath << endl;    //prints the environment of $PWD

Output of this code is `$HOME = /class/classes/username` this is because the char variable `ppath` is getting the 
environment from `getenv("HOME")` and the environment of `$HOME` is `/class/classes/username`. Therefore `ppath` points to that 
environment. There is also proper error checking to make sure that `$HOME` has a environment and if it does not `perror` 
is called. 

    if(-1==setenv("PWD",ppath,1))           //since the overwrite parameter is non-zero it replaces environment 
      perror("setenv");                     //of $PWD with the value of ppath which is defined by the environment 
                                            //of $HOME
    
This is to change the environment of `$PWD` in this case it take the value that the `ppath` is pointing to which in this case is `/class/classes/username` which is also `$HOME`. The `overwrite` parameter is non-zero, so it replaces the environment of `$PWD` to `ppath`

    ppath = getenv("PWD");                  //gets the environment of $PWD
    if(ppath == NULL)                       //error checking
      perror("getenv");
    cout << "$PWD = " << ppath << endl;     //the value should now be the same as the value of $HOME

Output of this code is `$PWD = /class/classes/username` this is because the char variable `ppath` is getting the 
environment from `getenv("PWD")` and the environment of `$PWD` is `/class/classes/username`. Therefore `ppath` points to that 
environment. There is also proper error checking to make sure that `$PWD` has a environment and if it does not `perror` 
is called. The full output of example 1 is as follows.

Output 1:

    $PWD = /class/classes/username/CS100
    $HOME = /class/classes/username
    $PWD = /class/classes/username

Example 2: This example shows what happens when the `overwrite` parameter is a non-zero and `v_name` has a blank value as in `v_name = ""` so an empty string.

    ppath = getenv("PWD");                  
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath  << endl;    //in this case ppath ="" because the environment of $PWD is not set
    
Output of the following code will be `$PWD = ` this is because the environment of `$PWD` is set to `""` in this case, it makes the `ppath` point to an empty string. Hence the reason it does not throw an error, however if `$PWD` was an undefined variable then `perror` is called.

    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;

Output: of this code is `$HOME = /class/classes/username` this is because the char variable `ppath` is getting the 
environment from `getenv("HOME")` and the environment of `$HOME` is `/class/classes/username`. Therefore `ppath` points to that 
environment. There is also proper error checking to make sure that `$HOME` has an environment and if it does not `perror` 
is called.

    if(-1==setenv("PWD",ppath,1))           //since the overwrite parameter is non-zero it replaces environment 
      perror("setenv");                     //of $PWD with the value of ppath which is defined by the environment 
                                            //of $HOME 

Since the `overwrite` parameter is 1 it does not matter what the `$PWD` it is set to `ppath` as defined in the earlier example.

    ppath = getenv("PWD");                  
    if(ppath == NULL)
      perror("getenv");  
    cout << "$PWD = " << ppath << endl;     //the value should now be the same as the value of $HOME
The output of the following code is `$PWD = /class/classes/username` this is because `setenv` changed the value of `$PWD` as defined in the past code block, to `ppath`. 

Output 2:

    $PWD =
    $HOME = /class/classes/username
    $PWD = /class/classes/username

Example 3: This example shows what happens when the `overwrite` parameter is a zero and v_name does have a value.

    ppath = getenv("PWD"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath << endl;
In this case `ppath` is set to the environment of `$PWD`. The output of this code block is 
`$PWD = /class/classes/username/CS100`. 

    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;

In this code block `ppath` is set to the environment of `$HOME`. The output of the following code block will be 
`$HOME = /class/classes/username`.

    if(-1==setenv("PWD",ppath,0))           //since the overwrite parameter is zero it does not replaces  
      perror("setenv");                     //environment of $PWD with ppath.

Here there is a new case where the `overwrite` parameter is zero. In this case it does not matter what `ppath` is because the
zero flag makes it so that the `$PWD` is not replaced by the `ppath`, unless `$PWD` was a undefined variable, in which case 
`$PWD` would be given the value of `ppath`.

    ppath = getenv("PWD");                
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath << endl;     //the value should not be changed.

The output of this code block is `$PWD = /class/classes/username/CS100`. This is because `setenv` did not change the 
environment of `$PWD` because of the `overwrite` parameter.

Output 3:

    $PWD = /class/classes/username/CS100
    $HOME = /class/classes/username
    $PWD = /class/classes/username/CS100

Example 4: This example shows what happens when the `overwrite` parameter is a zero *or* a non-zero and `v_name` is a parameter that is not defined in the environment.

    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;

In this case ppath is given the environment of `$HOME`, there is also proper error checking done. The output of the code
block is `$HOME = /class/classes/username`.

    if(-1==setenv("random_name",ppath,0))   //since the overwrite parameter is zero and the variable     
    perror("setenv");                       //$random_name is undefined, setenv makes the environment of 
                                            //$random_variable is the value of ppath. If the case where
                                            //there is a undefined variable the setenv behaves the
                                            //same way regardless of a non-zero or zero overwrites parameter. 
                                            
In this case the `overwrite` parameter is still zero, but the `v_name` is not declared so this is where the `overwrite` parameter of zero is helpful. In this case `random_name` is set to `ppath` which is pointing to the environment of `$HOME` which is `/class/classes/username`. 

    ppath = getenv("random_name");                  //gets the value of $PWD
    if(ppath == NULL)
      perror("getenv");
    cout << "$random_name = " << ppath << endl;     //the value should now be the same as the value of $HOME

The `ppath` is contains the environment of `$random_name` which is set by the `setenv` in the previous code block. The output
of this code block is `    $random_name = /class/classes/username`

Output 4:

    $HOME = /class/classes/username
    $random_name = /class/classes/username
