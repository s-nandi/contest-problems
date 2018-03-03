//heavy-light decomposition, segment tree, edge assignment updates, path maximum queries
//http://www.spoj.com/problems/QTREE/

#include <iostream>
#include <vector>

using namespace std;

struct segmentTree
{
    int sz;
    vector <int> elements;

    void initialize(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void initVal(int p, int v)
    {
        elements[p + sz] = v;
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = max(elements[i << 1], elements[i << 1 | 1]);
        }
    }

    void modify(int p, int v)
    {
        p += sz;
        elements[p] = v;

        while (p >= 2)
        {
            elements[p >> 1] = max(elements[p], elements[p ^ 1]);
            p >>= 1;
        }
    }

    int query(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                acc = max(acc, elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                acc = max(acc, elements[r]);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc;
    }
};

struct edge
{
    int to, weight;
};

typedef vector <vector<edge>> graph;

struct heavyLightDecomposition
{
    int sz, timer = 0;
    bool edgeWeighted;
    vector <int> parent, sizes, root, value, position;
    graph g;
    segmentTree st;

    heavyLightDecomposition(int s, bool e)
    {
        sz = s;
        st.initialize(sz);
        parent.resize(sz, -1), sizes.resize(sz, -1), root.resize(sz), value.resize(sz), position.resize(sz);
        edgeWeighted = e;
    }

    void reorder(int curr)
    {
        sizes[curr] = 1;
        for (edge &e: g[curr]) if (e.to != parent[curr])
        {
            parent[e.to] = curr, value[e.to] = e.weight;
            reorder(e.to);
            sizes[curr] += sizes[e.to];
            if (sizes[e.to] > sizes[g[curr][0].to])
            {
                swap(e, g[curr][0]);
            }
        }
    }

    void tour(int curr)
    {
        position[curr] = timer++;
        st.initVal(position[curr], value[curr]);
        for (edge e: g[curr]) if (e.to != parent[curr])
        {
            root[e.to] = e.to == g[curr][0].to ? root[curr] : e.to;
            tour(e.to);
        }
    }

    void build(graph &gr, int rt)
    {
        g = gr;
        reorder(rt);
        tour(rt);
        st.build();
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

    void modify(int a, int b, int v)
    {
        st.modify(max(position[a], position[b]), v);
    }

    int query(int l, int r)
    {
        int res = 0;
        process(l, r, [this, &res](int l, int r) { res = max(res, st.query(l, r)); });
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin>>tests;
    while (tests--)
    {
        int n;
        cin>>n;

        graph g(n);
        heavyLightDecomposition hld(n, true);
        vector <pair <int, int>> ithEdge(n + 1);

        for (int i = 0; i < n - 1; i++)
        {
            int a, b, v;
            cin>>a>>b>>v;
            --a; --b;
            g[a].push_back({b, v});
            g[b].push_back({a, v});
            ithEdge[i + 1] = {a, b};
        }
        hld.build(g, 0);

        while(true)
        {
            string type;
            cin>>type;
            if (type[0] == 'C')
            {
                int p, v;
                cin>>p>>v;
                hld.modify(ithEdge[p].first, ithEdge[p].second, v);
            }
            else if(type[0] == 'Q')
            {
                int l, r;
                cin>>l>>r;
                cout<<hld.query(--l, --r)<<'\n';
            }
            else break;
        }
    }

    return 0;
}
