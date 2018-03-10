//dsu on trees (merging maps)
//http://codeforces.com/contest/600/problem/E

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define ll long long

typedef vector <vector<int>> graph;

struct node : map <int, int>
{
    int maxCount;
    ll sumColors;

    node(int color)
    {
        (*this)[color] = 1;
        maxCount = 1;
        sumColors = color;
    }
};

vector <int> colors;

node dfs(graph &g, int curr, int prev, vector <ll> &sol)
{
    node current(colors[curr]);
    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        node res = dfs(g, neighbor, curr, sol);
        if (res.size() > current.size()) swap(res, current);
        for (auto elem: res)
        {
            current[elem.first] += elem.second;
            if (current[elem.first] > current.maxCount)
            {
                current.maxCount = current[elem.first];
                current.sumColors = elem.first;
            }
            else if(current[elem.first] == current.maxCount)
            {
                current.sumColors += elem.first;
            }
        }
    }
    sol[curr] = current.sumColors;
    return current;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);
    colors.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>colors[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector <ll> sol(n);
    dfs(g, 0, -1, sol);

    for (auto i: sol)
    {
        cout<<i<<" ";
    }
    cout<<'\n';

    return 0;
}
