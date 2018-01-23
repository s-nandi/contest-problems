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

vector <vector<edge>> graph;

struct heavyLightDecomposition
{
    int sz;
    bool edgeWeighted;
    vector <int> parent, heavy, depth, root, position;
    segmentTree st;

    heavyLightDecomposition(int s, bool e)
    {
        sz = s;
        st.initialize(sz);
        parent.resize(sz, -1); heavy.resize(sz, -1); depth.resize(sz); root.resize(sz); position.resize(sz);
        edgeWeighted = e;
    }

    int precompute(int curr)
    {
        int subtree = 1, maxChild = -1;
        for (edge e: graph[curr])
        {
            if (e.to == parent[curr]) continue;

            parent[e.to] = curr;
            depth[e.to] = depth[curr] + 1;
            int childSize = precompute(e.to);
            if (childSize > maxChild)
            {
                heavy[curr] = e.to;
                maxChild = childSize;
            }
            subtree += childSize;
        }
        return subtree;
    }

    void build()
    {
        precompute(0);
        int pos = 0;
        for (int node = 0; node < sz; node++)
        {
            if (parent[node] == -1 or heavy[parent[node]] != node)
            {
                for (int curr = node; curr != -1; curr = heavy[curr])
                {
                    root[curr] = node;
                    position[curr] = pos++;
                }
            }
        }
        for (int curr = 0; curr < sz; curr++)
        {
            for (edge e: graph[curr])
            {
                if (e.to == parent[curr]) continue;

                st.initVal(position[e.to], e.weight);
            }
        }
        st.build();
    }

    template <class Operation>
    void process(int l, int r, Operation op)
    {
        while (root[l] != root[r])
        {
            if (depth[root[l]] > depth[root[r]]) swap(l, r);
            op(position[root[r]], position[r]);
            r = parent[root[r]];
        }
        if (edgeWeighted and l == r) return;

        if (depth[l] > depth[r]) swap(l, r);
        op(position[l] + edgeWeighted, position[r]);
    }

    void modify(int a, int b, int v)
    {
        if (depth[a] > depth[b]) swap(a, b);
        st.modify(position[b], v);
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

        graph.clear(); graph.resize(n);
        heavyLightDecomposition hld(n, true);
        vector <pair <int, int>> ithEdge(n + 1);

        for (int i = 0; i < n - 1; i++)
        {
            int a, b, v;
            cin>>a>>b>>v;
            --a; --b;
            graph[a].push_back({b, v});
            graph[b].push_back({a, v});
            ithEdge[i + 1] = {a, b};
        }
        hld.build();

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
