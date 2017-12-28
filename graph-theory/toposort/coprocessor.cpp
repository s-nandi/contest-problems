//toposort(indegree), bfs
//http://codeforces.com/contest/909/problem/E

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector <int> e;
vector <vector<int>> graph;
vector <int> inDegree;

int solve()
{
    int n = graph.size();
    queue <int> q[2];

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q[e[i]].push(i);
        }
    }

    int sol = 0;

    while(!q[0].empty() or !q[1].empty())
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == 1 and !q[i].empty())
            {
                sol++;
            }

            while (!q[i].empty())
            {
                int top = q[i].front();
                q[i].pop();

                for (int neighbor: graph[top])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0)
                    {
                        q[e[neighbor]].push(neighbor);
                    }
                }
            }

        }
    }

    return sol;
}

int main()
{
    int n, m;
    cin>>n>>m;
    
    e.resize(n);

    for (int i = 0; i < n; i++)
    {
       cin>>e[i];
    }

    graph.resize(n);
    inDegree.resize(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        graph[b].push_back(a);
        inDegree[a]++;
    }

    cout<<solve()<<'\n';

    return 0;
}
