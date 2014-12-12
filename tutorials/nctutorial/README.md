# netcat

[Main Project Page](https://github.com/abarb014/nctutorial)

A short tutorial, on a very complicated and versatile tool.

## Table of Contents

* [Background](#background)
* [Basic Usage](#basic-usage)
* [Example Uses](#example-uses)
  - [Chat System](#chat-system)
  - [File Transfer](#file-transfer)
  - [Port Scanning](#port-scanning)
  - [Proxying and Port Forwarding](#proxying-and-port-forwarding)
* [Further Reading](#further-reading)

### Background

`netcat` is a service used to read and write from network connections, so it can be used for good, or it can be used for evil.`netcat` has been described as a "hacker" tool, 
 as well as a "swiss army knife". `netcat` can be explained by using another similar command called `telnet`. `telnet` does a lot of the same things as `netcat`, but it
 opens up a terminal-link prompt for the user to use. `netcat` does not, so you can automate tasks and make your life easier by using I/O redirection as well as piping
 with `netcat`.

 `netcat` and `telnet` both rely on the usage of computer networking ports. These are not physical ports on the compter (like USB or ethernet), but they are virtual
 ports. Ports in computer networking allow programs on the computer to share
 information with each other, or with someone else over the internet. Think of it like a bucket with two people on each side. One person puts something in the bucket, and
 the other person takes the thing out. These explanations are vastly oversimplified, but they will do for our purposes. However, if you are interested in ports and their
 role in the internet, you should look at these articles on [TCP](http://en.wikipedia.org/wiki/Transmission_Control_Protocol) and 
 [IP](http://en.wikipedia.org/wiki/Internet_Protocol). Another important note is port assignment. Many ports
 are registered for specific programs, so we should not use them for our tests. Luckily most Linux kernels allow the ports in the range 32768 to 61000 to be used for a wide 
 variety of things, and are not bound to one program or process.

### Basic Usage

To use the `netcat` command all you have to do is type `nc IPADDRESS PORT` at a terminal, where IPADDRESS is the IP you want to connect to, and PORT is the port number you
want to connect to. For most of this tutorial, we will connect to our own computers. The IP address of our own computer is `127.0.0.1`, or more simply `localhost`. The port
can be anything less than 2^16. Some common ports are are 22 for file transfers (SSH), 80 for internet browsers (HTTP), 443 for secure internet
browsing (HTTP over SSL), and a fun one is 3724 for Xbox Live.

If you type `nc localhost 32981` you probably will not see anything in the output. This is because `netcat` is going to that port, checking if anything is there, and
returning. It will output what is on that port on the standard output. However, if you type `nc -l localhost 32981` it will appear as though your terminal has frozen. Let it 
go! It is fine. What you told `netcat` to do is to go to port 32981 and wait there until someone or somthing gives it some data. `-l` tells `netcat` to listen to a port, rather than try to connect to it. You cannot use this with the -p option. As soon as it recieves the data, `netcat`
will close. Now we can start looking at some optional features of `netcat` as well as some examples to illustrate them. When using the `-l` option, `netcat` will default
to your default interfaces as shown by the `ifconfig` command.

### Example Uses

#### Chat System

This is a VERY simple system, where you can talk to another terminal session open on your computer. What is the point of that you may ask? Well read on, and you just might
 learn how to do this with other computers on your network. However, I must tell you this is not encrypted. You are sending your mail unsealed through the internet, so
 anyone that wants to read it, and knows how, can do what they want.

 The first thing you will want to do is open up two terminal windows. One will act as the listener, and the other one will send the data. After the connection is
 established it will not matter who types; whatever is typed on the server will be sent to both computers.

 Set up one window as the listener:
 ```
 nc -l 32981 # Or any port number you prefer above 32768!
 ```
 What this does is it tells `netcat` to listen to port 32981 (Or whatever) and it will print what it recieves.

 On the other window, we will connect to the server:
 ```
 nc localhost 32981
 ```

 This window is now connected to the port, and you are free to transfer text between the two windows. You have a simple chat system! Yay! If you want to end the system, go
 ahead and just type CTRL-D on any window. CTRL-D sends an EOF character to `netcat`s standard input, which closes the standard input. Since there is no input to the server, it gets closed, and closes the connections to it. This is cool and all, but why not try it with different computers? This requires one more step. You need to [find](http://lifehacker.com/5833108/how-to-find-your-local-and-external-ip-address) the local IP of the listening computer. Once you have it, go ahead and do the following commands.
 ```
 nc -l 32981 # This should be on the same computer as the two window experiment
 ```

 ```
 nc LISTENERS-LOCAL-IP 32981
 ```
 And voila! You have a super dangerous to use, but still cool chat system. The only thing to remember is that the computers must be on the same network for this to work.

#### File Transfer

This is another simple system that will show you how to transfer files with `netcat` as well as show you a little of piping with `netcat`. You will need two windows or two
computers like before. On one terminal, enter this:
```
cat file | nc -l 32981
```
Essentially, this tells `netcat` to listen on a given port and hold a file. Going back to the bucket analogy, one man takes a package with him and tosses it in the bucket
and waits until he sees someone else. Now the other window or computer will run this:
```
nc localhost 32981 > file # Where localhost can be the local IP address of the listener, if you are using two computers.
```
With this command, you connect to port 32981 on the server computer, and you redirect what you find there into a file. A man shows up, takes what is in the bucket, and both
men leave. This command will close `netcat` on the server because we did not specify to keep the connection open. In order to keep the connection open, you would have to use
the `-k` option. This option cannot be used with `-l`.
This is a simple, but powerful example; you now know
that you can "load up" the server, and that you can redirect the output to files. Of course if we did not redirect the output, the contents of the file would have been
printed to standard output instead.

#### Port Scanning

Say you want to host your own website with your favorite web server. While you are getting everything set up, you run into an error! For some reason, your server cannot
start on port 80, the HTTP port. Instead of panicking or calling the cops, you probably should check to see if the port is in use by something else first. There are
some programs like `netstat` on Linux that can do this for you, but you need to be on the machine you want to check for open ports on. However, if you were away
from the computer, say at school for example, and you just need a quick and dirty check of some ports, like port 80, you can do this:

Start by running this on a terminal:
```
nc -z localhost 80
```
`-z` makes `netcat` scan for listeners. This cannot be used with the -l option. You must specify a port, or range of ports to scan. 
This command checks to see if anything is listening on port 80, however the output can get a little tricky. First of all, the command will not print anything if there is
nothing listening on the port. This might confuse new users. If something IS listening, then you will get a message like the folowing:
```
Connection to localhost port 32981 [tcp/*] succeeded!
```

You can also use the -v flag to get better output. 
`-v` gives `netcat` verbose (lots of big words) output. 
But you would know that if you read the flag section, right? So if nothing is listening on port 80, you can run your
web server. But if you get output, that means something is running on that port, and you should close it before trying to make a web server.

Port scanning also works on domain names! Here is an example:
```
abarb014@nctutorial$ nc -z -v -w 1 google.com 80
found 0 associations
found 1 connections:
     1: flags=82<CONNECTED,PREFERRED>
        outif en1
        src MY.IP.CENSORED port 52345
        dst 74.125.196.113 port 80
        rank info not available
        TCP aux info available

Connection to google.com port 80 [tcp/http] succeeded!
abarb014@nctutorial$ 
```
`-w` specifies a timeout for `netcat`, and it has no purpose with the -l option. It must be immediately followed by a wait time in seconds. 
From the output, you can see the source IP and port, as well as the destination IP and
port. I covered my IP and port for some security, but notice at the bottom it said the connection to google was a success! Yay! This is not as useful as checking your own
ports, but you might be able to check for some open ports on the computers that serve a website you do not particularly like. You can find out more about that on some shadier
websites, but as for this tutorial, we will be good little hackers.

Another important fact to note is you can specify a range of ports to check rather than just one! I would also like to note that port scanning is not normally done with
`netcat`. By using the [nmap](http://nmap.org/book/man.html) command, you can get a more detailed port scan. However, if you have no time and are away from home, you can go
ahead and run a nice, quick `netcat`.

#### Proxying and Port Forwarding

Your internet router has one IP address that the
world can use to talk to it. It assigns local IP addresses (like the one we found earlier) to the devices on your network, and it routes the internet traffic to whatever 
device is requesting it, or being requested. Regular port forwarding means redirecting the requested port to a machine on the local network.

In this example, we will redirect requests from a port on our computer to a website.

This is done with the following command:
```
nc -l 32981 | nc www.amazon.com 80
```
What we are doing is making a `netcat` server on port 32981. Requests to that port will be piped (or forwarded) to the amazon.com webserver on port 80. Now if we go to a
web browser and type `localhost:32981` in the address bar, nothing will happen! Why? Well, the first call to `netcat` makes the server, and the second one redirects the 
request, but we are not doing anything with the repy from amazon! We can fix this with a two way pipe, or "named pipe". If you would like some more information on named
pipes, I recommend you check out this [article](http://www.tldp.org/LDP/lpg/node15.html).

This time, do this:
```
mkfifo pipe
nc -l 32981 < pipe | nc www.amazon.com 80 > pipe
```
This time if you refresh the browser, we get output! Woo! This is because we redirect standard input to come from the pipe, which at first has nothing, and we redirect the
output from amazon to the pipe. We can read and write from this pipe, so not only do we get output from the browser, but we can send more input to get new webpages. Using
this technique along with some crafty BASH scripting skills, you can make a small, very insecure webserver.

This idea of sending web requests to one server, and having it make the request for you is called proxying. Say your favorite website was blocked at work, and you knew this
trick. With some port forwarding on your router you could run this command using your favorite website (probably not amazon) on your home computer, and get access to it 
from work or school. For example, your school might block the hacking website [phrack.org](http://www.phrack.org), but you have access to it at home. It is no longer a
problem for you with your newfound knowledge.
The key is that your computer does not make the web request directly. It requests that another server make the request, and in the end you get the same 
output. This is an incredibly basic proxy, but of course with some work and added code, you can build your very own proxy server, and now you have the knowledge to do so.

The same thing can be done, but instead of websites, with ports. If your company or school blocks a port for outgoing requests, then you can forward requests to that pipe to
go through a different pipe. For example, port 80 is blocked. No matter! simply use:
```
nc -l 80 | nc localhost 32981
```
Now any requests made to port 80 will be forwarded to port 32981. Yay for you!

### Further Reading

As I mentioned back in the beginning, `netcat` is referred to as a "swiss army knife" by many. It is a great little tool for many things, but it is not always the best tool.
You would not cut a tree down with a spoon, right? We saw in the port scanning section that there are better tools, like nmap, and netstat. Also, many system administrators
might block usage of `netcat` because of the possibility of malicious actions with it. You might want a prompt to play around with rather than sending one whole chunk of
commands to the server. In that case, you are probably better off using `telnet`. With named pipes and redirections running wild, the syntax for `netcat` might be a little
too crazy for you, so you might be better off with a different version of `netcat` like `ncat`. Maybe you are more interested in breaking into systems and nothing else, then
you might be interested in the Metasploit framework, or Wireshark to read those unencrypted chat sessions I taught you to make!

Here is a link dump if you are interested in learning more about `netcat` or some of these other tools:

* [netcat Man Page](http://linux.die.net/man/1/nc)
* [netstat Man Page](http://linux.die.net/man/8/netstat)
* [nmap](http://nmap.org/book/man.html#man-description)
* [telnet](http://linux.die.net/man/1/telnet)
* [ncat](http://nmap.org/ncat/)
* [Metasploit Project](http://en.wikipedia.org/wiki/Metasploit_Project)
* [Wireshark](http://en.wikipedia.org/wiki/Wireshark)
* [Wiki for Packet Analyzers](http://en.wikipedia.org/wiki/Packet_analyzer)
