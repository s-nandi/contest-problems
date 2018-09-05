// dynamic connectivity (delete only, finding combined size of all k-connected components)
// https://codeforces.com/contest/1037/problem/E

#include <bits/stdc++.h>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

int n, m, k;

vector <int> removed, used, degree;
int removeNode(graph &g, int curr, int pid = -1)
{
    if (removed[curr] or degree[curr] >= k)
        return 0;
    removed[curr] = true;

    int acc = 1;
    for (edge e: g[curr]) if (!used[e.id])
    {
        --degree[e.to];
        used[e.id] = true;
        acc += removeNode(g, e.to, e.id);
    }
    return acc;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m>>k;

    graph g(n);
    vector <pair<int, int>> changes(m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        changes[i] = {a, b};
    }

    degree.resize(n);
    for (int i = 0; i < n; i++)
    {
        degree[i] = g[i].size();
    }

    removed.resize(n), used.resize(m);
    int sol = n;
    for (int i = 0; i < n; i++) if (!removed[i])
    {
        if (degree[i] < k)
            sol -= removeNode(g, i);
    }

    vector <int> sols(m);
    for (int i = m - 1; i >= 0; i--)
    {
        sols[i] = sol;
        int a = changes[i].first, b = changes[i].second;

        if (removed[a] or removed[b] or used[i])
            continue;

        --degree[a], --degree[b];
        used[i] = true;

        sol -= removeNode(g, a);
        sol -= removeNode(g, b);
    }

    for (int i: sols)
        cout<<i<<'\n';

    return 0;
}
