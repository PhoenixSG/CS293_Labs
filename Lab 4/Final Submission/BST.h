// In this lab you will be implementing binary search tree as an enhancement to last week's tree traversal
// You will also be implementing the first question in your tutorial: the specific version of the binary search tree which stores at each node, the height of that node.
// In addition, store a null terminated string (max length 32) (this is instead of the char from the earlier lab).
// The string is used for defining the ordering, based on alphabetical comparison as implemented in strcmp.
// You may find it necessary/convenient to store a pointer to the parent of each node

/*
Improved by- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 4

BST.
*/
#include <iostream>
using namespace std;

enum TraversalType_e
{
  PRE_ORDER,
  IN_ORDER,
  POST_ORDER
};

struct Node
{
  string key;
  int height;
  Node *parent;
  Node *left_child;
  Node *right_child;
  Node();
  Node(string k);

  void external(TraversalType_e tt);
  void left(TraversalType_e tt);
  void below(TraversalType_e tt);
  void right(TraversalType_e tt);
  void traverse(TraversalType_e tt);
  
};

Node::Node()
{
  parent = nullptr;
  left_child = nullptr;
  right_child = nullptr;
  key = '\0';
  height=0;
}

Node::Node(string k)
{
  parent = nullptr;
  left_child = nullptr;
  right_child = nullptr;
  key = k;
  height=0;
}


class BST
{
  struct Node *root;

public:
  bool possible;
  BST()
  {
    root = new Node();
    possible = true;
  } // Default constructor to construct empty tree

  BST(Node* root){
    this->root = root;
    possible = true;
  }

  // Notes for your learning
  // Beware of memory leaks: ideally the tree should also have a suitable destructor
  // But you will not be implementing a destructor here
  // Java is a better programming language than C++ in this regard, as you do not have to bother about memory leaks; Java has a dynamic garbage collector

  // Note: deduce tree from lab3 is not relevant here for this lab

  // Traverse the tree as per the given traversal type; this function must be recursive
  void traverse(){
        // cout << endl
    //      << "Post order- ";
    // root->traverse(POST_ORDER);
    cout << endl
         << "In order- ";

    root->traverse(IN_ORDER);
    // cout << endl
    //      << "Pre order- ";

    // root->traverse(PRE_ORDER);

    cout << endl;
  }

  //---- Lab4 functions start here ----//
  // Min and Max nodes in the BST
  struct Node *minim();
  struct Node *maxim();
  // Search for a given character; return a pointer to the node; NULL if no such string found
  struct Node *search(char *s);
  // Insert the given node in the BST; return true if success; false if already exists (don't insert duplicates)
  bool insert(struct Node n);
  // Delete the given character from the BST; return true if success; false if not found
  bool remove(char *s);
  // Return the successor of the given node; NULL if no successor exists
  struct Node *successor(struct Node *n);
  // Return the predecessor of the given node; NULL if no predecessor exists
  struct Node *predecessor(struct Node *n);
};

// Implement the above in BST.cpp
// Also include the main() function in BST.cpp
// In the main function, you can read one string after another, insert them
// Check that the in-order traversal gives strings in sorted order
// Also check that the height of each node is correct

// Next, plot a graph of time to insert vs size of tree
// Compare the shape of this plot with nlog(n) in the same graph
// For this, you may find it convenient to insert random strings, say a million of them, in a loop, and compute+store the time taken for each insert operation, then later plot
// You can just generate random int/float values and convert them to strings of certain length

// Optional: (a) insert a milion strings (b) delete each of them
// Compare the memory occupied by your program, before insertion, after insertion, and after deletion (you can put a sleep(30) or cin in-between); you can use the linux top command for this
// If you do not delete memory carefully, you will likely be leaking memory, which can cause the program/system to crash; if you are adventerous, make it crash your laptop
