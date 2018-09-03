// bfs, greedy
// https://codeforces.com/contest/1037/problem/D

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

void sortEdges(graph &g, vector <int> &seq)
{
    vector <int> pos(seq.size());
    for (int i = 0; i < seq.size(); i++)
    {
        pos[seq[i]] = i;
    }
    auto cmp = [&pos](edge &a, edge &b)
    {
        return pos[a.to] < pos[b.to];
    };
    for (vector <edge>& v: g)
    {
        sort(v.begin(), v.end(), cmp);
    }
}

bool feasible(graph &g, vector <int> &seq)
{
    vector <int> visited(seq.size());
    queue <int> q;

    q.push(0);
    visited[0] = true;

    int it = 0;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (curr != seq[it])
            return false;
        it++;

        for (edge e: g[curr]) if (!visited[e.to])
        {
            q.push(e.to);
            visited[e.to] = true;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        --a[i];
    }
    sortEdges(g, a);
    bool res = feasible(g, a);
    if (res)
        cout<<"Yes"<<'\n';
    else
        cout<<"No"<<'\n';

    return 0;
}
