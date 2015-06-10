##setenv:

[man page - setenv](http://linux.die.net/man/3/setenv)

**includes:** `#include <stdlib.h>`

**declaraton:** `int setenv(const char *v_name, const char *v_value, int overwrite);`

**returns:** If successful returns zero, otherwise returns -1, with errno set to indicate the cause of the error.

**overwrite paramater:**

######Nonzero

- Change the existing entry of v_name.
- If v_name is defined and exists, the value of v_name is changed to the v_value. 
- If v_name was previously undefined, it is given the value of v_value. 

######Zero
  
- Do not change the existing entry of v_name.
- If v_name is defined and exists, the value of v_name is *not* changed to the v_value. 
- If v_name was previously undefined, it is given the value of v_value. 

##getenv:

[man page - getenv](http://linux.die.net/man/3/getenv)

**includes:** `#include <stdlib.h>`

**declaraton:** `char *getenv(const char *name)`

**returns:**  If successful returns a pointer to the value in the environment, or NULL if there is no match.

##Examples

``char *ppath`` is used as a variable in the following examples.

Example 1: This example shows what happens when the overwrite paramater is a non-zero and v_name has a value.

    ppath = getenv("PWD");                  //puts the environment of $PWD into ppath
    if(ppath == NULL)                       //error checking
      perror("getenv");   
    cout << "$PWD = " << ppath << endl;     //prints the environment of $PWD 

Output: of this code would be `$PWD = /class/classes/username/CS100` this is because the char variable ppath is getting the 
environment from `getenv("PWD")` and the environment of `$PWD` is `/class/classes/username/CS100`. So ppath points to that 
environment. There is also proper error checking to make sure that `$PWD` has a environment and if it does not the `perror` 
is called. 

    ppath = getenv("HOME");                 //gets the environment of the $HOME
    if(ppath == NULL)                       //error checking
      perror("getenv");
    cout << "$HOME = " << ppath << endl;    //prints the environment of $PWD

Output: of this code would be `$HOME = /class/classes/username` this is because the char variable `ppath` is getting the 
environment from `getenv("HOME")` and the environment of `$HOME` is `/class/classes/username`. So `ppath` points to that 
environment. There is also proper error checking to make sure that `$HOME` has a environment and if it does not the `perror` 
is called. 

    if(-1==setenv("PWD",ppath,1))           //since the overwrite paramater is non-zero it replaces environment 
      perror("setenv");                     //of $PWD with the value of ppath which is defined by the environment 
                                            //of $HOME
    
This is to change the environment of `$PWD` in this case it take the value that the `ppath` is pointing to which in this case
is `/class/classes/username` which is also `$HOME`. The overwrite paramater is non-zero so it replaces the environment of 
`$PWD` to `ppath`.

    ppath = getenv("PWD");                  //gets the environment of $PWD
    if(ppath == NULL)                       //error checking
      perror("getenv");
    cout << "$PWD = " << ppath << endl;     //the value should now be the same as the value of $HOME

Output: of this code would be `$PWD = /class/classes/username` this is because the char variable ppath is getting the 
environment from `getenv("PWD")` and the environment of `$PWD` is `/class/classes/username`. So ppath points to that 
environment. There is also proper error checking to make sure that `$PWD` has a environment and if it does not the `perror` 
is called. The full output of example 1 is as follows.

Output 1:

    $PWD = /class/classes/username/CS100
    $HOME = /class/classes/username
    $PWD = /class/classes/username

Example 2: This example shows what happens when the overwrite paramater is a non-zero and v_name does not have a value.

    ppath = getenv("PWD");                  
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath  << endl;    //in this case ppath ="" because the environment of $PWD is not set
    
Output of the following code will be `$PWD = ` this is because the environment of `$PWD` is set to `""` in this case, it 
makes the `ppath` point to a empty string. Hence the reason it does not throw an error, however if `$PWD` was not defined an 
error would be thrown.

    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;

Output: of this code would be `$HOME = /class/classes/username` this is because the char variable `ppath` is getting the 
environment from `getenv("HOME")` and the environment of `$HOME` is `/class/classes/username`. So `ppath` points to that 
environment. There is also proper error checking to make sure that `$HOME` has a environment and if it does not the `perror` 
is called.

    if(-1==setenv("PWD",ppath,1))           //since the overwrite paramater is non-zero it replaces environment 
      perror("setenv");                     //of $PWD with the value of ppath which is defined by the environment 
                                            //of $HOME 

Since the overwrite paramater is 1 it does not matter what the `$PWD` it is set to `ppath` as defined in the earlier example.

    ppath = getenv("PWD");                  
    if(ppath == NULL)
      perror("getenv");  
    cout << "$PWD = " << ppath << endl;     //the value should now be the same as the value of $HOME

Output 2:

    $PWD =
    $HOME = /class/classes/username
    $PWD = /class/classes/username

Example 3: This example shows what happens when the overwrite paramater is a zero and v_name does have a value.

    ppath = getenv("PWD"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath << endl;
    
    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;
    
    if(-1==setenv("PWD",ppath,0))           //since the overwrite paramater is zero it does not replaces  
      perror("setenv");                     //environment of $PWD with ppath.

Here there is a new case where the overwrite paramater is zero. In this case it does not matter what `ppath` is because the 
zero flag makes it so that the `$PWD` is not replaced by the `ppath`.

    ppath = getenv("PWD");                
    if(ppath == NULL)
      perror("getenv");
    cout << "$PWD = " << ppath << endl;     //the value should not be changed.

Output 3:

    $PWD = /class/classes/username/CS100
    $HOME = /class/classes/username
    $PWD = /class/classes/username/CS100

Example 4: This example shows what happens when the overwrite paramater is a zero *or* a non-zero and v_name is a paramater 
that is not defined in the environment.

    ppath = getenv("HOME"); 
    if(ppath == NULL)
      perror("getenv");
    cout << "$HOME = " << ppath << endl;

    if(-1==setenv("random_name",ppath,0))   //since the overwrite paramater is zero and the the variable     
    perror("setenv");                       //$random_name is undefined, setenv makes the environment of 
                                            //$random_variable be the value of ppath. If the case where
                                            //there is a undefined variable the setenv behavous the
                                            //same way regardless of a non-zero or zero overwrite paramater. 
                                            
In this case the overwrite paramater is still zero, but the `v_name` is not declared so this is where the overwrite paramater
of zero is helpful. In this case `random_name` is set to `ppath` which is pointing to the environment of `$HOME` which is 
`/class/classes/username`. 
                                            
    ppath = getenv("random_name");  //gets the value of $PWD
    if(ppath == NULL)
      perror("getenv");
    cout << "$random_name = " << ppath << endl;     //the value should now be the same as the value of $HOME

Output 4:

    $HOME = /class/classes/username
    $random_name = /class/classes/username
