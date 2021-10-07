// In this lab you will be implementing binary tree traversal, and also the algorithm to deduce the tree given pre-order and in-order traversal
// For these, we will be implementing a tree where each node stores a character

#include <iostream>
#include <string.h>
using namespace std;
#include "TreeTraversal.h"

void Tree::left(TraversalType_e tt)
{

    if (tt == PRE_ORDER)
    {
        cout << " " << get_value();
    }
}

void Tree::below(TraversalType_e tt)
{

    if (tt == IN_ORDER)
    {
        cout << " " << get_value();
    }
}

void Tree::right(TraversalType_e tt)
{

    if (tt == POST_ORDER)
    {
        cout << " " << get_value();
    }
}

void Tree::external(TraversalType_e tt)
{

    cout << " " << get_value();
}

void Tree::traverse(TraversalType_e tt, Node *nd)
{
    if (nd == nullptr)
    {
        return;
    }
    if (nd->left == nullptr && nd->right == nullptr)
    {
        external(tt);
        return;
    }
    left(tt);
    traverse(tt);
    below(tt);
    traverse(tt, nd->right);
    right(tt);
}

struct Node *Tree::deduce_tree(char *pre_order, char *in_order, int N)
{
    if (!possible)
    {
        return nullptr;
    }

    char k = pre_order[0];
    Node *temp = new Node(k);

    if (N == 0)
    {
        return nullptr;
    }
    if (N <= 1)
    {
        if (in_order[0] == k)
            return temp;
        else
        {
            cout << "False" << endl;
            possible = false;
            return nullptr;
        }
    }
    int x;
    bool flag = false;
    for (int i = 0; i < N; i++)
    {
        if (in_order[i] == k)
        {
            x = i;
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        possible = false;
        return nullptr;
    }

    temp->left->root = deduce_tree(&pre_order[1], in_order, x);
    temp->right->root = deduce_tree(&pre_order[x + 1], &in_order[x + 1], N - x - 1);

    if (!possible)
    {
        temp = nullptr;
    }
    return temp;
}

int main()
{

    string a = "abcdefghijklmnop";
    string b = "abcdefghijklmnop";
    Tree *tree = new Tree(&a[0], &b[0], a.length());

    tree->traverse(POST_ORDER, tree->root);
    cout << endl;
}

// Implement the above in TreeTraversal.cpp
// Also include the main() function in TreeTraversal.cpp
// In the main function, you can read two strings; you can assume that they each have unique characters, but check that their lengths are the same
// The first string will represent the pre-order traversal of the tree and the second will represent the in-order traversal
// You have to construct the tree using the suitable non-default constructor
// Then print its post-order traversal as a string
// Beware of null termination before printing strings!
