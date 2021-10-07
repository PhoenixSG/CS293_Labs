/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 3

Tree Traversal, Using Pre and In order to generate Binary tree
*/
#include <iostream>
#include <string.h>
using namespace std;
#include "TreeTraversal.h"

void Node::left(TraversalType_e tt)
{

    if (tt == PRE_ORDER)
    {
        cout << " " << key;
    }
}

void Node::below(TraversalType_e tt)
{

    if (tt == IN_ORDER)
    {
        cout << " " << key;
    }
}

void Node::right(TraversalType_e tt)
{

    if (tt == POST_ORDER)
    {
        cout << " " << key;
    }
}

void Node::external(TraversalType_e tt)
{

    cout << " " << key;
}

void Node::traverse(TraversalType_e tt)
{
    if (this == nullptr)
    {
        return;
    }

    if (this->left_child == nullptr && this->right_child == nullptr)
    {
        this->external(tt);
        return;
    }
    this->left(tt);
    this->left_child->traverse(tt);
    this->below(tt);
    this->right_child->traverse(tt);
    this->right(tt);
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

    temp->left_child = deduce_tree(&pre_order[1], in_order, x);
    temp->right_child = deduce_tree(&pre_order[x + 1], &in_order[x + 1], N - x - 1);

    if (!possible)
    {
        temp = nullptr;
    }
    return temp;
}

int main()
{

    string a, b;
    cin >> a >> b;
    if (a.length() != b.length())
    {
        cout << "Length Mismatch" << endl;
        return 0;
    }
    Tree *tree = new Tree(&a[0], &b[0], a.length());

    if (tree->possible == false)
    {
        cout << "Tree not possible" << endl;
        return 0;
    }
    tree->traverse();

}


