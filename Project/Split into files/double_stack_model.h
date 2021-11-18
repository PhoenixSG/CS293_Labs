#ifndef STACK
#define STACK

#include "image.cpp"

#define GROWTH_FACTOR 2
#define INIT_SIZE 1000

class image_dequeue
{
private:
    image_sfml *A;
    unsigned int N;
    unsigned int f;
    unsigned int r;
    unsigned int nextSize() { return N * GROWTH_FACTOR; }

public:
    image_dequeue();
    bool isEmpty();
    bool isFull();
    void grow();
    unsigned int size();
    void insertFront(image_sfml x);
    void insertRear(image_sfml x);
    bool removeFront(image_sfml *x);
    bool removeRear(image_sfml *x);
    bool front(image_sfml *x);
    bool rear(image_sfml *x);
};

//This is a unique double stack model I thought to store and traverse through a set of values.
//Basically, we need a Data structure such that we can move through different elements of the Data Structure, without losing ordering.
//I also wanted to add the option of adding a new value in between.

//This could have been implemented by a linked list, but I wanted to try something new in this project.
//Thus I have come with a double stack model.
//Here we have a primary stack and a secondary stack.

//We initially deal with the primary stack. All the data points we wish to store are put in the primary stack.
//Then, if we wish to go back to an old element at a certain point, we pop off elements and push them onto the secondary stack.
//When we reach the element we wanted, we can add more elements on top of it directly.

//Thus, we have found a way to model the dynamic ordering of data points.
// A right move means to pop from 2 and push onto 1.
// A left move mean to pop from 1 and push onto 2.
// Insertions always happen on 1 and control/current image is always on the 1st stack
class double_stack
{
private:
public:
};


//This is another data structure using the dequeue class.
//This structure returns a random image from the set of images stored.
//The way we achieve this is by
class random_sampling{


};

#endif