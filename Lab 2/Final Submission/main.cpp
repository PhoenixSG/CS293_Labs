/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 2

Implement Dictionary of Strings using Hashing
*/

#include "Dictionary.cpp"
#include <iostream>
#include <chrono>

using namespace std;

//For bonus/optional, incomplete right now
// string alphabet = "abcdefghijklmnopqrstuvwxyz";

// char *random_string(int n)
// {
//     string res = "";
//     for (int i = 0; i < n; i++)
//         res = res + alphabet[rand() % 26];

//     return &res[0];
// }

//above string statement will iterate strings for all above characters in string

int main()
{
    srand(time(0));
    Dictionary* d=new Dictionary();
    char *word = new char[32];
    char a;
    int size;

    while (true)
    {
        cin >> a;
        if (a == 'e')//enter
        {
            Entry *temp = new Entry();
            cin >> temp->data;
            d->put(*temp);
            delete temp;
        }
        else if (a == 'd')//delete
        {
            cin >> word;
            d->remove(word);
        }
        else if (a == 's')//show
        {
            d->show();
        }
        //bonus/optional part attempt
        // else if (a == 'a')
        // {
        //     cin>>size;
        //     double time = 0;
        //     for (int i = 0; i < 1000; i++)
        //     {
        //         Entry *temp = new Entry();
        //         temp->data = random_string(size);
        //         cout<<temp->data<<endl;
        //         auto start = std::chrono::system_clock::now(); //timer begin
        //         d->put(*temp);
        //         auto now = std::chrono::system_clock::now(); //timer end

        //         std::chrono::duration<double> diff = now - start;
        //         time += diff.count();
        //         delete (temp);
        //     }
        //     cout << time << " seconds per 1000 operations, with words of length "<<size << endl;
        // }
        else if(a=='n'){ //new object
            delete d;
            d=new Dictionary();
        }
        else
        {
            break;
        }
    }

    return 0;
}