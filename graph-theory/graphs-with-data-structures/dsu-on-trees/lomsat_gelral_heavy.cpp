//dsu on trees (arpa's style)
//http://codeforces.com/contest/600/problem/E

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct edge{int to;};
typedef vector <vector<edge>> graph;

vector <int> colors;
struct dsuOnTree
{
    int sz, timer = 0;
    graph g;
    vector <int> st, ft, ordered, sizes, heavy;
    int maxCount = 0; ll sumCount = 0; vector <int> counts; vector <ll> sols;

    dsuOnTree(graph &gr)
    {
        g = gr, sz = g.size();
        st.resize(sz), ft.resize(sz), ordered.resize(sz), sizes.resize(sz), heavy.resize(sz, -1);
        sols.resize(sz), counts.resize(sz + 1);
        tour(), dfs();
    }

    int tour(int curr = 0, int prev = -1)
    {
        sizes[curr] = 1;
        ordered[timer] = curr, st[curr] = timer++;
        for (edge e: g[curr]) if (e.to != prev)
        {
            sizes[curr] += tour(e.to, curr);
            if (heavy[curr] == -1 or sizes[e.to] > sizes[heavy[curr]])
                heavy[curr] = e.to;
        }
        ft[curr] = timer;
        return sizes[curr];
    }

    void add(int v)
    {
        int nw = ++counts[colors[v]];
        if (nw == maxCount) sumCount += colors[v];
        else if(nw > maxCount) maxCount = nw, sumCount = colors[v];
    }

    void rmv(int v){--counts[colors[v]];}

    void dfs(int curr = 0, int prev = -1, bool keep = false)
    {
        int oldCount = maxCount; ll oldSum = sumCount;
        for (edge e: g[curr]) if (e.to != prev and e.to != heavy[curr])
            dfs(e.to, curr);
        if (heavy[curr] != -1)
            dfs(heavy[curr], curr, true);
        for (edge e: g[curr]) if (e.to != prev and e.to != heavy[curr])
            for (int t = st[e.to]; t < ft[e.to]; t++)
                {add(ordered[t]);}
        add(curr);
        sols[curr] = sumCount;
        if (!keep)
        {
            for (int t = st[curr]; t < ft[curr]; t++)
                rmv(ordered[t]);
            maxCount = oldCount, sumCount = oldSum;
        }
    }
};

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
        g[a].push_back({b});
        g[b].push_back({a});
    }

    dsuOnTree dsu(g);
    for (auto i: dsu.sols) cout<<i<<" ";
    cout<<'\n';

    return 0;
}
