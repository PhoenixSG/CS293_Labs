/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 4

BST
*/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <chrono>
using namespace std;
#include "BST.h"

void Node::left(TraversalType_e tt)
{

    if (tt == PRE_ORDER)
    {
        cout << " " << key << height;
    }
}

void Node::below(TraversalType_e tt)
{

    if (tt == IN_ORDER)
    {
        cout << " " << key << height;
    }
}

void Node::right(TraversalType_e tt)
{

    if (tt == POST_ORDER)
    {
        cout << " " << key << height;
    }
}

void Node::external(TraversalType_e tt)
{

    cout << " " << key << height;
}

void Node::traverse(TraversalType_e tt)
{
    if (this == nullptr || strcmp(this->key.c_str(), "") == 0)
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

struct Node *BST::minim()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        while (root->left_child != nullptr)
        {
            root = root->left_child;
        }
        return root;
    }
}

struct Node *BST::maxim()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        while (root->right_child != nullptr)
        {
            root = root->right_child;
        }
        return root;
    }
}

struct Node *BST::search(char *s)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        int x = strcmp(s, root->key.c_str());

        if (x == 0)
        {
            return root;
        }
        else if (x < 0)
        {
            return BST(root->left_child).search(s);
        }
        else
        {
            return BST(root->right_child).search(s);
        }
    }
}

bool BST::insert(struct Node an)
{

    Node *ptrn = new Node(an.key);
    Node n = *ptrn;

    if (strcmp(root->key.c_str(), "") == 0)
    {
        root = ptrn;
        return true;
    }

    int x = strcmp(n.key.c_str(), root->key.c_str());

    if (x == 0)
    {
        return false;
    }
    else
    {
        if (x < 0)
        {
            if (root->left_child == nullptr)
            {
                root->left_child = ptrn;
                ptrn->parent = root;
                root->height = max(root->left_child->height + 1, root->height);
                return true;
            }
            else
            {
                bool val = BST(root->left_child).insert(n);
                root->height = max(root->left_child->height + 1, root->height);
                return val;
            }
        }
        else
        {
            if (root->right_child == nullptr)
            {
                root->right_child = ptrn;
                ptrn->parent = root;
                root->height = max(root->height, root->right_child->height + 1);
                return true;
            }
            else
            {
                bool val = BST(root->right_child).insert(n);
                root->height = max(root->height, root->right_child->height + 1);
                return val;
            }
        }
    }
}

bool BST::remove(char *s)
{
    Node *temp = search(s);

    if (temp == nullptr)
    {
        return false;
    }
    else if (temp->parent == nullptr)
    {
        if (temp->right_child == nullptr && temp->left_child == nullptr)
        {
            delete temp;
            root = new Node();
            return true;
        }
        else if (temp->right_child == nullptr)
        {
            temp->left_child->parent = nullptr;
            root = temp->right_child;
            delete temp;
            return true;
        }
        else if (temp->left_child == nullptr)
        {
            temp->right_child->parent = nullptr;
            root = temp->right_child;
            delete temp;
            return true;
        }
        else
        {
            Node *temp2 = BST(temp).successor(temp);
            string a = temp->key;
            temp->key = temp2->key;
            temp2->key = a;
            bool val = BST(temp2).remove(s);
            root->height = max(root->left_child->height, root->right_child->height) + 1;
            return val;
        }
    }
    else if (temp->left_child == nullptr && temp->right_child == nullptr)
    {
        if (temp->parent->right_child == temp)
        {
            temp->parent->right_child = nullptr;
            if (temp->parent->left_child != nullptr)
            {
                temp->parent->height = temp->parent->left_child->height + 1;
            }
            else
            {
                temp->parent->height = 0;
            }

            delete temp;
            return true;
        }
        else
        {

            temp->parent->left_child = nullptr;
            if (temp->parent->right_child != nullptr)
            {
                temp->parent->height = temp->parent->right_child->height + 1;
            }
            else
            {
                temp->parent->height = 0;
            }
            delete temp;
            return true;
        }
    }

    else if (temp->left_child == nullptr)
    {
        if (temp->parent->right_child == temp)
        {
            temp->parent->right_child = temp->right_child;

            temp->right_child->parent = temp->parent;

            if (temp->parent->left_child != nullptr)
            {
                temp->parent->height = max(temp->parent->left_child->height, temp->right_child->height) + 1;
            }
            else
            {
                temp->parent->height = temp->right_child->height + 1;
            }

            delete temp;
            return true;
        }
        else
        {

            temp->parent->left_child = temp->right_child;

            temp->right_child->parent = temp->parent;

            if (temp->parent->right_child != nullptr)
            {
                temp->parent->height = max(temp->parent->right_child->height, temp->right_child->height) + 1;
            }
            else
            {
                temp->parent->height = temp->right_child->height + 1;
            }

            delete temp;
            return true;
        }
    }
    else if (temp->right_child == nullptr)
    {
        if (temp->parent->right_child == temp)
        {
            temp->parent->right_child = temp->left_child;

            temp->left_child->parent = temp->parent;

            if (temp->parent->left_child != nullptr)
            {
                temp->parent->height = max(temp->parent->left_child->height, temp->left_child->height) + 1;
            }
            else
            {
                temp->parent->height = temp->left_child->height + 1;
            }

            delete temp;
            return true;
        }
        else
        {

            temp->parent->left_child = temp->left_child;

            temp->left_child->parent = temp->parent;

            if (temp->parent->right_child != nullptr)
            {
                temp->parent->height = max(temp->parent->right_child->height, temp->left_child->height) + 1;
            }
            else
            {
                temp->parent->height = temp->left_child->height + 1;
            }

            delete temp;
            return true;
        }
    }
    else
    {
        Node *temp2 = BST(temp).successor(temp);
        string a = temp->key;
        temp->key = temp2->key;
        temp2->key = a;
        bool val = BST(temp2).remove(s);
        temp->height = max(temp->right_child->height, temp->left_child->height) + 1;
        return val;
    }
}

struct Node *BST::successor(struct Node *n)
{
    Node *temp = n;
    if (temp == nullptr)
    {
        return nullptr;
    }

    if (temp->right_child != nullptr)
    {
        return BST(temp->right_child).minim();
    }

    while (temp->parent != nullptr && temp->parent->right_child == temp)
    {
        temp = temp->parent;
    }
    return temp->parent;
}

struct Node *BST::predecessor(struct Node *n)
{
    Node *temp = n;
    if (temp == nullptr)
    {
        return nullptr;
    }

    if (temp->left_child != nullptr)
    {
        return BST(temp->left_child).minim();
    }

    while (temp->parent != nullptr && temp->parent->left_child == temp)
    {
        temp = temp->parent;
    }
    return temp->parent;
}

int main()
{

    BST *tree = new BST();
    srand(10);
    Node *n = new Node();
    char a;
    int x;
    char *word = new char[32];

    // while (true)
    // {

    // cin >> a;
    a = 'a';
    if (a == 'e') //enter
    {
        cin >> n->key;
        tree->insert(*n);
        tree->traverse();
    }
    else if (a == 'd') //delete
    {
        cin >> word;
        tree->remove(word);
        tree->traverse();
    }
    else if (a == 's') //show
    {
        ;
    }

    else if (a == 'a')
    {
        for (int len = 10000; len < 5000000; len *= 2)
        {
            double time = 0;
            for (int i = 0; i < len; i++)
            {
                n->key = to_string(rand());

                auto start = std::chrono::system_clock::now(); //timer begin
                tree->insert(*n);
                auto now = std::chrono::system_clock::now(); //timer end

                std::chrono::duration<double> diff = now - start;
                time += diff.count();
            }
            cout << time << " seconds taken per " << len << " operations" << endl;
        }
    }
    else if (a == 'n')
    { //new object
        delete tree;
        tree = new BST();
    }
    //     else
    //     {
    //         break;
    //     }
    // }
}
