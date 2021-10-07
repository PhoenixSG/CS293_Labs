/*
Improved by- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 3

Tree Traversal, Using Pre and In order to generate Binary tree
*/
enum TraversalType_e
{
  PRE_ORDER,
  IN_ORDER,
  POST_ORDER
};

struct Node
{
  char key;
  Node *parent;
  Node *left_child;
  Node *right_child;
  Node();
  Node(char k);

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
}

Node::Node(char k)
{
  parent = nullptr;
  left_child = nullptr;
  right_child = nullptr;
  key = k;
}

class Tree
{
  struct Node *root;

public:
  bool possible;
  Tree()
  {
    root = new Node();
    possible = true;
  } // Default constructor to construct empty tree

  // Notes for your learning
  // Beware of memory leaks: ideally the tree should also have a suitable destructor
  // But you will not be implementing a destructor here
  // Java is a better programming language than C++ in this regard, as you do not have to bother about memory leaks; Java has a dynamic garbage collector

  Tree(char *pre_order, char *in_order, int N)
  {
    possible = true;
    root = deduce_tree(pre_order, in_order, N);
  }

  // This will deduce the binary tree given the pre_order and in_order traversals
  // The first N characters of each string pre_order and in_order are relevant (this will be convenient for a recursive call)
  // You are to return NULL if there is no tree possible with the given pre and in order traversals
  struct Node *deduce_tree(char *pre_order, char *in_order, int N);

  // Functions external, left, below, right are the same as what is defined in the lecture video under generic binary tree traversal
  void traverse(){
        cout << endl
         << "Post order- ";
    root->traverse(POST_ORDER);
    cout << endl<<endl
         << "In order- ";

    root->traverse(IN_ORDER);
    cout << endl
         << "Pre order- ";

    root->traverse(PRE_ORDER);

    cout << endl;
  }
  // Traverse the tree as per the given traversal type; this function must be recursive
};

// Implement the above in TreeTraversal.cpp
// Also include the main() function in TreeTraversal.cpp
// In the main function, you can read two strings; you can assume that they each have unique characters, but check that their lengths are the same
// The first string will represent the pre-order traversal of the tree and the second will represent the in-order traversal
// You have to construct the tree using the suitable non-default constructor
// Then print its post-order traversal as a string
// Beware of null termination before printing strings!
