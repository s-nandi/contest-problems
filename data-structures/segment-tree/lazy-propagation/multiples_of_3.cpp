//segment tree, lazy propagation, finding # of divisible numbers in a range queries, increment updates
//http://www.spoj.com/problems/MULTQ3/

#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int counts[3];

    node lazyUpdate(int v)
    {
        node res;
        for (int i = 0; i < 3; i++)  res.counts[(i + v) % 3] = counts[i];
        return res;
    }

    node combine(node o)
    {
        node res;
        for (int i = 0; i < 3; i++) { res.counts[i] = counts[i] + o.counts[i]; }
        return res;
    }
};

struct segmentTree
{
    int sz, h = 0;
    vector <node> elements;
    vector <int> lazy;

    segmentTree(int s)
    {
        sz = s;
        while (1 << h < sz) h++;
        elements.resize(2 * sz, {{1, 0, 0}});
        lazy.resize(sz);
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    void apply(int p, int v)
    {
        elements[p] = elements[p].lazyUpdate(v);
        if (p < sz)
        {
            lazy[p] = (lazy[p] + v) % 3;
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
            for (int i = 0; i < 3; i++)
            {
                elements[p] = (elements[p << 1].combine(elements[p << 1 | 1])).lazyUpdate(lazy[p]);
            }
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

        siftUp(lSave);
        siftUp(rSave);
    }

    int query(int l, int r)
    {
        l += sz;
        r += sz;
        siftDown(l);
        siftDown(r);

        node acc = {{0, 0, 0}};
        while (l <= r)
        {
            if (l & 1)
            {
                acc = acc.combine(elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                acc = acc.combine(elements[r]);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc.counts[0];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    segmentTree st(n);
    st.build();

    for (int i = 0; i < m; i++)
    {
        int type, l, r;
        cin>>type>>l>>r;

        if (type == 0)
        {
            st.modify(l, r, 1);
        }
        else
        {
            cout<<st.query(l, r)<<'\n';
        }
    }

    return 0;
}
