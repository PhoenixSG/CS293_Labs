#include "DynamicDequeue.h"
using namespace std;

DynamicDequeue ::DynamicDequeue()
{
    N = INIT_SIZE;
    f = 0;
    r = 0;
    //keeping f==r as a sign of empty queue
    A = new double[INIT_SIZE];
    //All variables initialised
}

bool DynamicDequeue::isEmpty()
{
    return size()==0;
    //sign of empty queue
}

bool DynamicDequeue::isFull()
{
    return (f - r + N) % N == 1;
    //sign of full queue, max capacity of N has been reached
}

unsigned int DynamicDequeue::size()
{
    return (N + r - f) % N;
    //return size of a circular array
}

void DynamicDequeue::grow()
{
    double *B = A; //holder temporary variable, will be destroyed after this function.

    //creating new larger array
    
    // A = new double[nextSizeLinear()];
    A = new double[nextSizeExponential()]; 
    

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

    // N = nextSizeLinear();
    N = nextSizeExponential();
}

void DynamicDequeue::insertFront(double x)
{
    if (isFull())
    {
        grow();
    }
    //change front and insert at new position
    f = (f + N - 1) % N;
    A[f] = x;
}

void DynamicDequeue::insertRear(double x)
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

bool DynamicDequeue::removeFront(double *x)
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

bool DynamicDequeue::removeRear(double *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value and remove the element by bringing nack the r index

    *x = A[(r-1+N)%N];
    r = (r + N - 1) % N;
    return true;
}

bool DynamicDequeue::front(double *x)
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

bool DynamicDequeue::rear(double *x)
{
    if (isEmpty())
    {
        return false;
    }
    //if control reaches here, means queue is non-empty
    //assign and value.
    *x = A[(r-1+N)%N];
    return true;
}
