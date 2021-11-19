#ifndef STACK
#define STACK

#include "double_stack_model.h"

image_dequeue ::image_dequeue()
{
    N = INIT_SIZE;
    f = 0;
    r = 0;
    //keeping f==r as a sign of empty queue
    A = new image_sfml[INIT_SIZE];
    //All variables initialised
}

bool image_dequeue::isEmpty()
{
    return size() == 0;
    //sign of empty queue
}

bool image_dequeue::isFull()
{
    return (f - r + N) % N == 1;
    //sign of full queue, max capacity of N has been reached
}

unsigned int image_dequeue::size()
{
    return (N + r - f) % N;
    //return size of a circular array
}

void image_dequeue::grow()
{
    image_sfml *B = A; //holder temporary variable, will be destroyed after this function.

    //creating new larger array

    // A = new double[nextSizeLinear()];
    A = new image_sfml[nextSize()];

    int size_till_now = size(), k;
    for (int i = 0; i < size_till_now; i++)
    {
        k = (f + i) % N;
        A[i] = B[k];
    }
    //copying all the original elements
    // Using variable k to "unroll" the previous circular array.

    //initialising the front and rear variables
    f = 0;
    r = N - 1;

    N = nextSize();
}

void image_dequeue::insertFront(image_sfml x)
{
    if (isFull())
    {
        grow();
    }
    //change front and insert at new position
    f = (f + N - 1) % N;
    A[f] = x;
}

void image_dequeue::insertRear(image_sfml x)
{
    if (isFull())
    {
        grow();
    }
    //insert at the necessary position and then update the position
    //This reverse order is as per instructions in the question
    A[r] = x;
    r = (r + 1) % N;
}

bool image_dequeue::removeFront(image_sfml *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value and remove the element by advancing f index
    *x = A[f];
    f = (f + 1) % N;
    return true;
}

bool image_dequeue::removeRear(image_sfml *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value and remove the element by bringing nack the r index

    *x = A[(r - 1 + N) % N];
    r = (r + N - 1) % N;
    return true;
}

bool image_dequeue::front(image_sfml *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value.
    *x = A[f];
    return true;
}

bool image_dequeue::rear(image_sfml *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value.
    *x = A[(r - 1 + N) % N];
    return true;
}

void double_stack::insert(long double x_shift, long double y_shift, int resolution, float zoom, sf::VertexArray vertexarray)
{
    image_sfml *new_image = new image_sfml();
    new_image->save_image_parameters(x_shift, y_shift, resolution, zoom, vertexarray);
    first.insertFront(*new_image);
}

void double_stack::delete_current_image(long double x_shift, long double y_shift, int resolution, float zoom, sf::VertexArray vertexarray)
{
    image_sfml *current_image = new image_sfml();
    first.removeFront(current_image);
    delete current_image;
}

bool double_stack::move_left()
{
    if (first.size()<=1)
    {
        return false ;
    }
    image_sfml *removed_image = new image_sfml();
    first.removeFront(removed_image);
    second.insertFront(*removed_image);
    return true;
}

bool double_stack::move_right()
{
    if (second.isEmpty())
    {
        return false;
    }
    image_sfml *removed_image = new image_sfml();
    second.removeFront(removed_image);
    first.insertFront(*removed_image);
    return true;
}

bool double_stack::return_current(image_sfml *image_pointer)
{ 
    return first.front(image_pointer);
}

#endif
