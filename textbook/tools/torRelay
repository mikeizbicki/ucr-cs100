# TOR Relay Setup
## What is Tor?
The Tor network is a group of servers that provide a means of virtual tunnel 
connections for internet use. 
This provides the user the ability to avoid direct connection to the internet,
thus allowing for a more private browsing over public networks without leaving any trace.
It also gives users the ability to be free from surveillance and reach otherwise 
unreachable contents online without the fear of being tracked.
Besides the numerous benefits of Tor, setting up a Tor Relay is also an extra credit for 
this class so this tutorial will help you get your precious extra credit the easiest way. 

## The Setup
* First we need to know the distribution.
We can know this by running `lsb_release -c or cat /etc/debian_version`

* Once we know the distribution, open /etc/apt/sources.list
and add the following(change the <distribution> with whatever
the previous step printed out):

```
deb http://deb.torproject.org/torproject.org <distribution> main
deb-src http://deb.torproject.org/torproject.org <distribution> main
// For my Case I appended this to my source.list
// deb http://deb.torproject.org/torproject.org sid main
// deb-src http://deb.torproject.org/torproject.org sid main
//
```
* After changing the repo list, we run the following commands:
```
gpg --keyserver keys.gnupg.net --recv 886DDD89
gpg --export A3C4F0F979CAA22CDBA8F512EE8CBC9E886DDD89 | sudo apt-key add -
```
Now we can install it:
```
sudo apt-get update
sudo apt-get install tor deb.torproject.org-keyring
```

* For optimal anonymity, it is suggested that you install Tor browser as well.
Here's a link: https://www.torproject.org/projects/torbrowser.html.en
For ubuntu files, simply uncompress the file, go into the directory and run 
`./start-tor-browser`

Now the important part. Configuring your computer as a Tor Relay. 
By doing this, not only your getting close to your extra credit, but you're also helping
to speed up the service by volunteering as a relay.

* We can configure it by modifying the `torcc` file located at Data\Tor\torcc.
For my case, I have it saved in my downloads folder, so I have:
`VAIO-PC:~/Downloads/tor-browser_en-US/Browser/TorBrowser/Data/Tor$`
Open it with any text editor, and add the following lines:
```
ORPort 9001//Here is where Tor listens for connections
Dirport 9030//Here is where Tor advertises the direcrory service
Exitpolicy reject *:*//Determines wether its an exit relay or not
Nickname ididntedittheconfig//Nickname for connection
ContactInfo human@...    
```
 
Now restart tor `sudo service tor restart`

We should check in /var/log/tor/log to see if the computer has successfully connected
as a tor relay. We should have a message saying something like:
```
Self-testing indicates your ORPort is reachable from the outside. Excellent. Publishing server descriptor.
Self-testing indicates your DirPort is reachable from the outside. Excellent.
```

Once done, you can check using Atlas or Globe to see whether your relay is up:
atlas: https://atlas.torproject.org/
https://globe.torproject.org/


