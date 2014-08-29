# Faking Git Commits

## Description
Git is a feature rich distributed version control system. The built in
git features have real world legitimate uses for writing software as
individuals or in a group but in this writeup I'm gonna show how these
features can be used to hack the grading system used in this course. 

## Hacking with Git
My main motivation for finding a way to hack the my grade was the extra
credit that was offered up for doing it. The first idea I had was to
convince our professor Mike that he had make a mistake but seeing that
he payed a lot of attention to what was going on I didn't think that
would go to well for me. So, I turned to google and started reading up on
git. I didn't know exactly what I was looking for but I know I was on
the right track. In one of our labs we covered how to add files to a git
repository and commit the changes, what we didn't cover was how git
decided on who made the commits in the first place. If you look at a
repository's log with `git log`, you'll see the history of all the commits
made up to that point. If you look at the output you'll see a output
similar to: 
```
commit cfd45281e21e09966c1e91317402bbbc2a25f816
Author: Antoine Guerrero <asguerrero3@gmail.com>
Date:   Thu Aug 28 21:31:47 2014 -0700

    Add my tutorial README
```
Looking at the example above we see that the author is identified by a
name followed by an email address. How does git determine which email
address to use? It uses the name and email address in your
`~/.gitconfig` file which the user gets to set. Since the user gets to
set which email is in the file and no validation ever takes place, there
is no way of telling if your name and email address are actually your
name and email address. With this in mind, lets look at how I used this
information to hack our grading system.

## Changing My Grade
After determining that there was no way git could tell if I was who my
configurations said I was I was left with one last hurdle. When pushing
to a GitHub repository using the https protocol you need to authenticate
yourself using your login information. I wasn't too sure what would
happen if I pushed a commit using a different email than the one used
for my GitHub credentials but I told Mike of my idea and with his
permission I went and tried out my idea. The process of committing with
Mike's credentials was straight forward. First I changed the grade in
file and then added the file with `git add grade`. The commit was made
with `git commit --author="Mike Izbicki <mike@izbicki.me>" -m "Change
grade"`. My concern about pushing with my Github credentials were not an
issue and all signs pointed to Mike have made the commit himself. You
may be wondering why git even allows this to happen in the first place
and the answer is simple. The person pushing new commits to a repository
may not be the person who made the changes. In a team environment many
people may commit code changes but for whatever reason one person may be
the only one responsible for pushing the code. So what happens to be a
Git feature helped my get extra credit in class.

## Using Git For Evil
In the example above Mike happened to be a contributor to my repository
but would the same method work for non contributors? It turns out it
still works. If you look up the git log to this repository you'll see
that 5 GitHub staff members have also contributed to this repository and
made changes to the file `look_inside.txt`. While this case of
committing commit fraud was rather innocent there are a few not so
innocent ways to abuse this feature. Consider the average CS student
that will be searching for job after graduation. Such a student may be
building a portfolio to present to possible employers but may not have
anything on GitHub that catches too much attention. One way to change
that could be fake some commits from some high profile programmers like
Linus Torvalds. Having some commits from Linus may get your project some
attention and make people assume you are a better programmer than you
really are. After all if your project was bad there would be no way
Linus would have looked at it and contributed in the first place.

## How to Avoid Fake Commits
In the case of this class there are at least one way to keep fake
commits from making it into the repository. The use of RSA signed
commits would probably be the best way to make sure that a student can't
make any commits without being discovered. This way all commits could be
viewed by running `git log --show-signature` and any commit not signed
would immediately be discovered. In the real world this would not help
in the case of a person committing to their own repository in an attempt
to bolster their list of contributors since they would receive no
benefit from verifiable commits.

# Additional Information
More information on the use of git can be found be reading the
documentation found at www.git-scm.com/documentation.
