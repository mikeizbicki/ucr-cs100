#Stashing

Imagine this situation: you just made a commit for `a.cpp` and are half way into developing `b.cpp`, but you realize that there is a small mistake in `a.cpp`.

If you want to keep your work in `b.cpp`, you have to make a commit for `b.cpp` with half-way work and then back to `a.cpp` to fix the bug. 
If you back to fix the bug in `a.cpp` without making the commit for `b.cpp`, you'll lose all the work in `b.cpp` since the last commit. 

Stashing is a way to solve this problem -- fixing the bug in previous commit without losing your recent work.

Now let's try the stash command:
First, create `a.cpp` and `b.cpp`, make a commit for `a.cpp` and make some development in `b.cpp` after the commit:
```
$ mkdir test
$ cd test
$ git init
Initialized empty Git repository in /Users/wangjinhang/Desktop/test/.git/
$ touch a.cpp
$ toch b.cpp
$ vim a.cpp
$ cat a.cpp
// hello world
$ git add a.cpp
$ git commit -m "helloworld a.cpp"
[master cd3e990] helloworld a.cpp
 1 file changed, 1 insertions(+)
$ git add b.cpp # suppose b.cpp has already been in the stage in the real situation
$ echo int main() >> b.cpp
$ echo { >> b.cpp
$ echo } >> b.cpp
$ cat b.cpp
int main()
{
}
```
Use git stash to interrupt the current work and back to the last commit cd3e990:
```
$ git stash
Saved working directory and index state WIP on master: df93074 helloworld a.cpp
HEAD is now at df93074 helloworld a.cpp
```
make some change(fix the bug in `a.cpp`) and commit it:
```
$ echo // a new line in a.cpp to test stash >> a.cpp
$ cat a.cpp
// hellow world
// a new line in a.cpp to test stash
$ git add a.cpp
$ git commit -m "add a line in a.cpp"
[master e495093] add a line in a.cpp
 1 file changed, 1 insertion(+)
```
Then use ```git stash list``` to check your stash status:
```
$ git stash list
stash@{0}: WIP on master: cd3e990 helloworld a.cpp
```
Back to the status that both updates the develop in `a.cpp` and keeps the work in `b.cpp` by ```git stash apply```
```
$git stash apply
$ cat b.cpp
int main()
{
}
$ cat a.cpp
// hellow world
// a new line in a.cpp
```
As a note, it seems that SVN doesn't have that function.


####Stashing Queue
You can also stash multiple statuses. (Always fixing the bugs)

With the following commands you can check the stash list:
```
$ git stash list
stash@{0}: WIP on book: 51bea1d... fixed images
stash@{1}: WIP on master: 9705ae6... changed the browse code to the official repo
```
You can also use these commands to go back to the stash you want:
```
$ git stash apply stash@{1}
```
Simply clear stash with the command ```git stash clear```.

