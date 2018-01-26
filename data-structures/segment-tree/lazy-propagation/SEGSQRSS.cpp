//segment tree, lazy propagation (order/length dependent), sum of squares queries, range increment update, range assignment update
//http://www.spoj.com/problems/SEGSQRSS/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define INF 1231231234

struct node
{
    ll sum, sumSquares;

    node lazyUpdate(int v, int len, int t)
    {
        if (t == 0)
        {
            return {(ll) len * v, (ll) len * v * v};
        }
        else
        {
            return {sum + len * v, sumSquares + v * len + 2 * sum * v};
        }
    }

    node combine(node o)
    {
        return {sum + o.sum, sumSquares + o.sumSquares};
    }
};

struct segmentTree
{
    int sz, h = 0, NIL = -INF;
    vector <node> elements;
    vector <int> len, lazy[2];

    segmentTree(int s)
    {
        sz = s;
        while (1 << h < sz) h++;
        elements.resize(2 * sz), len.resize(2 * sz, 1), lazy[0].resize(sz, NIL), lazy[1].resize(sz, NIL);
    }

    node& operator [] (int i)
    {
        return elements[i + sz];
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
            len[i] = len[i << 1] + len[i << 1 | 1];
        }
    }

    void apply(int p, int v, int type)
    {
        elements[p] = elements[p].lazyUpdate(v, len[p], type);
        if (p < sz)
        {
            lazy[type][p] = v;
        }
    }

    void siftDown(int p)
    {
        for (int u = h; u >= 1; u--)
        {
            int i = p >> u;
            for (int t = 0; t < 2; t++)
            {
                if (lazy[t][i] != NIL)
                {
                    apply(i << 1, lazy[t][i], t);
                    apply(i << 1 | 1, lazy[t][i], t);
                    lazy[t][i] = NIL;
                }
            }
        }
    }

    void siftUp(int p)
    {
        p >>= 1;
        while (p >= 1)
        {
            elements[p] = elements[p << 1].combine(elements[p << 1 | 1]);
            for (int t = 0; t < 2; t++)
            {
                if (lazy[t][p] != NIL)
                {
                    elements[p] = elements[p].lazyUpdate(lazy[t][p], len[p], t);
                }
            }
            p >>= 1;
        }
    }

    void modify(int l, int r, int v, int t)
    {
        l += sz, r += sz;
        siftDown(l), siftDown(r);
        int lSave = l, rSave = r;
        while (l <= r)
        {
            if (l & 1)
            {
                apply(l, v, t);
                l++;
            }
            if (!(r & 1))
            {
                apply(r, v, t);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        siftUp(lSave), siftUp(rSave);
    }

    ll query(int l, int r)
    {
        l += sz, r += sz;
        siftDown(l), siftDown(r);
        node acc = {0, 0};
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
        return acc.sumSquares;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin>>tests;

    for (int test = 1; test <= tests; test++)
    {
        cout<<"Case "<<test<<":"<<'\n';
        int n, m;
        cin>>n>>m;

        segmentTree st(n);
        for (int i = 0; i < n; i++)
        {
            int num;
            cin>>num;
            st[i] = {num, num * num};
        }
        st.build();

        for (int i = 0; i < m; i++)
        {
            int type, l, r, v;
            cin>>type>>l>>r;
            if (type == 0 or type == 1)
            {
                cin>>v;
                st.modify(--l, --r, v, type);
            }
            else
            {
                cout<<st.query(--l, --r)<<'\n';
            }
        }
    }

    return 0;
}
