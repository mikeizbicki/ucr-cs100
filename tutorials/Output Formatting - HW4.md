# OUTPUT FORMATTING IN C++

This tutorial is inspired by the *ls* project in CS100. In that projects, we have to replicate the `ls` program, which entails getting a list of file names and outputting them automatically. In the process of attempting to replicate the format in which `ls` outputs, I learned about some usefull *iostream* functions and techniqes that implement them. So, let's get started, with a list!

##LIST DATATYPES
Lists are incredibly common in C++ programming. Whether you're using an array, a linked list, a vector, or any other datatype that behaves like some type of list, it is important to know how to effectively traverse it. For the majority of this tutorial, I'll be focusing on lists with random accessibility (arrays, vectors, etc.), that is any list datatype whose elements can be accessed with an index.

Example: Two lists of different datatypes(int[] and vector<int>) that hold exactly the same data.
```
//array
int myArray[3];
myList[0] = 5;
myList[1] = -4;
myList[2] = 17;

//vector
vector<int> myVector;
myVector.push_back(17);
myVector.push_back(-4);
myVector.push_back(5);
```

##SORTING
One really common task related to lists is sorting. There are a bunch of different sorting algorithms that are each better in some cases and worst in other, but you're best bet will usually be the `sort()` function included in the Standard Template Library(STL). Specifically, it is contained in the *algorithm* library.

Example: Using `sort()` is pretty simple:
```
//array
int ints[5];
  ints[0] = 5;
  ints[1] = -4;
  ints[2] = 17;

sort(begin(ints), end(ints));

//vector
vector<int> myVector;
  myVector.push_back(17);
  myVector.push_back(-4);
  myVector.push_back(5);

sort(myVector.begin(), myVector.end());
```
The code above calls the `sort()` function for the array and the vector. There is a third, optional parameter for `sort()` that lets you create your own comparison function to compare whatever datatype is stored in your lists. Omitting it, however, results in a simple ascending sort.

Sorting a list of strings in alphabetical order is just as simple. The only differece, of course, is that the elements are some type of strings. I recomend sticking with the STL string object. It's really easy to use and handles all of the memory management for you.

Example: Sorting strings:
```
//string vector
vector<string> myStrVector;
  myStrVector.push_back("rick");
  myStrVector.push_back("dave");
  myStrVector.push_back("carl");

sort(myStrVector.begin(), myStrVector.end());
```
And that's it! Just like that, you've got an alphabetically sorted list of strings ready to be sent to output with some funky, stylish formatting.

##OUTPUT
Now that we've got a sorted list, we can decide how we want to output it. The most simple method is to print each element on its own line. That would look like this:
```
carl
dave
rick
```
This is really basic but poses a pretty big issue. As soon as you start dealing with a list any larger than ten or so elements, the output is going to be rediculously long. That brings us to columns.

Printing a sorted list into columns turns out to be a bit more complicated than it may seem at first. We've got a few things to consider. First of all, do we want the output to ascend accross the columns or down the columns? Let's go back to numbers for clarity's sake.

Example: ascending accross columns:
```
0 1 2
3 4 5
6 7 8
```
Example: ascending down columns:
```
0 3 6
1 4 7
2 5 8
```
Printing out a list ascending accross columns is really simple if you know how many columns you want. We'll learn how to calculate the number of columns later. Assuming you want three columns, you just print three element at a time on each line. This works pretty well, but there is still an issue that causes the columns to not line up. We'll get to that later.

Printing out a list ascending down columns takes a bit more work. I am, again, going to assume we want three columns. Let's start off with an ordered list of numbers, `[0, 1, 2, 3, 4, 5, 6, 7, 8]`. We know how we want the output to look so let's just do it by hand for now.
```
0 3 6
1 4 7
2 5 8
```
The reason why I chose a list of numbers is so that it will be clear exactly which elements ended up where. We can see that elements 0, 3, and 6 are in the zeroeth row, 1, 4, and 7 are in the first, and 2, 5, and 8 are in the second. There is definitely a pattern here. The the first element of each row corresponds to the row number (zeroeth row starts with 0, first row starts with 1, etc.). After that, we increment by three. To be sure we've got the pattern right, and to figure out why three is the magic number, let's do the same thing with four columns and 14 elements.
```
0 4 8  11
1 5 9  12
2 6 10 13
3 7 

OR

0 4 8  12
1 5 9  13
2 6 10 
3 7 11
```
This is a bit more complicated than the previous example. The reason why is because the number of columns we chose does not divide evenly into the number of element we have. Before, we had 9 elements and three columns so we knew we needed a 3x3 grid, which perfectly holds 9 elements. In this case however, we need a 4x4 grid which can hold 16 element even though we only have 14. This means we will definitely have two empty spaces in our grid. The two options above show two possible arrangements. So the question is, do we want a partially filled row, or a partially filled column? My pick is the prior. Here's why.

Suppose we have 9 elements and we want them arranged into four columns. Our two options are:
```
//partially filled row
0 3 5 7
1 4 6 8
2 x x x

OR

//partially filled column
0 3 6 x
1 4 7 x
2 5 8 x
```
The x's represent blank spaces. As you can see, the first option has a partially filled row and the second option has a partially filled column. However, in this case, the number of empty spaces equals the number of rows, which means that in the second option, one columns is completely empty. So, even though we wanted four columns, we ended up with 3! This will happen any time the number of blank spaces(total spaces - number of elements) is equal to the number of rows.

Before we start coding, we still need to figure out where that magic three from earlier comes from. As it turns out, it is based on the number of rows. Everytime we start a new column, we know we've already printed as many elements as there are rows times how many columns we've printed. So, with nine elements and a 3x3 grid, we know that by the time we start printing the first element of the middle column, we've already printed the first three elements. Furthermore, when we get to the first element of the far right column, we know we've already printed the six preceding elements. When there are blanks to consider, we end up with a grid that has n rows at first, then n-1 rows after a certain point. In the 4x3 grid above, when we get to the second columns, the grid only has two rows. So, rather than adding three to the index, we add two.

Here's an illustration:
```
0 3 5 7
1 4 6 8
2
```
From the zeroeth column to the first column, each element is increased by three because in the zeroeth column, there are three rows. From the first row to the second row, each element is increased by two because in the first column, there are two rows. And so on.

So, now that we know we want partially filled rows, and we know how much to increment each element by from column to column, let's make an algorithm to do it for us.

Let's start with the simple case(9 elements, 3 columns, 3x3 grid).
```
int nCols = 5;//how many columns we want
int nRows = ceil( myStrVector.size()/float(nCols));//returns how many rows we will need
int blanks = nCols * nRows - myStrVector.size();//returns how many blank spaces there will be in the grid
int stepSwitch = nCols - blanks;//determines at which column the number of rows decreases to account for the blanks

int printCount = 0;//this will count how many elements we have printed

for( int row=0; row<nRows; row++ ){//this loop will run once for each row

    int step = nRows;//this will be how much each element is incremented by
    int off = 0;//this will hold the current offset to add to each element.

    for( int col=0; col<nCols; col++ ){//this loop will run once for each column
        printCount++;//increment how many elements have been processed
        if(printCount <= myStrVector.size()){//make sure we only process as many elements as exist.
            cout << myStrVector[row + off] << "\t";//prints the element and a tab
            if(col == stepSwitch){//if we've reached the column where the number of rows decreases,
                step = nRows-1;//set the new step value to one less
            }
            off += step;//increase the offset
        }
    }
    cout << endl;
}
```
The above code will print the contents of a sorted vector, `myStrVector` into `nCols` columns, alphabetically descending down each column.


