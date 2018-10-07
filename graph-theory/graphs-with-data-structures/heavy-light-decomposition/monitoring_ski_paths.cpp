// heavy light decomposition (path sum query, node increment update w/ fenwick tree), greedy (postorder processing), building subgraphs from forest of trees
// https://open.kattis.com/problems/monitoringskipaths
// 2018 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

struct fenwickTree
{
    vector <int> elements;

    fenwickTree(int s = 0){elements.resize(s + 1);}

    void modify(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i))
            elements[i] += v;
    }

    int query(int i)
    {
        int ans = 0;
        for (i++; i > 0; i -= i & (-i))
            ans += elements[i];
        return ans;
    }

    int query(int l, int r) {return query(r) - query(l - 1);}
};

struct heavyLightDecomposition
{
    int sz, timer = 0;
    bool edgeWeighted;
    graph g;
    vector <int> parent, sizes, root, position;
    fenwickTree ft;

    heavyLightDecomposition(graph &gr, int rt, bool e)
    {
        g = gr, sz = g.size(), edgeWeighted = e;
        ft = fenwickTree(sz);
        parent.resize(sz, -1), sizes.resize(sz, -1), root.resize(sz), position.resize(sz);
        reorder(rt), tour(rt);
    }

    void reorder(int curr)
    {
        sizes[curr] = 1;
        for (edge &e: g[curr]) if (e.to != parent[curr])
        {
            parent[e.to] = curr;
            reorder(e.to);
            sizes[curr] += sizes[e.to];
            if(sizes[e.to] > sizes[g[curr][0].to])
                swap(e, g[curr][0]);
        }
    }

    void tour(int curr)
    {
        position[curr] = timer++;
        for (edge e: g[curr]) if (e.to != parent[curr])
        {
            root[e.to] = e.to == g[curr][0].to ? root[curr] : e.to;
            tour(e.to);
        }
    }

    template <class Operation>
    void process(int l, int r, Operation op)
    {
        for (; root[l] != root[r]; r = parent[root[r]])
        {
            if (position[root[l]] > position[root[r]]) swap(l, r);
            op(position[root[r]], position[r]);
        }
        if (edgeWeighted and l == r) return;
        if (position[l] > position[r]) swap(l, r);
        op(position[l] + edgeWeighted, position[r]);
    }

    void modifyNode(int p, int v)
    {
        ft.modify(position[p], v);
    }

    int queryPath(int l, int r)
    {
        int res = 0;
        process(l, r, [this, &res](int l, int r) {res += ft.query(l, r);});
        return res;
    }
};

vector <int> used;
map <int, vector<int>> paths;
void solve(graph &g, int curr, heavyLightDecomposition &hld, map <int, int> &mapping, map <int, int> &invmap)
{
    for (edge e: g[curr])
        solve(g, e.to, hld, mapping, invmap);

    if (paths.count(invmap[curr]))
    {
        bool useless = true;
        for (int t: paths[invmap[curr]])
        {
            int h = hld.queryPath(mapping[t], curr);
            if(h == 1)
                useless = false;
        }
        if (useless)
            hld.modifyNode(curr, -1);
        else
            used[invmap[curr]] = 1;
    }
}

int numNodes;
void getMapping(graph &g, int curr, map <int, int> &mapping, map <int, int> &invmapping)
{
    mapping[curr] = numNodes++;
    invmapping[mapping[curr]] = curr;
    for (edge e: g[curr])
        getMapping(g, e.to, mapping, invmapping);
}

void getSubgraph(graph &g, graph &sg, int curr, map <int, int> &mapping)
{
    int from = mapping[curr];
    for (edge e: g[curr])
    {
        int to = mapping[e.to];
        sg[from].push_back({to});
        getSubgraph(g, sg, e.to, mapping);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k, m;
    cin >> n >> k >> m;

    graph g(n);
    vector <int> inDegrees(n);
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        inDegrees[v]++;
        g[u].push_back({v});
    }

    for (int i = 0; i < m; i++)
    {
        int s, t;
        cin >> s >> t;
        paths[--s].push_back(--t);
    }

    used.resize(n);
    for (int i = 0; i < n; i++) if (inDegrees[i] == 0)
    {
        numNodes = 0;

        map <int, int> mapping, invmap;
        getMapping(g, i, mapping, invmap);

        graph sg(numNodes);
        getSubgraph(g, sg, i, mapping);

        heavyLightDecomposition hld(sg, mapping[i], false);
        for (auto elem: mapping) if (paths.count(elem.first))
            hld.modifyNode(elem.second, 1);

        solve(sg, mapping[i], hld, mapping, invmap);
    }

    int sol = 0;
    for (int i = 0; i < n; i++)
        sol += used[i];
    cout << sol << '\n';
}
