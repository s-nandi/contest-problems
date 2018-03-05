//dsu on trees (merging sets)
//http://codeforces.com/contest/931/problem/D

#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector<vector<int>> graph;

set <int> dfs(graph &g, int curr, int depth)
{
    set <int> possible;
    possible.insert(depth);

    for (int neighbor: g[curr])
    {
        auto res = dfs(g, neighbor, depth + 1);
        if (res.size() > possible.size()) swap(res, possible);
        for (int i: res)
        {
            if (possible.count(i)) possible.erase(i);
            else possible.insert(i);
        }
    }

    return possible;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);

    for (int i = 1; i < n; i++)
    {
        int p;
        cin>>p;
        g[--p].push_back(i);
    }

    auto possible = dfs(g, 0, 0);
    cout<<possible.size()<<'\n';

    return 0;
}
