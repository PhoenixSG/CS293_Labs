#ifndef DYNAMIC_DEQUEUE
#define DYNAMIC_DEQUEUE

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
