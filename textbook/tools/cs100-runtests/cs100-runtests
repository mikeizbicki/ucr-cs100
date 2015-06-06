#!/bin/sh

# sets up and launches cs100-runtests

# prints usage to stderr then quits
usage() {
    cat >&2 <<EOF
Usage: $(basename $0) [shell [testFile]]
EOF
    exit 1
}



######################################
# setup (data / functions)

# file edit grades in. Changeable at a later day.
gradeFile=grade

# unique session and window name
session="$USER-runtests"
window="$USER-runtests-window"


# prints what's passed in in red
red() {
    echo -en "\033[1;31m"
    echo -n "$@"
    echo -en "\033[0m"
}



######################################
# parameters

# shell. Defaults to "bin/rshell"
shell=${1:-bin/rshell}
# test case file
testCaseFile=$2

if [ "$shell" != "--controller" ]
then

    command -v $shell &>/dev/null || {
        red "$shell"
        echo ": not found" >&2
        usage
    }


    # make new session or attach previous if one already exists opens vim on the
    # grade file
    tmux -2 new-session -d -n $window -s $session "vim $gradeFile" || {
        tmux kill-session -t $session
        tmux -2 new-session -d -n $window -s $session "vim $gradeFile" || {
            echo "There was a serious problem" >&2; exit 1
        }
    }


    ### session settings
    # Mouse support
    tmux set-option -t $session mouse-select-pane on
    tmux set-option -t $session mouse-resize-pane on
    tmux set-option -t $session mouse-select-window on
    # Set the default terminal mode to 256color mode
    tmux set-option -t $session default-terminal "screen-256color"
    # new panes start in current directory
    tmux set-option -t $session default-path "$PWD"
    # don't stop server when there are no attached clients
    tmux set-option -t $session exit-unattached off
    # if the session becomes unattached, don't kill it
    tmux set-option -t $session destroy-unattached off
  
    ### window settings
    # mouse support for window
    tmux set-window-option -t $session:$window mode-mouse on
    tmux set-window-option -t $session:$window allow-rename off
  
    # split current window vertically, ends up as the top right pane
    tmux split-window -h "sh"
    # after pane is created, it is selected
    # calling list-window and printing pane_pid will give the pid of sh
    # running in that pane
    upperRightPID=`tmux list-pane -t $session -F '#{pane_pid}' | tail -1`
    #echo upperRightPID:$upperRightPID
    # split right pane horizontally, ends up as the bottom right pane
    tmux split-window -v -t 1 "$0 --controller $upperRightPID $shell $testCaseFile"
  
    # show linenumbers in vim (pane 0)
    tmux send-keys -t 0 ":set number" C-m C-l
  
    tmux -2 attach -t $session >/dev/null

else

    # todo: add cppcheck, valgind, checksyscalls, etc
    #echo >>$gradeFile
    #echo "cppcheck output:" >>$gradeFile
    #cppcheck src/ &>>$gradeFile
    #echo >>$gradeFile
    #echo "valgrind output:" >>$gradeFile
    #cppcheck src/ &>>$gradeFile
    #echo >>$gradeFile


    upperRightPID=$2
    shell=$3
    starterTestCaseFile=$4
    tempFile=$(mktemp)
    prevCommand="next"
    commandIndex=0
  
    declare -a commandArray
  
    # function to print its parameters in red
    # does not insert a newline after printing
  
    cleanupAndQuit() {
        rm -rf $tempFile
        tmux kill-session -t $session
    }

    trap cleanupAndQuit SIGINT SIGQUIT SIGTERM SIGTSTP

    readTestCases() {
        if [ -z "$1" ]
        then
            return
        elif [ ! -f $1 ]
        then
            red "$1"; echo ": file not found"
            return
        fi

        index=0
        commandArray=()

        while read -r line
        do
            commandArray[$index]="$line"
            index=`bc <<< "$index + 1"`
        done <$1

        unset index
        echo "Successfully loaded test cases from \"$1\""
    }



    shellUp() {
        if [ ! -z $disabled ]
        then
            return 1
        fi

        if [ `ps --ppid $upperRightPID | wc -l` -le 1 ]
        then
            red "shell is not running. starting a new instance... "
            tmux send-keys -t 1 C-c
            tmux send-keys -t 1 "$shell" C-m
            #tmux send-keys -t 1 "valgrind --leak-check=full $shell" C-m
            if [ `ps --ppid $upperRightPID | wc -l` -le 1 ]
            then
                red "failed"; echo
                disabled=true
                return 1
            else
                red "success"; echo
                return 0
            fi
        elif [ ! -z `ps --ppid $upperRightPID -o state | grep T` ]
        then
            red "shell is stopped. attempting to restart... "
            tmux send-keys -t 1 C-c
            tmux send-keys -t 1 fg C-m
            usleep 500000
            if [ ! -z `ps --ppid $upperRightPID -o state | grep T` ]
            then
                red "failed"; echo
                disabled=true
                return 1
            else
                red "success"; echo
                return 0
            fi
        fi
    }



    executeCommand() {
        shellUp
        if [ ! -z $disabled ]
        then
            red "The controller is disabled. This means that the shell has likely"; echo
            red "encountered a serious issue and will not stay running."; echo
            return
        fi
        for charIndex in $(seq 0 `bc <<< "${#1} - 1"`)
        do
            # send one char
            # assumes shell is in pane 1
            tmux send-keys -t 1 "${1:$charIndex:1}"
        done
        tmux send-keys -t 1 C-m
    }


    fullGrade() {
        line=$1
        outOf=$(cat $gradeFile | head -$line | tail -1 |
                grep -o '/[[:blank:]]*[[:digit:]][[:digit:].]*[[:blank:]]*\]' |
                grep -o '[[:digit:].]*')
        #echo line:$line
        #echo amt:$amt
        changeGrade $line $outOf
        #sed "$line"'s/\[.*\//\['$outOf'\//' $gradeFile >$tempFile &&
        #cp $tempFile $gradeFile
    }


    changeGrade() {
        line=$1
        amt=$2
        if [[ $line =~ ^[0-9]+$ ]] # line is made of only numbers
        then
            if [[ $amt =~ ^[0-9][0-9.]*$ ]] # amt is made of only numbers and '.'
            then
                sed "$line"'s/\[.*\//\['$amt'\//' $gradeFile >$tempFile &&
                cp $tempFile $gradeFile
            else
                red $amt; echo ": invalid amount"
            fi
        else
            red $line; echo ": invalid line number"
        fi
    }


    parseGradeFile() {
        grep -o '\[[[:blank:]]*[[:digit:].]*[[:blank:]]*/[[:blank:]]*[[:digit:]][[:digit:].]*[[:blank:]]*\]' |
        grep -o '[[:blank:][:digit:]/.]*'
    }


    updateTotal() {
        earned=0
        total=0
        for val in $(cat $gradeFile | parseGradeFile | cut -d/ -f1)
        do
            earned=`bc <<< "$earned + $val"`
        done

        for val in $(cat $gradeFile | parseGradeFile | cut -d/ -f2)
        do
            total=`bc <<< "$total + $val"`
        done

        sed '1s/.*/'"$earned \\/ $total"'/' $gradeFile >$tempFile &&
        cp $tempFile $gradeFile
    }


    updateVim() {
        tmux send-keys -t 0 ':e!' C-m 'gg' C-l
    }


    controllerUsage() {
        echo -e "Valid commands:"
        echo -e "n\t\t - next test case"
        echo -e "p\t\t - previous test case"
        echo -e "\t\t   + b is an alias of p"
        echo

        echo -e "g <line> <amt>\t - assign <amt> points to <line> in grade file"
        echo -e "f <line>\t - assign full points to <line> in grade file"
        echo -e "zero\t\t - make all grades [ 0 / total ]"
        echo -e "full\t\t - make all grades [ total / total ]"
        echo

        echo -e "h\t\t - print this message"
        echo -e "c\t\t - clear the screen"
        echo -e "e\t\t - exit"
        echo -e "\t\t   + q is an alias of e"
    }



    controller() {
        cmd=$1
        line=$2
        file=$2
        amt=$3
        if [ ! -z "$cmd" ]
        then
            prevCommand="$@"
        fi
        case "$cmd" in
            "") # same as previous
                controller $prevCommand
                ;;
            "h")
                ;&
            "h?")
                ;&
            "?h")
                ;&
            "?")
                ;&
            "??")
                ;&
            "help")
                controllerUsage
                ;;
            "c")
                ;&
            "clear")
                clear
                ;;
            "l") # load testcase
                ;&
            "load") # load testcase
                readTestCases $file
                ;;
            "n") # next one command
                ;&
            "next") # next one command
                if [ $commandIndex -lt ${#commandArray[@]} ]
                then
                    executeCommand "${commandArray[$commandIndex]}"
                    commandIndex=`bc <<< "$commandIndex + 1"`
                else
                    red "no more test cases"; echo
                fi
                ;;
            "b") # back one command
                ;&
            "back")
                ;&
            "p")
                ;&
            "previous")
                if [ $commandIndex -gt 0 ]
                then
                    commandIndex=`bc <<< "$commandIndex - 1"`
                    executeCommand "${commandArray[$commandIndex]}"
                else
                    red "no previous test case"; echo
                fi
                ;;
            "g")
                ;&
            "grade") # grade <line> <amt>
                changeGrade $line $amt
                updateTotal
                updateVim
                ;;
            "f") # full grade <line>
                fullGrade $line
                updateTotal
                updateVim
                ;;
            "zero") # zero all grades
                for zeroLine in `seq 1 $(cat $gradeFile | wc -l)`
                do
                    changeGrade $zeroLine 0
                done
                updateTotal
                updateVim
                ;;
            "full") # max all grades
                for fullLine in `seq 1 $(cat $gradeFile | wc -l)`
                do
                    fullGrade $fullLine >/dev/null
                done
                updateTotal
                updateVim
                ;;
            "q")
                ;&
            "quit")
                ;&
            "e")
                ;&
            "exit")
                cleanupAndQuit
                ;;
            *)
                red $cmd
                echo ": invalid command (try h?)"
        esac
    }

    # stuff to do before starting:
    shellUp
    readTestCases $starterTestCaseFile
    controllerUsage

    while read -p "command [$prevCommand]: " args
    do
        controller $args
    done

    cleanupAndQuit
fi


