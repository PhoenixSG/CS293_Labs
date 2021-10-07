#ifndef DYNAMIC_DEQUEUE_H
#define DYNAMIC_DEQUEUE_H

// In this lab, you have to implement a dynamic dequeue of double values using an array
// When the array size is exceeded, you have to grow it (a) linearly, and (b) exponentially (i.e. doubling)
// You will compare the average run-time under both the above scenarios
// Your code for linear vs exponential growth should differ exactly in one function call: nextSizeLinear or nextSizeExponential
// Comparison graph: x-axis is number of elements inserted, y-axis run-time; two plots in same graph: one for linear size growth and one for exponential size growth
// Make sure to document your code properly using suitable comments

// FILES
// DO NOT MODIFY this file, submit as-is
// Write the CPP code for the specified header file below, in DynamicDequeue.cpp
// Write the main function in file main.cpp
// Submit graph as file runtime.png
// If you write any separate code for plotting the runtime, submit that too in plot.py

// While testing, you can change these constant values if you want
#define CONST_GROWTH 100
#define EXPO_GROWTH_FACTOR 2
#define INIT_SIZE 1000

class DynamicDequeue {
private:
  double *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int f; // index where first element of queue is present (if not empty)
  unsigned int r; // index where next element will be inserted
  unsigned int nextSizeLinear() { return N+CONST_GROWTH; }
  unsigned int nextSizeExponential() { return N*EXPO_GROWTH_FACTOR; }
public:
  DynamicDequeue(); // default constructor
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size (linear or exponential)
  unsigned int size(); // return the current number of elements in the queue
  void insertFront(double x); // insert given value in front of the queue; grow array size as necessary
  void insertRear(double x); // insert given value in rear of the queue; grow array size as necessary
  bool removeFront(double *x); // remove the value in front of the queue and place it in *x; returns false if queue is empty, true otherwise
  bool removeRear(double *x); // remove the value in rear of the queue and place it in *x; returns false if queue is empty, true otherwise
  bool front(double *x); // place value in front of queue in *x; returns false if queue is empty, true otherwise
  bool rear(double *x); // place value in rear of queue in *x; returns false if queue is empty, true otherwise
};

#endif
