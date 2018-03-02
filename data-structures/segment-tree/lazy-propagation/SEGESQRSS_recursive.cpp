//segment tree (lazy propagation), sum of squares queries, range increment update, range assignment update
//http://www.spoj.com/problems/SEGSQRSS/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct node
{
    ll sum, sumSquares, lazy[2];
    bool isLazy[2];
    node *l, *r;

    node(){sum = 0, sumSquares = 0, lazy[0] = lazy[1] = 0, isLazy[0] = isLazy[1] = false, l = NULL, r = NULL;}
    void init(int i) {sum = i, sumSquares = i * i;}

    node* refresh()
    {
        sum = l -> sum + r -> sum, sumSquares = l -> sumSquares + r -> sumSquares;
        return this;
    }

    void pushLazy(int lb, int rb)
    {
        for (int t = 0; t < 2; t++)
        {
            if (isLazy[t])
            {
                int v = lazy[t], len = (rb - lb + 1);
                if (t == 0)
                {
                    sumSquares = len * v * v;
                    sum = len * v;
                }
                else
                {
                    sumSquares += len * v + 2 * sum * v;
                    sum += len * v;
                }

                if (lb != rb)
                {
                    l -> setLazy(v, t), r -> setLazy(v, t);
                }
                resetLazy(t);
            }
        }
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
    int sz;
    node* root;

    segmentTree(vector <int> &v)
    {
        root = new node();
        sz = v.size();
        build(v, root, 0, sz - 1);
    }

    node combine(node a, node b)
    {
        node acc;
        acc.l = &a, acc.r = &b;
        return *(acc.refresh());
    }

    void build(vector <int> &v, node* &curr, int l, int r)
    {
        if (l == r) {curr -> init(v[l]); return;}
        int m = (l + r) >> 1;
        curr -> l = new node(), curr -> r = new node();
        build(v, curr -> l, l, m);
        build(v, curr -> r, m + 1, r);
        curr -> refresh();
    }

    ll query(int l, int r) {return query(root, 0, sz - 1, l, r).sumSquares;}
    node query(node* curr, int l, int r, int ql, int qr)
    {
        curr -> pushLazy(l, r);
        if (l > qr or r < ql) return node();
        if (l >= ql and r <= qr) return *curr;
        int m = (l + r) >> 1;
        return combine(query(curr -> l, l, m, ql, qr), query(curr -> r, m + 1, r, ql, qr));
    }

    void modify(int ql, int qr, int v, int t) {modify(root, 0, sz - 1, v, t, ql, qr);}
    void modify(node* &curr, int l, int r, int v, int t, int ql, int qr)
    {
        curr -> pushLazy(l, r);
        if (l > qr or r < ql) return;
        if (l >= ql and r <= qr)
        {
            curr -> setLazy(v, t);
            curr -> pushLazy(l, r);
            return;
        }
        int m = (l + r) >> 1;
        modify(curr -> l, l, m, v, t, ql, qr), modify(curr -> r, m + 1, r, v, t, ql, qr);
        curr -> refresh();
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

        vector <int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin>>a[i];
        }
        segmentTree st(a);

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
