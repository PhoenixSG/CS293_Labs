/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 2

Implement Dictionary of Strings using Hashing
*/

#include "Dictionary.h"
#include <iostream>
#include <string.h>

using namespace std;



int Dictionary::hashValue(char *key)
{
    //Using x=33, for computing polynomial in Hash Code Map
    //Taking fibonacci constant as a
    int i = 0;
    double x = 33, a = 0.618033989, key_from_string = 0;

    //Using polynomial accumulation and roll-over compression starting from the left of the string.
    while (key[i] != '\0')
    {
        key_from_string *= x;
        key_from_string += int(key[i]);
        key_from_string *= a;
        key_from_string -= int(key_from_string);
        i++;
    }

    return int(N * key_from_string);
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
}

int Dictionary::findFreeIndex(char *key)
{
    int key_from_string = hashValue(key), i = 0;

    while (A[(key_from_string + i) % N].state != -1 && A[(key_from_string + i) % N].state != -2)
    {
        i++;
        if (i > N)
        {
            return -1;
        }
    }

    return (key_from_string + i) % N;

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
}

Dictionary::Dictionary()
{
    N = ARRAY_SIZE;
    A = new Entry[N];
} // Default constructor



bool Dictionary::put(struct Entry e)
{
    struct Entry *temp = get(e.data);

    if (temp != NULL)
    {
        temp->count++;
        cout<<"Increasing "<<e.data<<" count by 1"<<endl; 
        return true;
    }
    int key = findFreeIndex(e.data);
    if (key != -1)
    {
        A[key].data=e.data;
        A[key].count=1;
        A[key].state=0;
        cout<<"Putting "<<e.data<<" in "<<key<<endl;
        return true;
    }
    else
    {
        cout<<"FULL CAPACITY"<<endl;
        return false;
    }
}
struct Entry *Dictionary::get(char *key)
{
    int i = 0, key_generated = hashValue(key);
    while (A[(key_generated + i) % N].state != -2 && i < N)
    {
        if (strcmp(A[(key_generated + i) % N].data, key)==0)
        {

            return &A[(key_generated + i) % N];
        }
        i++;
    }
    return NULL;
}

bool Dictionary::remove(char *key)
{
    struct Entry *temp = get(key);
    if (temp == NULL)
    {
        cout<<"Key not found!"<<endl;
        return false;
    }
    temp->state = -1;
    cout<<"Removed Successfully"<<endl;
    return true;
}

void Dictionary::show()
{
    for (int i = 0; i < N; i++)
    {
        if (A[i].state != -2 && A[i].state!=-1)
        {
            cout<< A[i].data <<" "<<A[i].count<< endl;
        }
    }
}
