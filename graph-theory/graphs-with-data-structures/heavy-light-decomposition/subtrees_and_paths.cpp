//heavy-light decomposition, segment tree (lazy propagation), subtree increment updates, path maximum query
//https://www.hackerrank.com/challenges/subtrees-and-paths/problem

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234

struct segmentTree
{
    int sz, h = 0;
    vector <int> elements, lazy;

    void initialize(int s)
    {
        sz = s;
        while (1 << h < sz) h++;
        elements.resize(2 * sz), lazy.resize(sz);
    }

    void apply(int p, int v)
    {
        elements[p] += v;
        if (p < sz)
        {
            lazy[p] += v;
        }
    }

    void siftDown(int p)
    {
        for (int u = h; u >= 1; u--)
        {
            int i = p >> u;
            if (lazy[i] != 0)
            {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    void siftUp(int p)
    {
        p >>= 1;
        while (p >= 1)
        {
            elements[p] = max(elements[p << 1], elements[p << 1 | 1]) + lazy[p];
            p >>= 1;
        }
    }

    void modify(int l, int r, int v)
    {
        l += sz;
        r += sz;
        int lSave = l, rSave = r;
        while (l <= r)
        {
            if (l & 1)
            {
                apply(l, v);
                l++;
            }
            if (!(r & 1))
            {
                apply(r, v);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        siftUp(lSave), siftUp(rSave);
    }

    int query(int l, int r)
    {
        l += sz;
        r += sz;
        siftDown(l), siftDown(r);
        int acc = -INF;
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

typedef vector <vector<int>> graph;

struct heavyLightDecomposition
{
    int sz, timer = 0;
    bool edgeWeighted;
    vector <int> parent, sizes, root, position, endPosition;
    graph g;
    segmentTree st;

    heavyLightDecomposition(int s, bool e)
    {
        sz = s;
        st.initialize(sz);
        parent.resize(sz, -1), sizes.resize(sz, -1), root.resize(sz), position.resize(sz), endPosition.resize(sz);
        edgeWeighted = e;
    }

    void reorder(int curr)
    {
        sizes[curr] = 1;
        for (int &i: g[curr]) if (i != parent[curr])
        {
            parent[i] = curr;
            reorder(i);
            sizes[curr] += sizes[i];
            if (sizes[i] > sizes[g[curr][0]])
            {
                swap(i, g[curr][0]);
            }
        }
    }

    void tour(int curr)
    {
        position[curr] = timer++;
        for (int i: g[curr]) if (i != parent[curr])
        {
            root[i] = i == g[curr][0] ? root[curr] : i;
            tour(i);
        }
        endPosition[curr] = timer;
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
        st.modify(position[p], endPosition[p] - 1, v);
    }

    int query(int l, int r)
    {
        int res = -INF;
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
        int x, y;
        cin>>x>>y;
        --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    hld.build(g, 0);

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        string type;
        cin>>type;
        if (type[0] == 'a')
        {
            int p, v;
            cin>>p>>v;
            hld.modify(--p, v);
        }
        else
        {
            int l, r;
            cin>>l>>r;
            cout<<hld.query(--l, --r)<<'\n';
        }
    }

    return 0;
}
