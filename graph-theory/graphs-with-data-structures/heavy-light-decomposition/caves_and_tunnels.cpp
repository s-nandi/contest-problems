//heavy-light decomposition, segment tree, node increment updates, path maximum queries
//http://acm.timus.ru/problem.aspx?space=1&num=1553

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

    void modify(int p, int v)
    {
        p += sz;
        elements[p] += v;
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

struct edge{int to;};
typedef vector <vector<edge>> graph;

struct heavyLightDecomposition
{
    int sz, timer = 0;
    bool edgeWeighted;
    vector <int> parent, sizes, root, position;
    graph g;
    segmentTree st;

    heavyLightDecomposition(int s, bool e)
    {
        sz = s;
        st.initialize(sz);
        parent.resize(sz, -1), sizes.resize(sz, -1), root.resize(sz), position.resize(sz);
        edgeWeighted = e;
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
            {
                swap(e, g[curr][0]);
            }
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

    void build(graph &gr, int rt)
    {
        g = gr;
        reorder(rt);
        tour(rt);
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

    void modify(int p, int v)
    {
        st.modify(position[p], v);
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

    int n;
    cin>>n;

    graph g(n);
    heavyLightDecomposition hld(n, false);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }
    hld.build(g, 0);

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        char type;
        int a, b;
        cin>>type>>a>>b;
        if (type == 'I')
        {
            hld.modify(--a, b);
        }
        else
        {
            cout<<hld.query(--a, --b)<<'\n';
        }
    }

    return 0;
}
