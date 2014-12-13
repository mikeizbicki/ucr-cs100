# how to be a spammer

You should complete this lab using pair programming with a new partner.

### coding instructions

In this lab, we're going to learn to send spam emails.  It turns out that with the [Simple Mail Transfer Protocol (SMTP)](http://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol), you don't need to know someone's password to send email from their account!  Anyone can send emails from anyone else's account!

First, you're going to practice sending these emails.  Then, you're going to write a bash script to automate the process.

**IMPORTANT:** Don't use this for evil!  It will get your cs account suspended and could even get you arrested!

#### spoofing an email

First, telnet into the local SMTP webserver:

```
telnet mail.cs.ucr.edu 25
```

Telnet is a simple command line utility that let's us send commands over the network.  Whatever you type in gets sent over the network to the server you're connected to.

Now, type the following commands:

```
helo whitehouse.gov
mail from: presidentobama@whitehouse.gov
rcpt to: yourpartnersemail@server.com
data
Subject: I'm the president!
I order you to submit correct homework!
.
```

The dot at the end is very important.  It must be on a line all by itself.  That's what tells the server that the email message is over.

**IMPORTANT:** Our server is configured so that you must be on the computer science network to have access to it.  You cannot do this from home (unless you ssh in).  There are, however, many poorly configured servers on the internet that let anyone access them to send email from.

#### automate the process using bash

In this part of the lab, you're going to write a bash script that sends spam to your friends.  The script should be called `sendspam.sh`.  It will take two parameters.  The first is the email address of the recipient, and the second is the email of the sender.  Your script will read stdin to get the body of the email, and the subject line will always be `This email is spam!`.

For example, if you were a jerk, you could spoof an email from me to one of your classmates using the command:

```
$ ./spam.sh classmate@ucr.edu mike@izbicki.me
Class is cancelled forever.  
There is no more homework.
Everyone get's an A++++++.
:)
^D
```

### deliverables

When finished, demo your working code for the TA.  
