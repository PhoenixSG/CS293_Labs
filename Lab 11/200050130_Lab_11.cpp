#include <bits/stdc++.h>

using namespace std;

class graph
{

    vector<vector<int>> adjacency_list;
    vector<vector<int>> reversal_list;
    int size;

public:
    graph(int size)
    {
        this->size = size;
        for (int i = 0; i <= size; i++)
        {
            vector<int> v, w;
            adjacency_list.push_back(v);
            reversal_list.push_back(w);

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
        reversal_list[j].push_back(i);
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
        for (int i = 0; i <= size; i++)
        {
            if (visited[i] != true)
            {
                cout << s << " and " << i << " are not strongly connected, Traversal 1\n";
                delete visited;
                delete distance;
                return;
            }
        }
        cout << "All well connected in traversal 1\n";
        delete visited;
        delete distance;
    }

    void TRAVERSAL_reverse(int s, bool flag)
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
            for (auto i : reversal_list[s])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    distance[i] = distance[s] + 1;
                    list.push_front(i);
                }
            }
        }
        for (int i = 0; i <= size; i++)
        {
            if (visited[i] != true)
            {
                cout << s << " and " << i << " are not strongly connected, Traversal 2\n";
                delete visited;
                delete distance;

                return;
            }
        }
        cout << "All well connected in traversal 2\n";
        delete visited;
        delete distance;
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

    for (int i = 0; i < 3 * n;)
    {
        i += g->neighbour(random(n), random(n));
    }

    cout << "\nDFS\n";
    g->TRAVERSAL(0, false);
    g->TRAVERSAL_reverse(0, false);

    return 0;
}