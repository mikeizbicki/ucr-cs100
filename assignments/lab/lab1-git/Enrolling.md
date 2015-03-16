
## enrolling in this course

We will not be using ilearn in this course.  We will be using git and github to manage everything.  This will give you practice working with open source software.  To enroll in this course, you will follow the same steps that you would do to contribute to an open source project.

### subscribing to the course

If you do not already have a github account, you will need to create one.  Go to http://www.github.com and register an account.  Your github account does NOT need to be the same as your CS account.  For example, my account is just my full name `mikeizbicki`.  Feel free to get creative and pick something fun.  If you already have a github account, you do not need to register a new one.

Return to http://github.com/mikeizbicki/ucr-cs100. At the top of the page there is a button labeled `Watch`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/watch.png?raw=true"/>
</p>

Click this button to become a follower of the repository. Anytime we update the course with new information or announcements, you will be notified by email.

Return to http://github.com/mikeizbicki/ucr-cs100.  On the right hand side of the page is a button labeled `issues`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/issues.png?raw=true"/>
</p>

Click this button.  At the top of the page will be a green button labeled `new issue`.  Whenever you have a question with the course, you should NOT email the instructors directly.  Instead, you should submit an issue here.  This will notify following the project (both instructors and students) about your question, and anyone can answer it.  We will be using this system for communicating instead of piazza.

### forking your repo 

Return to http://github.com/mikeizbicki/ucr-cs100.  In the top right corner of the page is a button labeled `fork`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/fork.png?raw=true"/>
</p>

Click this button to create a new version of this repository in your own GitHub account.  This is where all your grade information will be stored.  (Keep reading for details!)

By default, you are the only person with write access to your new repository.  You must give all the instructors write access so we can update your grades.  Visit the page:

*(Use your actual github username below)*

```
https://github.com/examplestudent/ucr-cs100
```

Click the button on the right hand side labeled `settings`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/settings.png?raw=true"/>
</p>

Click the button on the left hand side labeled `collaborators`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/collaborators.png?raw=true"/>
</p>

This should bring up a menu that lets you add collaborators.  Everyone you add here has full write access to the repo.  Add all of the course instructors as collaborators.  Our GitHub accounts are: `MikeIzbicki`, `busrac`, and `benavidz`.

**IMPORTANT:** The file <a href="https://github.com/mikeizbicki/gitlearn">README.md</a> in the gitlearn repo contains detailed information about how your grades will be stored in this repo.  Finish completing this lab, then go back and read this file.

### add your information to the course page

To finalize your enrollment in this class, you will change this repo to include your student information.

For open source projects, it's common that only a small number of people have write permissions to the repo.  In this repo, only the TA and I have write permission!  If I gave all you students write permission, someone would just delete all the homework!

Because you don't have write permission to this repo, adding changes will involve a few extra steps.  Here's a quick outline:  You first add the changes to your forked repo. Then you issue a "pull request."  This sends a message to the owners of the repo (in this case the course instructors) that you've made some changes you think we should add.  The instructors will then review your commit and make sure it follows the guidelines.

You've already forked the repository, so we can skip that step.  In order to modify the forked repo, you'll need to copy it onto your local computer.  This process is called "cloning" a repository.  Run the command:

*(Use your actual github username below)*

```
git clone https://github.com/examplestudent/ucr-cs100.git
```

This will create a folder in your current working directory called `ucr-cs100`.  This folder contains the contents of the repo you just cloned.

In the directory `people/students`, there is a file called `examplestudent` that contains the following information:

```
name = Mike Izbicki
giturl = http://github.com/examplestudent/ucr-cs100.git

# you MUST put valid accounts for each of the following websites below
# if you do not have an account (or do not want to list one you already have) then you may create a new, empty account
github = examplestudent
stackoverflow = mikeizbicki
slashdot = jackpirate
reddit = PokerPirate
hackernews = jackpirate

# only include a personal website if you already have one
website = http://izbicki.me
```

You need to create a file in the `people/students` directory that has the same name as your **CS account** and no file extension.
You need to add into the file all the information contained in the `examplestudent` file.

* The `name` field should be your full name.

* The `giturl` field is the url that we should use to clone your forked repo.

* The `github` field is the name of your github account.

* The `stackoverflow` field is the name of your stackoverflow account.
If you don't have one, you must go to http://stackoverflow.com and create one before continuing.

* The `slashdot` field is the name of your slashdot account.
If you don't have one, you must go to http://slashdot.org and create one before continuing.

* The `reddit` field is the name of your reddit account.
If you don't have one, you must go to http://reddit.com and create one before continuing.

* The `hackernews` field is the name of your hackernews account.
If you don't have one, you must go to http://news.ycombinator.com and create one before continuing.

Add and commit your new file like normal.
You may want to review the commands from the previous sections.

**IMPORTANT:**
I will be using the usernames for the social networking account to do research into the relationship between social network usage and academic performance.
You are not required to participate, but you still MUST provide valid social network logins above.
In order to opt out, you should create new accounts at each of the sites, provide those usernames, and then never user those accounts again.

We have two more steps to get your changes added into the original repository.
First, we have to update your forked repository on the github servers.
Run the command:

```
git push origin 2015winter
```

This "pushes" all the changes you've made back up to github.

Now you need to issue a "pull request" to this repository.
This is done through the github web server and not through the command line.
Visit your forked project's webpage at: http://www.github.com/yourusername/ucr-cs100.
There is a dull gray button labeled `pull request`:

<p align="center">
  <img src="https://github.com/thekevinlemon2/ucr-cs100/blob/master/assignments/lab/lab1-git/images/pull_request.png?raw=true"/>
</p>

Pressing this button will send you to a form where you fill out a message describing what you've changed in the code.  You merge message should be "enrolling in cs100".

Once you issue your pull request, the TA will review your contribution and add it to the repository.  Congratulations!  You've just made your first contribution to open source software and are officially enrolled in the class!

## references

We've only scratched the surface of what the git command has to offer.  You should be able to get by in this course using just these commands.  But if you’re looking for more info, here's some good links:

This webpage is a reference for the most common and useful git commands.

http://rogerdudler.github.io/git-guide

This is a full book on how to use git effectively.  It also has videos of programmers in action.

http://www.git-scm.com/doc

Here is a game made by previous students to test your git skills:

https://github.com/hgarc014/git-game.git

## deliverables

Tell the TA once you have issued your pull request.

You must get your drawing of your final git repository checked off by the TA.
