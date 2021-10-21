#include <bits/stdc++.h>

using namespace std;

class graph
{

    vector<vector<int>> adjacency_list;
    int size;

public:
    graph(int size)
    {
        this->size = size;
        for (int i = 0; i <= size; i++)
        {
            vector<int> v;
            adjacency_list.push_back(v);
        }
    }

    int neighbour(int i, int j)
    {
        if (i == j)
        {
            return 0;
        }
        auto iterator = find(adjacency_list[i].begin(), adjacency_list[i].end(), j);
        if (iterator != adjacency_list[i].end())
        {
            return 0;
        }
        adjacency_list[i].push_back(j);
        adjacency_list[j].push_back(i);
        return 1;
    }

    void TRAVERSAL(int s, bool flag)
    {
        bool *visited = new bool[size + 1];
        int *distance = new int[size + 1];
        for (int i = 0; i <= size; i++)
        {
            visited[i] = false;
            distance[i] = 99999;
        }

        deque<int> list;

        visited[s] = true;
        distance[s] = 0;
        list.push_front(s);

        while (!list.empty())
        {
            // s = list.front();
            if (flag)
            {
                s = list.back();
                list.pop_back();
            }
            else
            {
                s = list.front();
                list.pop_front();
            }

            cout << s << " " << distance[s] << endl;
            for (auto i : adjacency_list[s])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    distance[i] = distance[s] + 1;
                    list.push_front(i);
                }
            }
        }
        delete visited;
        delete distance;
    }

    void bipartite(int s)
    {
        bool *visited = new bool[size + 1];
        int *color = new int[size + 1];
        string *path = new string[size+1];
        for (int i = 0; i <= size; i++)
        {
            visited[i] = false;
            color[i] = 99999;
            path[i]="";

        }

        deque<int> list;

        visited[s] = true;
        color[s] = 1;
        path[s]=to_string(s)+" ";
        list.push_front(s);

        while (!list.empty())
        {

            s = list.front();
            list.pop_front();

            cout << s << " " << color[s] << endl;
            for (auto i : adjacency_list[s])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    color[i] = color[s] * -1;
                    path[i] = path[s] + to_string(i)+" ";
                    list.push_front(i);
                }
                else{
                    if(color[i]==color[s]){
                        cout<<"NOT BIPARTITE!!\n";
                        cout<<"The clashing cycle formed is- "<<path[i]<<"and "<<path[s]<<"\n";
                        return;
                    }
                }
            }
        }
        cout<<"IT IS BIPARTITE!!\n";

    }
};
int random(int n)
{
    return 1.0 * rand() * n / RAND_MAX;
}

int main()
{
    int n;
    cin >> n;

    graph *g = new graph(n);

    for (int i = 0; i < 2 * n;)
    {
        i += g->neighbour(random(n), random(n));
    }


    
    cout<<"\nBFS\n";
    g->TRAVERSAL(0, true);
    cout<<"\nDFS\n";
    g->TRAVERSAL(0, false);
    cout<<"\nBipartite check\n";
    g->bipartite(0);
    // cout << "HELLO\n";

    return 0;
}