# Sample .bashrc file: customized for CS100 students!
# Please look below and fill out these variables.
# Altering them will cause this file to function correctly
# according to your preferences.

# FIXME
favdirectory=""
rshelldir=""
username=""

#
# colors
#

# Normal Colors
Black='\e[0;30m'        # Black
Red='\e[0;31m'          # Red
Green='\e[0;32m'        # Green
Yellow='\e[0;33m'       # Yellow
Blue='\e[0;34m'         # Blue
Purple='\e[0;35m'       # Purple
Cyan='\e[0;36m'         # Cyan
White='\e[0;37m'        # White

# Bold
BBlack='\e[1;30m'       # Black
BRed='\e[1;31m'         # Red
BGreen='\e[1;32m'       # Green
BYellow='\e[1;33m'      # Yellow
BBlue='\e[1;34m'        # Blue
BPurple='\e[1;35m'      # Purple
BCyan='\e[1;36m'        # Cyan
BWhite='\e[1;37m'       # White

# Background
On_Black='\e[40m'       # Black
On_Red='\e[41m'         # Red
On_Green='\e[42m'       # Green
On_Yellow='\e[43m'      # Yellow
On_Blue='\e[44m'        # Blue
On_Purple='\e[45m'      # Purple
On_Cyan='\e[46m'        # Cyan
On_White='\e[47m'       # White

NC="\e[m"               # Color Reset

#
# functions
#

function take_me_home {
  cd $favdirectory
}

# make the directory, then cd into it
function mcd {
    mkdir -p $1
    cd $1
}

# extract EVERYTHING
function extract {
 if [ -z "$1" ]; then
    # display usage if no parameters given
    echo "Usage: extract <path/file_name>.<zip|rar|bz2|gz|tar|tbz2|tgz|Z|7z|xz|ex|tar.bz2|tar.gz|tar.xz>"
 else
    if [ -f $1 ] ; then
        # NAME=${1%.*}
        # mkdir $NAME && cd $NAME
        case $1 in
          *.tar.bz2)   tar xvjf $1    ;;
          *.tar.gz)    tar xvzf $1    ;;
          *.tar.xz)    tar xvJf $1    ;;
          *.lzma)      unlzma $1      ;;
          *.bz2)       bunzip2 $1     ;;
          *.rar)       unrar x -ad $1 ;;
          *.gz)        gunzip $1      ;;
          *.tar)       tar xvf $1     ;;
          *.tbz2)      tar xvjf $1    ;;
          *.tgz)       tar xvzf $1    ;;
          *.zip)       unzip $1       ;;
          *.Z)         uncompress $1  ;;
          *.7z)        7z x $1        ;;
          *.xz)        unxz $1        ;;
          *.exe)       cabextract $1  ;;
          *)           echo "extract: '$1' - unknown archive method" ;;
        esac
    else
        echo "$1 - file does not exist"
    fi
  fi
}

function _exit
{
    echo -e "${Blue}a crash reduces\nyour ${Red}${On_White}expensive${NC}${Blue} computer\ntosimple ${Black}stone${NC}"
}
trap _exit EXIT

function mod_pwd {
    if [ $1 = "red" ]; then
        echo -e "${Red}"
    elif [ $1 = "blue" ]; then
        echo -e "${Blue}"
    elif [ $1 = "green" ]; then
        echo -e "${Green}"
    fi
    pwd
    echo -e "${NC}"
}

# print most common commands
function mostcommon {
  history | awk '{CMD[$2]++;count++;}END { for (a in CMD)print CMD[a] " " CMD[a]/count*100 "% " a;}' | grep -v "./" | column -c3 -s " " -t | sort -nr | nl |  head -n10
}

# print the branch name for git
function git_branch_pun_intended {
    __git_ps1 "${1:-(%s) }"
}

#
# aliases
#

alias ll='ls -alF'                          # long-listing format for ls

alias c='clear'                             # useful, common

alias ..='cd ..'
alias ...='cd ../../../'
alias ....='cd ../../../../'                # and so on
alias meminfof='free -mlt'                  # memory information

# print subdirectories in a tree visualization
alias tree="ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'"

# create a random password
alias genpasswd="strings /dev/urandom | grep -o '[[:alnum:]]' | head -n 30 | tr -d '\n'; echo"

alias rs="cd $rshelldir"
alias hammer="ssh -X $username@hammer.cs.ucr.edu"
alias well="ssh -X $username@well.cs.ucr.edu"
alias bell="ssh -X $username@bell.cs.ucr.edu"
alias bass="ssh -X $username@bass.cs.ucr.edu"

#
# PS1 stuff
#

# Add the branch to PS1
export GIT_PS1_SHOWDIRTYSTATE=yes
export PS1="\$(git_branch_pun_intended)${PS1}";
