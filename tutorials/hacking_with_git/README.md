# Falsifying Git Commits and Changing History

## Description
Git is a feature rich distributed version control system. The built in
git features have real world legitimate uses for writing software as
individuals or in a group but in this writeup I'm gonna show how these
features can be used to hack the grading system used in this course. 

## Hacking
My main motivation for finding a way to hack the my grade was the extra
credit that was offered up for doing it. The first idea I had was to
convince our professor Mike that he had make a mistake but seeing that
he payed a lot of attention to what was going on I didn't think that
would go to well for me. So, I turned to google and started reading up on
git. I didn't know exactly what I was looking for but I know I was on
the right track. In one of our labs we covered how to add files to a git
repository and commit the changes, what we didn't cover was how git
decided on who made the commits in the first place. If you look at a
repository's log with `git log`, you'll the history of all the commits
made up to that point. If you look at the output you'll see a output
similar to 
```
commit cfd45281e21e09966c1e91317402bbbc2a25f816
Author: Antoine Guerrero <asguerrero3@gmail.com>
Date:   Thu Aug 28 21:31:47 2014 -0700

    Add my tutorial README
```

## Additional Information
TODO: Add links relating to documentation pertaining to this bug. Also
add links relating to git and other bugs/features.
