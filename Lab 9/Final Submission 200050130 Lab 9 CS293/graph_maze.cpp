/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 9

Solving a Maze using Graphs
*/

#include <bits/stdc++.h>
using namespace std;

class graph
{

    vector<vector<int>> adjacency_list;
    int size;
    int rows;
    int columns;

public:
    graph(int rows, int columns)
    {
        size = rows*columns;
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i <= size; i++)
        {
            vector<int> v;
            adjacency_list.push_back(v);
        }
    }

    void neighbour(int i, int j)
    {
        adjacency_list[i].push_back(j);
        adjacency_list[j].push_back(i);
    }

    void BFS(int s, int final)
    {
        bool *visited = new bool[size + 1];
        string *path = new string[size+1];
        for (int i = 0; i <= size; i++){
            visited[i] = false;
            path[i]="";
        }

        list<int> queue;

        visited[s] = true;
        path[s]="Start ("+ to_string((s-1)/columns+1)+","+to_string((s-1)%columns+1)+")";
        queue.push_back(s);

        while (!queue.empty())
        {
            s = queue.front();
            // cout << s << " "<<path[s]<<endl;
            queue.pop_front();

            for (auto i : adjacency_list[s])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    path[i] = path[s] + " ("+ to_string((i-1)/columns+1)+","+to_string((i-1)%columns+1)+")";
                    queue.push_back(i);
                }
            }
        }

        cout<<path[final]<<" Finish"<<endl;
    }
};

int main()
{

    ifstream file;
    file.open("input.txt");
    if (!file)
    { // file couldn't be opened
        cout << "Error, file not present" << endl;
        return 0;
    }
    int rows, columns;
    file >> rows >> columns;
    graph *g = new graph((rows - 1) , (columns - 1));

    char horizontal[rows + 1][columns];
    char vertical[rows][columns + 1];

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            file >> horizontal[i][j];
        }
    }

    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j <= columns; j++)
        {
            file >> vertical[i][j];
        }
    }
    file.close();

    //There will be rows-1 * columns-1 cells.
    for (int i = 2; i < rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            if ('0' == horizontal[i][j])
            {
                g->neighbour((i - 1) * (columns - 1) + j, (i - 2) * (columns - 1) + j);
            }
        }
    }

    for (int i = 1; i < rows; i++)
    {
        for (int j = 2; j < columns; j++)
        {
            if ('0' == vertical[i][j])
            {
                g->neighbour((i - 1) * (columns - 1) + j, (i - 1) * (columns - 1) + j - 1);
            }
        }
    }

    //number of each cell (i, j) is columns*(i-1)+j
    g->BFS(1, (rows-1)*(columns-1));


    return 0;
}