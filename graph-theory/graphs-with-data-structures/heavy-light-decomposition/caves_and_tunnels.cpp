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

vector <vector<int>> graph;

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
        for (int i: graph[curr])
        {
            if (i == parent[curr]) continue;

            parent[i] = curr;
            depth[i] = depth[curr] + 1;
            int childSize = precompute(i);
            if (childSize > maxChild)
            {
                heavy[curr] = i;
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

    graph.resize(n);
    heavyLightDecomposition hld(n, false);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    hld.build();

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        char type;
        cin>>type;
        if (type == 'I')
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
