//dfs on tree
//http://codeforces.com/contest/981/problem/C

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

int common = -1, maxdegree = 0;
vector <int> res;

void findCommon(graph &g, int curr, int prev)
{
    if (g[curr].size() > maxdegree)
    {
        common = curr;
        maxdegree = g[curr].size();
    }
    for (edge e: g[curr]) if (e.to != prev)
    {
        findCommon(g, e.to, curr);
    }
}

bool hasSol(graph &g, int curr, int prev)
{
    int out = 0;
    for (edge e: g[curr]) if (e.to != prev)
    {
        if (!hasSol(g, e.to, curr))
            return false;
        out++;
    }
    if (out > 1 and curr != common) return false;

    if (out == 0)
        res.push_back(curr);

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    findCommon(g, 0, -1);

    if (!hasSol(g, common, -1))
    {
        cout<<"No"<<'\n';
    }
    else
    {
        cout<<"Yes"<<'\n';
        cout<<res.size()<<'\n';
        for (int elem: res)
        {
            cout<<common + 1 <<" "<<elem + 1<<'\n';
        }
    }

    return 0;
}
