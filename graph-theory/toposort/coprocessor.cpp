//toposort, greedy
//http://codeforces.com/contest/909/problem/E

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector <vector<int>> graph;

int toposort(graph &g, vector <int> &type)
{
    int n = g.size();
    vector <int> inDegree(n);
    queue <int> q[2];

    for (int i = 0; i < n; i++)
    {
        for (int j: g[i])
        {
            inDegree[j]++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q[type[i]].push(i);
        }
    }

    int sol = 0;
    while(!q[0].empty() or !q[1].empty())
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == 1 and !q[i].empty()) sol++;

            while (!q[i].empty())
            {
                int curr = q[i].front();
                q[i].pop();

                for (int neighbor: g[curr])
                {
                    inDegree[neighbor]--;
                    if (inDegree[neighbor] == 0)
                    {
                        q[type[neighbor]].push(neighbor);
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

    graph g(n);
    vector <int> type(n);

    for (int i = 0; i < n; i++)
    {
       cin>>type[i];
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        g[b].push_back(a);
    }

    cout<<toposort(g, type)<<'\n';

    return 0;
}
