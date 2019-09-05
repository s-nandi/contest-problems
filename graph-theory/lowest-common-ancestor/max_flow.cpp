//binary lifting (lca), prefix sums on tree
//http://www.usaco.org/index.php?page=viewproblem2&cpid=576
//2015 USACO december platinum

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

struct binaryLift
{
    int sz, h = 0;
    graph g;
    vector <vector<int>> table;
    vector <int> depths, prefixSums, cumulSums;

    binaryLift(graph &gr)
    {
        g = gr, sz = g.size();
        while (1 << h < sz) h++;
        table.resize(sz, vector<int>(h, -1)), depths.resize(sz), prefixSums.resize(sz), cumulSums.resize(sz);
        build(0);
    }

    void build(int curr, int depth = 0)
    {
        depths[curr] = depth;
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
        }
        for (edge e: g[curr]) if (e.to != table[curr][0])
        {
            table[e.to][0] = curr;
            build(e.to, depth + 1);
        }
    }

    int lca(int l, int r)
    {
        if (depths[l] > depths[r]) swap(l, r);
        for (int i = h - 1; i >= 0; i--)
        {
            if ((1 << i) & (depths[r] - depths[l]))
                r = table[r][i];
        }
        if (l == r) return l;
        for (int i = h - 1; i >= 0; i--) if (table[l][i] != table[r][i])
        {
            l = table[l][i], r = table[r][i];
        }
        return table[l][0];
    }

    void addFlow(int a, int b)
    {
        if (depths[a] > depths[b]) swap(a, b);
        int anc = lca(a, b);
        int par = table[anc][0];
        if (anc == a)
        {
            if (par != -1) prefixSums[par]--;
            prefixSums[b]++;
        }
        else
        {
            if (par != -1) prefixSums[par] --;
            prefixSums[anc]--;
            prefixSums[a]++, prefixSums[b]++;
        }
    }

    int pushFlow(int curr = 0, int prev = -1)
    {
        int currSum = prefixSums[curr];
        for (edge e: g[curr]) if (e.to != prev)
        {
            currSum += pushFlow(e.to, curr);
        }
        cumulSums[curr] = currSum;
        return currSum;
    }
};

int main()
{
    /*
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    */

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    binaryLift bl(g);
    for (int i = 0; i < k; i++)
    {
        int a, b;
        cin>>a>>b;
        bl.addFlow(--a, --b);
    }
    bl.pushFlow();
    cout<<*max_element(bl.cumulSums.begin(), bl.cumulSums.end())<<'\n';

    return 0;
}
