#XMonad Basics

Xmonad is a tiling manager that automatically resizes or moves your current open windows to make efficient use of screen space. I will cover its basic usage in this tutorial.

##Installation

For debian based distros, fire up your terminal and enter `sudo apt-get install xmonad`

Otherwise, users should follow [this link](http://xmonad.org/intro.html) 

Xmonad can be used in two ways

1. Setting it as your default tiling manager in your current environment( by editing the ~/.xinitrc file ).
2. Running the xmonad environment.

For a beginner, I recommend using the second method, and that is the one I will be going over in this tutorial.

##Preparation

After the installation has finished, **log out** the current session. **Do not shutdown**. I mean, you can if you want to, but then you would have to power on again.

Now, you have to login to your user account in the xmonad session. The way to do this depends on your login manager. For KDM, which is the default login manager for Debian and Ubuntu (majority of people will have this), there will be a dropdown right next to your username at the login screen.

![](./images/login.png)

If you have a different login manager, or you do not see a dropdown to select your session, follow the instructions [here](https://wiki.archlinux.org/index.php/xmonad#Starting_xmonad)

##Usage

###Opening a terminal window
When you login, you will see a blank screen.

![](images/blanks.png)

Now, the command to run the terminal is **MOD-SHIFT-N**. MOD is by default the alt key, but it can be changed. So, basically, you will press alt, shift and n at the same time to run the terminal.

*On pressing MOD-SHIFT-N*

![](images/terms.png)

As you can see the terminal fills the screen completely. Lets see what happens when run another terminal.

*MOD-SHIFT-N again*

![](images/term2s.png)

A new terminal window opens up, but the two windows do not overlap and utilize the screen space most efficiently. This is the beauty of XMonad. 

*On pressing MOD-SHIFT-N for the third time.*

![](images/term3s.png)

As you can see, you can open as many things as you want and there would be no overlaps or blank spaces.

###Changing the focused window.
To cycle through other windows clockwise press **MOD-TAB** or **MOD-J**.
To cycle anticlockwise press **MOD-K**
 

###Closing the terminal
To close a focused window press **MOD-SHIFT-C**

After *MOD-SHIFT-C*, the screen will look like

![](images/term2s.png)

###Change current window size

You can change a window size by shifting the middle divider.

To move the divider left or right, press **MOD-H** or **MOD-L** respectively.

After pressing *MOD-H* a couple of times.

![](images/term2bss.png)

###Changing window layout mode

By default the windows will be viewed in the tall mode. There are other modes besides this. 

For e.g. the wide mode in which the terminals are split by a horizontal line instead of a vertical line. To change view mode press **MOD-SPACE**

There is also a single window mode, in which a single window occupies the screen, but you can cycle through other windows by pressing MOD-TAB.

*Wide Mode*

![](images/term2ws.png)

Apart from these three, there are many additional tiling algorithms that do not come packaged with xmonad. For instructions on how to install those follow this [link](http://xmonad.org/contrib.html)

###Switch Workspace

A workspace is a virtual screen. Every workspace has a desktop and has access to the same file system, but can run different applications and have different open windows. You can imagine them as different monitors.

In the xmonad environment, you will have 9 workspaces, which can be accessed using **MOD-1** to **MOD-9**.
This comes in real handy when you are working on something and suddenly you need to do something else. Instead of closing your current setup, you can just switch to a different workspace and come back later.

###Moving focused window to another workspace

To move the focused window to different workspace simply enter **MOD-SHIFT-NUM**.

###Installing Dmenu

So far, we have covered the basics of xmonad. Now we will install another useful tool called dmenu. Dmenu is an app launcher, that lets you type in the name of the app you want to run. This comes in real handy as you do not have to run the terminal to run Firefox.

For user with debian-based distros, run `sudo apt-get install dmenu` in the terminal.

For other distro users, follow the instructions [here](http://software.opensuse.org/download.html?project=utilities%3Asuckless&package=dmenu)

Xmonad has a default key binding to launch dmenu. The combo is **MOD-P**. On pressing MOD-P, you will notice that a toolbar will appear on the top of the screen. Here you can type the name of any application and press *ENTER* to launch it. Even partial names work, as long as there is no ambiguity. For e.g. to run Firefox, you can just type fir and that will do the job.

On pressing *MOD-P*

![](images/dmenus.png)

###Cheatsheet

Xmonad has a built in cheatsheet called xmessage. It displays the default keyboard bindings.
It can be run by pressing **MOD-SHIFT-SLASH**
 
On pressing *MOD-SHIFT-SLASH*

![](images/xmes.png)

###Accessing system settings

When you are in the xmonad session, there will be no menu bar and the right clicks with the mouse will not open anything. So everything must be done from the terminal. To connect to the internet, you will need to run `nm-connections-editor` in the terminal.

To open the control center, run `gnome-control-center`.
Ubuntu user should run `unity-control-center`.

###Personalizing Xmonad

Xmonad is very flexible in personalizations. You can add many things including new keyboard shortcuts, add-ons etc.

To configure you have to edit the `~/.xmonad/xmonad.hs` file. The configuration is not as easy as it has to be written in haskell. However, you can find many configurations online. A personal favorite of mine is [this](https://www.haskell.org/haskellwiki/Xmonad/Config_archive/John_Goerzen's_Configuration). This one will also teach you how to add your own keyboard bindings.

Report typos and/or broken links at ihund001@ucr.edu

