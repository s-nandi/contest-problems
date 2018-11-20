// binary search on solution, 2-sat, strongly connected components (naive n^2)
// https://open.kattis.com/problems/collusionontwowheels
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

struct pt
{
    int x, y;
    int dist(const pt &o) const {return abs(x - o.x) + abs(y - o.y);}
};

int mapping(int i, bool neg)
{
    return 2 * i + neg;
}

bool reachable(graph &g, int curr, int dest, vector <int> &visited)
{
    if (curr == dest)
        return true;
    if (visited[curr])
        return false;
    visited[curr] = true;
    for (edge e: g[curr]) if (!visited[e.to])
        if (reachable(g, e.to, dest, visited))
            return true;
    return false;
}

bool feasible(vector <pt> &points, int dist)
{
    int n = points.size();
    graph g(2 * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (points[i].dist(points[j]) > dist)
            {
                g[mapping(i, false)].push_back({mapping(j, true)});
                g[mapping(i, true)].push_back({mapping(j, false)});
            }
        }
    }
    vector <int> visited(g.size()), sat(n);
    for (int i = 0; i < g.size(); i++)
    {
        fill(visited.begin(), visited.end(), 0);
        if (reachable(g, i, i ^ 1, visited))
            if (++sat[i / 2] == 2)
                return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <pt> points(n);
    for (pt &p: points)
        cin >> p.x >> p.y;

    int l = 0, r = 3000;
    while (l < r)
    {
        int m = (l + r) / 2;
        if (feasible(points, m))
            r = m;
        else
            l = m + 1;
    }
    cout << l << '\n';
}
