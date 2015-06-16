# PART 5: Text screens and a story

In case you missed it, the previous tutorial can be found [here](../part4).

## 5.1 Creating Text
The next step we will be implementing in our game will be an intro screen. The first step
in this process will be storing the text we want to output. Since our text will be 
displayed sequentially based on an input, we want to store it in a `std::vector`. We also
want to keep track of where we are in our text as well as which part. Let's go ahead 
and do this. 
```c++
const std::vector<std::string> story_text = {
    "Just another Monday, and you're on your way to work...",
    "When suddenly..."
    "You realize you left the oven on!",
    "Take a shortcut through that asteroid field!",
    "Get back to the house before your planet explodes!"
};

size_t story_part = 0;
size_t story_position = 0;
```
Each line represented in the vector above is a different part of the story. We will
advance these parts with the SPACE key.

## 5.2 Setting Up Our Intro Window
Now that we have created and stored our text that we will display, we will set up the 
window we will display it on. For our game we will use the `main_wnd` to display our 
intro text. We will begin by creating an infinite loop that will only break when we
have reached the end of our text. Our window must be able to take input, so we will 
use `wgetch`. Now we will implement this method. 
```c++
void run() {

    // code omitted

    int in_char = 0;

    const std::vector<std::string> story_text = {
        "Just another Monday, and you're on your way to work...",
        "When suddenly..."
            "You realize you left the oven on!",
        "Take a shortcut through that asteroid field!",
        "Get back to the house before your planet explodes!"
    };

    size_t story_part = 0;
    size_t story_position = 0;
    
    while(1) {
        in_char = wgetch(main_wnd);
        
        if(story_part >= story_text.size()) break;

        usleep(10000); // 1 ms
    }
}
```
## 5.3 Displaying Some Text
In order to display text onto our window, we will be using the `mvaddch` function as well
as the `wattron` and `wattroff` to add attributes to our text. These functions will use
our story position and part to determine which text to display. `mvaddch` will display our 
text char by char along a the given x and y positions. Since we want our text to be in 
our main window, we will choose our y coordinate as 20 and our x coordinate as
5 + `story_position`. We must also check that our story position is within the bounds of 
our story text. Let's have a look at what this looks like.
```c++
void run() {

    // code omitted

    int in_char = 0;

    const std::vector<std::string> story_text = {
        "Just another Monday, and you're on your way to work...",
        "When suddenly..."
            "You realize you left the oven on!",
        "Take a shortcut through that asteroid field!",
        "Get back to the house before your planet explodes!"
    };

    size_t story_part = 0;
    size_t story_position = 0;
    
    while(1) {
        in_char = wgetch(main_wnd);
       
        // check if position is within length
        if(story_position < story_text[story_part].length()) {
            wattron(main_wnd, A_BOLD); // makes text added BOLD

            //prints out correspondin part of story char by char
            mvwaddch(main_wnd, 20, 5 + story_postion, story_text[story_part][story_postion]);

            wattroff(main_wnd, A_BOLD); // turns off BOLD effects
            story_postion++;
        }

        if(story_part >= story_text.size()) break;

        usleep(10000); // 1 ms
    }
}
```
## 5.4 Using Input to Traverse Through Text
Now that we can display one part of our stories text, we want to know how to continue to 
the next part of the story. To do this we will be using the `SPACE` key to advance us.
First, let us print out a prompt to the user letting them know that `SPACE` will advance them.
Now that the user know we need only check for the input since we have already implemented 
our input feature. So, if we detect an input of `SPACE` we should increment `story_part` and
reset the position to 0. Another thing we should check if the user input is the letter `q`.
This will not only get us out of the intro text, it will also exit the game which is what
we want. Let's give this a try. 
```c++
void run() {

    // code omitted

    int in_char = 0;

    const std::vector<std::string> story_text = {
        "Just another Monday, and you're on your way to work...",
        "When suddenly..."
            "You realize you left the oven on!",
        "Take a shortcut through that asteroid field!",
        "Get back to the house before your planet explodes!"
    };
    
    // display prompt to user
    mvwprintw(main_wnd, 22, 57, "press SPACE to skip...");

    size_t story_part = 0;
    size_t story_position = 0;
    
    while(1) {
        in_char = wgetch(main_wnd);
       
        // check if position is within length
        if(story_position < story_text[story_part].length()) {
            wattron(main_wnd, A_BOLD); // makes text added BOLD

            //prints out correspondin part of story char by char
            mvwaddch(main_wnd, 20, 5 + story_postion, story_text[story_part][story_postion]);

            wattroff(main_wnd, A_BOLD); // turns off BOLD effects
            story_postion++;
        }

        if(in_char == ' ') {
            story_part++;
            story_postition = 0;
            mvwhline(main_wnd, 20, 1, ' ', screen_area.width() -2);
        }

        else if(in_char == 'q') {
            exit_requested = true;
            break;
        }

        if(story_part >= story_text.size()) break;

        usleep(10000); // 1 ms
    }
}
```
## 5.5 Making Our Intro More Interesting
Now that we have the core components of our intro window done, we can focus on making it
less boring. For our game, we will simply make our starry background run on the `game_wnd`.
In order to do this, we will add features we have used previously to our loop. These will 
include a sleep time, a tick counter, and the `wrefresh` to refresh our game window only. 
We will also assume that our star object has already been declared and initialized.
```c++
void run(){
    
    // code omitted

    while(1) {
        werase(game_wnd); // deletes contents on game window
        in_char = wgetch(main_wnd);
        
        if(tick % 50 == 0)
            stars.update();

        // makes starry background
        for(auto s : stars.getData())
            mvwaddch(game_wnd, s.getPos().y, s.getPos().x, '.');
            
        // check if position is within length
        if(story_position < story_text[story_part].length()) {
            wattron(main_wnd, A_BOLD); // makes text added BOLD

            //prints out correspondin part of story char by char
            mvwaddch(main_wnd, 20, 5 + story_postion, story_text[story_part][story_postion]);

            wattroff(main_wnd, A_BOLD); // turns off BOLD effects
            story_postion++;
        }

        if(in_char == ' ') {
            story_part++;
            story_postition = 0;
            mvwhline(main_wnd, 20, 1, ' ', screen_area.width() -2);
        }

        else if(in_char == 'q') {
            exit_requested = true;
            break;
        }

        if(story_part >= story_text.size()) break;

        wrefresh(game_wnd);

        tick++;
        usleep(10000); // 1 ms
    }
}
```
We have now finished making our intro story for our game. You can now use this
method make many more features such as the game over window displayed when a player loses.
