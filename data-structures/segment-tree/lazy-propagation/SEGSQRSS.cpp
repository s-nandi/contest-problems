//segment tree, lazy propagation (iterative), sum of squares queries, range increment update, range assignment update
//http://www.spoj.com/problems/SEGSQRSS/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct node
{
    ll sum, sumSquares, lazy[2]; bool isLazy[2];
    int len = 1;

    node(){sum = 0, sumSquares = 0, lazy[0] = lazy[1] = isLazy[0] = isLazy[1] = false;}
    node(ll a, ll b, int c) : node() {sum = a, sumSquares = b, len = c;}
    void init(int i){sum = i, sumSquares = i * i;}

    node combine(node o)
    {
        return {sum + o.sum, sumSquares + o.sumSquares, len + o.len};
    }

    void processLazy(int t)
    {
        if (t == 0) sum = len * lazy[t], sumSquares = len * lazy[t] * lazy[t];
        else sumSquares += len * lazy[t] + 2 * sum * lazy[t], sum += len * lazy[t];
    }

    void setLazy(int v, int t)
    {
        lazy[t] = t ? lazy[t] + v : v, isLazy[t] = true;
    }

    void resetLazy(int t)
    {
        lazy[t] = 0, isLazy[t] = false;
    }
};

struct segmentTree
{
    int sz, h = 0;
    vector <node> elements;

    segmentTree(int s)
    {
        sz = s, calcHeight();
        elements.resize(2 * sz);
    }
    void calcHeight(){while(1 << h < sz) h++;}
    node& operator [] (int i){return elements[i + sz];}

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    void pushLazy(int p)
    {
        for (int t = 0; t < 2; t++) if (elements[p].isLazy[t])
        {
            elements[p].processLazy(t);
            if (p < sz)
            {
                int v = elements[p].lazy[t];
                elements[p << 1].setLazy(v, t), elements[p << 1 | 1].setLazy(v, t);
            }
            elements[p].resetLazy(t);
        }
    }

    void siftDown(int p)
    {
        for (int u = h; u >= 1; u--)
        {
            pushLazy(p >> u);
        }
    }

    void siftUp(int p)
    {
        pushLazy(p);
        while (p >= 2)
        {
            elements[p >> 1] = elements[p].combine(elements[p ^ 1]);
            p >>= 1;
        }
    }

    void modify(int l, int r, int v, int t)
    {
        siftDown(l += sz), siftDown(r += sz);
        auto lr = make_pair(l, r);
        for (; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1)
            {
                elements[l].setLazy(v, t);
                pushLazy(l);
            }
            if (!(r & 1))
            {
                elements[r].setLazy(v, t);
                pushLazy(r);
            }
        }
        siftUp(lr.first), siftUp(lr.second);
    }

    ll query(int l, int r)
    {
        node lacc, racc;
        siftDown(l += sz), siftDown(r += sz);
        for(; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r & 1)) racc = elements[r].combine(racc);
        }
        return lacc.combine(racc).sumSquares;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        cout<<"Case "<<test<<":"<<'\n';
        int n, m;
        cin>>n>>m;

        segmentTree st(n);
        for (int i = 0; i < n; i++)
        {
            int num;
            cin>>num;
            st[i].init(num);
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
