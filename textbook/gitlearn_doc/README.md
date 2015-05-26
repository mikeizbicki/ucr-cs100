### Introduction  
We took a class that used github to track and record grades. Originally, the professor offered extra credit if we could hack his grading system to change grades. However, this plan is flawed because a former cs100 student [Antoine Guerrero](https://github.com/aguerrero/Faking-Git-Commits) had already came up with a solution to increase grading security thus making it harder to change our grades. To counter act this, we decided to pour our resources in understanding and documenting [gitlearn](https://github.com/mikeizbicki/gitlearn) in hopes to finding a weakness in its grading security.  

`gitlearn_doc` is a documented guide to using the open software [gitlearn](https://github.com/mikeizbicki/gitlearn) for new users, both instructors and students.
It includes, but is not limited to, registering for a course, grading and grade checking, and utilizing the scripts here.

### Installation & Registration

Installing is simple. Just clone the repo and add the scripts folder to your PATH using the following commands:

Original version: $ git clone https://github.com/mikeizbicki/gitlearn  
Documented version: $ git clone https://github.com/aso001/gitlearn_doc    
$ export PATH=$(pwd)/gitlearn/scripts:$PATH  
In order for your PATH to remain across sessions you need to update your ~/.bashrc (or similar):  

$ echo "export PATH=$(pwd)/gitlearn/scripts:"'$PATH' >> $HOME/.bashrc  
### Bugs/Issues
