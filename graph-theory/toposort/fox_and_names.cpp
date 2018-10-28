// toposort w/ dfs, implicit graph (sentinel node makes construction simpler)
// http://codeforces.com/contest/510/problem/C

#include <bits/stdc++.h>

using namespace std;

const int alpha = 26;

struct edge{int to;};
typedef vector<vector<edge>> graph;

bool hasCycle(graph &g, int curr, vector <int> &color, deque <int> &topo)
{
    if (color[curr])
        return color[curr] == 2 ? true : false;
    color[curr] = 2;

    for (edge e: g[curr])
        if (hasCycle(g, e.to, color, topo))
            return true;

    color[curr] = 1;
    topo.push_front(curr);
    return false;
}

pair <bool, deque<int>> toposort(graph &g)
{
    deque <int> topo;
    vector <int> color(g.size());
    for (int i = 0; i < g.size(); i++)
        if (hasCycle(g, i, color, topo))
            return {false, topo};
    return {true, topo};
} // false: has cycle, true: no cycle

pair <int, int> getEdge(vector <int> &v1, vector <int> &v2)
{
    pair <int, int> res = {alpha, alpha};
    for (int i = 0; i < max(v1.size(), v2.size()); i++)
    {
        int a = i < v1.size() ? v1[i] : alpha;
        int b = i < v2.size() ? v2[i] : alpha;
        if (a != b)
            return {a, b};
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    graph g(alpha + 1);
    vector <vector<int>> names(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (char c: s)
            names[i].push_back(c - 'a');
    }

    for (int i = 0; i < n - 1; i++)
    {
        auto e = getEdge(names[i], names[i + 1]);
        if (e.first != e.second)
            g[e.first].push_back({e.second});
    }
    for (int i = 0; i < alpha; i++)
        g[alpha].push_back({i});

    auto topo = toposort(g);
    if(topo.first)
    {
        for (int i: topo.second) if (i != alpha)
            cout << char('a' + i);
        cout << '\n';
    }
    else
        cout << "Impossible" << '\n';
}
