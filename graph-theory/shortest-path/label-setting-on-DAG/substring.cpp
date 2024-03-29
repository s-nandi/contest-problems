//longest path on DAG (label setting), toposort
//http://codeforces.com/contest/919/problem/D

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<int>> graph;

int longestPathDAG(graph &g, vector <int> &color)
{
    int n = g.size();
    queue <int> q;
    vector <int> inDegree(n);
    vector <vector<int>> d(n, vector<int>(26));

    for (int i = 0; i < n; i++)
    {
        for (int j: g[i])
        {
            inDegree[j]++;
        }
    }

    for (int i = 0; i < n; i++) if (inDegree[i] == 0)
    {
        q.push(i);
        d[i][color[i]] = 1;
    }

    int visited = 0, longest = 0;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        visited++;

        for (int i = 0; i < 26; i++)
        {
            longest = max(longest, d[curr][i]);
        }

        for (int neighbor: g[curr])
        {
            for (int i = 0; i < 26; i++)
            {
                d[neighbor][i] = max(d[neighbor][i], d[curr][i] + (color[neighbor] == i));
            }
            inDegree[neighbor]--;
            if(inDegree[neighbor] == 0) q.push(neighbor);
        }
    }
    if (visited < n) return -1;

    return longest;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    graph g(n);
    vector <int> color(n);

    string s;
    cin>>s;

    for (int i = 0; i < n; i++)
    {
        color[i] = s[i] - 'a';
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin>>x>>y;
        --x, --y;
        g[x].push_back(y);
    }

    cout<<longestPathDAG(g, color)<<'\n';

    return 0;
}
