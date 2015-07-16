# PART 3: Falling objects

In case you missed it, the previous tutorial can be found [here](../part2).

##3.1 Intro
In Part 3, we will be going over how we can create objects for our game. These objects can be used for 
multiple things such as stars, asteroids, power-ups, etc.

## 3.2 Code Overview
Before we can make use of our objects, we must learn how our object classes work.  
### 3.2.1 ObjectField.h
The `ObjectField.h` file contains our `ObjectField` and `SpaceObject` classes. `SpaceObject` holds the x and y position of
the object. `SpaceObject` is able to store and remove an object as well as update it's y position. Below we can see what 
our `ObjectField.h` file looks like. 
```c++
#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

class SpaceObject {

public:
    SpaceObject(int, int);
    void update();

    vec2i getPos() const;
    void setPos(vec2i);
   
private:
    vec2i pos;
};



class ObjectField {

public:
    void update();
    void erase(size_t);
    std::vector<SpaceObject> getData() const;

    void setBounds(rect);

private:
    rect field_bounds;
    std::vector<SpaceObject> object_set;

};

#endif
```
The functionality of each function is provided below.
* `SpaceObject`
  * `SpaceObject()` intializes the x and y position of the object
  * `update()` increments the y position of the object
  * `getPos()` returns the position of the object

* `ObjectField`
  * `getData()` returns the vector containing our objects 
  * `erase(size_t i)` removes object from vector at index i 
  * `setBounds(rect a)` sets boundary of our objects to variable a
  * `update` erases objects that are out of bounds and calls `SpaceObject::update` to change the y position of the remaining objects.


#### 3.2.2 ObjectField.cpp
Now that we have an understanding of the `ObjectField.h` file, we can now implement the `ObjectField.cpp` file. Let's begin
with the `SpaceObject` class functions. 
The constructor `SpaceObject` will set `pos.x` and `pos.y` to the two parameters passed in. 
```c++
SpaceObject::SpaceObject(int nx, int ny) { pos.x = nx ; pos.y = ny; }
```
Next, We want `SpaceObject::update` to update the y position of the object so that it moves down the screen. This means we 
must increment it by one each call. 
```c++
SpaceObject::update() { pos.y += 1; }
```
Our final `SpaceObject` function `getPos` will return a `vec2i` which contains the x and y position of an object. 
```c++
vec2i SpaceObject::getPos() const { return pos; }
```
Let's move onto our `ObjectField` functions now. Let's begin with `setBounds`. We know this function has parameter `a` 
which will constrain our objects to it's dimensions. So, we just have to set our `field_bounds` to a. 
```c++
void ObjectFields::setBounds(rect a) { field_bounds = a; }
```
Our next function `getData` will return a `vector` of `SpaceObject`. To implement this we just return our `object_set`.
```c++
std::vector<SpaceObject> ObjectField::getData() conts { return object_set; }
```
`erase` takes in an `size_t` parameter which is the index of the object we want to remove. We will use `vector::erase` in 
order to remove the object from the `object_set`
```c++
void ObjectField::erase(size_t i) {
    object_set.erase(object_set.begin() + i);
}
```
Our final function we must implement is the most difficult of them. `ObjectField::update` controls the movement of every 
object on the window. It also spawns a new object at a random x position and at y = 0. To do this, we must declare `srand` 
with `time(NULL)` as it's parameter in our `game.cpp` inti function. We then want to call `rand` to return a random number
within the range of our window width. Next, our function must also manage the memory of the vector. If we just keep pushing 
back every object, our vector will get too big and take up a lot of resources. So, we must have our function delete each object
from the vector as soon as it is out of bounds. Let's implement this now. 
```c++
void ObjectField::update() {
    // update existing objects
    for(size_t i = 0; i < object_set.size(); i++) {
        if(object_set.at(i).getPos().y > field_bounds.bot())
            object_set.erase(object_set.begin() + i);

        object_set.at(i).update();
    }

    // spawn a new object
    SpaceObject s(rand() % field_bounds.width(), 0);
    object_set.push_back(s);  
}
```
## 3.3 Object Implementation
Our next step will be to implement the objects class in our `game.cpp` in order to make game elements. For our demo, we will
create stars that will scroll down our game window. (Remember to include appropriate libraries as well as code from 
previous parts or our next task may not work as desired).
#### 3.3.1 Initialization
In order to create these stars, we must declare our object and set it's boundaries. Since we have not yet defined a window
for our game, we will be using the max dimensions of the terminal for our boundary. The function `getmaxyx(int, int)` from 
the `ncurses` library will return these dimensions for us. We must then store these two values in a `rect` in order to pass 
it into `setBounds(rect a)`. 
```c++
#include <unistd>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <vector> 

#include "game.h"
#include "ObjectField.h"

// code omitted

ObjectField stars; // initialize our star object

int init() {
    // code omitted
}

void run(){
    
    // code omitted

    // these will be used to initialize rect
    uinti_fast16_t maxx, maxy;   

    // get window boundaries
    getmaxyx(wnd, maxy, maxx);

    //initialize our rect with 0 offset
    rect game_area = { {0, 0} , {maxx, maxy} }; 
    
    //set our star bounds
    stars.setBounds(game_area);

    while(1) {
        // code omitted   
    }
}

```
#### 3.3.2 Displaying Objects
Our next task is to display the objects we created in our game window. We can use the `mvaddch(wnd, int, int, char)` from the
`ncurses` library to do this. `mvaddch` displays a char at the corresponding position and of the provided window. Let's also
call `update` so our stars will scroll down the game window. So, we will update the object then remove it from it's old 
position and finally display it at it's new position.
```c++

// code omitted

while(1) {

    stars.update();

    // this removes each object from it's previous position on the screen
    // by placing it with  a space on the screen instead
    // this will be replaced by a more efficent method later
    for(auto s : stars.getData()) {
        mvaddch(s.getPos().y, s.getPos().x, ' ');
    }

    for(auto s : stars.getData()) {

        // use getPos() to get position of stars
        // displays given character at given position on game window
        mvaddch(s.getPos().y, s.getPos().x, '*');

    }

    usleep(10000); // wait for 1 ms

}
```
## 3.4 Conclusion
We have now completed our task, however there is still problems we need to fix. Our stars currently moved down the screen to
quickly. They also create strange results when they collide with the window frame or player. This fix will be discussed in 
our next section which can be found here [next section](../part4).
