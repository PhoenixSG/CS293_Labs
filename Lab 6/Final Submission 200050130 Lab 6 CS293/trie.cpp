/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 6

Compressed Tries
*/
#include <bits/stdc++.h>
using namespace std;

// class text
// {
// public:
string words[10000];
// };

class trie_node
{
private:
    trie_node *next[27];
    int tuple_3[3];
    int number_of_times;
    bool root;
    bool filled;

public:
    trie_node()
    {
        for (int i = 0; i < 27; i++)
        {
            next[i] = nullptr;
        }
        tuple_3[0] = -1;
        tuple_3[1] = -1;
        tuple_3[2] = -1;
        root = false;
        filled = false;
    }
    void make_root()
    {
        root = true;
    }
    void insert(string s, int ind, int start)
    {
        // assert(words[ind] == s);
        if (root)
        {
            if (next[s[0] - 'a'] == nullptr)
            {
                next[s[0] - 'a'] = new trie_node();
            }
            next[s[0] - 'a']->insert(s, ind, 0);
        }
        else
        {
            if (!filled)
            {
                tuple_3[0] = ind;
                tuple_3[1] = start;
                tuple_3[2] = s.length();
                next[26] = new trie_node();
                filled = true;
            }
            else
            {
                int length = tuple_3[2];
                int i;
                for (i = 0; i < length; i++)
                {
                    if (s[i] != words[tuple_3[0]][tuple_3[1] + i])
                    {
                        break;
                    }
                }
                //i gives the number of matches
                if (length >= s.length())
                {
                    if (i == length)
                    {
                        cout << s << " already Present!" << endl;
                        return;
                    }
                    else
                    {
                        if (next[words[tuple_3[0]][tuple_3[1] + i] - 'a'] == nullptr)
                        {
                            next[words[tuple_3[0]][tuple_3[1] + i] - 'a'] = new trie_node();
                        }
                        next[words[tuple_3[0]][tuple_3[1] + i] - 'a']->insert(words[tuple_3[0]].substr(tuple_3[1] + i, length - i), tuple_3[0], tuple_3[1] + i);
                        delete(next[26]);
                        next[26]=nullptr;
                        if(i==s.length()){
                            next[26]=new trie_node();
                            tuple_3[2]=i;
                            return;
                        }
                        if (next[s[i] - 'a'] == nullptr)
                        {
                            next[s[i] - 'a'] = new trie_node();
                        }
                        tuple_3[2]=i;
                        next[s[i] - 'a']->insert(s.substr(i, s.length() - i), ind, i + start);
                    }
                }
                else
                {
                    if (i < length)
                    {
                        if (next[words[tuple_3[0]][tuple_3[1] + i] - 'a'] == nullptr)
                        {
                            next[words[tuple_3[0]][tuple_3[1] + i] - 'a'] = new trie_node();
                        }
                        if (next[s[i] - 'a'] == nullptr)
                        {
                            next[s[i] - 'a'] = new trie_node();
                        }
                        tuple_3[2]=i;
                        delete(next[26]);
                        next[26]=nullptr;
                        next[s[i] - 'a']->insert(s.substr(i, s.length() - i), ind, i + start);
                        next[words[tuple_3[0]][tuple_3[1] + i] - 'a']->insert(words[tuple_3[0]].substr(tuple_3[1] + i, length - i), tuple_3[0], tuple_3[1] + i);
                    }
                    else if (i == length)
                    {

                        if (next[s[i] - 'a'] == nullptr)
                        {
                            next[s[i] - 'a'] = new trie_node();
                        }
                        next[s[i] - 'a']->insert(s.substr(i, s.length() - i), ind, i + start);
                        next[26] = new trie_node();
                    }
                }
            }
        }
    }
    int find(string s, string full)
    {
        if (root)
        {
            if (next[s[0] - 'a'] == nullptr)
            {
                cout << full << " is not present in the text." << endl;
                return 0;
            }
            return next[s[0] - 'a']->find(s,s);
        }
        if (!filled)
        {
            cout << full << " is not present in the text." << endl;
            return 0;
        }
        else
        {
            int length = tuple_3[2];
            int i;
            for (i = 0; i < length; i++)
            {
                if (s[i] != words[tuple_3[0]][tuple_3[1] + i])
                {
                    if(i==s.length()){
                    cout << full << " present at word number " << tuple_3[0]<< endl;
                    cout<<"The full word is "<<words[tuple_3[0]]<<endl;
                    return 0;
                    }
                    cout << full << " is not present in the text." << endl;
                    return 0;
                }
            }
            //i gives the number of matche
            if (i == s.length())
            {
                // if (next[26] != nullptr)
                // {
                    cout << full << " present at word number " << tuple_3[0]<< endl;
                    cout<<"The full word is "<<words[tuple_3[0]]<<endl;

                // }
                return 0;
            }
            else
            {
                if (next[s[i] - 'a'] == nullptr)
                {
                    cout << full << " is not present in the text." << endl;
                    return 0;
                }
                return next[s[i] - 'a']->find(s.substr(i), full);
            }
        }
    }
};

int main()
{

    ifstream file;
    file.open("text.txt");

    trie_node *trie = new trie_node();
    trie->make_root();
    if (!file)
    { // file couldn't be opened
        cout << "Error, file not present" << endl;
        return 0;
    }

    string s;
    file >> s;
    int index = 0;
    while (!file.eof())
    {
        words[index++] = s;
        trie->insert(s, index - 1, 0);
        file >> s;
    }
    file.close();
    cout << "File Read!" << endl;
    cin>>s;
    while (s != "x")
    {
        trie->find(s, s);
        cout<<endl;
        cin >> s;
    }
    return 0;
}