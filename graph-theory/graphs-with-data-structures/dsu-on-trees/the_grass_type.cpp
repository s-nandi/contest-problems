//dsu on tree (two-pass calculation)
//https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/the-grass-type/description/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define ll long long

typedef vector<vector<int>> graph;

vector <int> values; vector <ll> sols;

map <int, int> dfs(graph &g, int curr, int prev = -1)
{
    map <int, int> current = {{values[curr], 1}};
    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        auto res = dfs(g, neighbor, curr);
        if (res.size() > current.size()) swap(res, current);
        for (auto elem: res)
        {
            if (values[curr] % elem.first == 0) sols[curr] += (ll) elem.second * current[values[curr] / elem.first];
        }
        for (auto elem: res)
        {
            current[elem.first] += elem.second;
        }
    }
    return current;
}

int main()
{
    int n;
    cin>>n;

    graph g(n);
    values.resize(n), sols.resize(n);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; i++)
    {
        cin>>values[i];
    }

    dfs(g, 0);

    ll sol = 0;
    for (int i: sols) sol += i;
    cout<<sol<<'\n';

    return 0;
}
