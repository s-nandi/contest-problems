//segment tree (lazy propagation), sum of squares queries, range increment update, range assignment update
//http://www.spoj.com/problems/SEGSQRSS/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct node
{
    ll sum, sumSquares, lazy[2]; bool isLazy[2];
    node *l, *r;
    int lb, rb;

    node(){sum = 0, sumSquares = 0, lazy[0] = lazy[1] = 0, isLazy[0] = isLazy[1] = false, l = NULL, r = NULL;}
    void setBounds(int a, int b){lb = a, rb = b;}
    void init(int i) {sum = i, sumSquares = i * i;}

    node* refresh()
    {
        sum = l -> sum + r -> sum, sumSquares = l -> sumSquares + r -> sumSquares;
        return this;
    }

    void pushLazy()
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
    vector <int> v;

    segmentTree(vector <int> &ve)
    {
        root = new node(), v = ve, sz = v.size();
        build(root, 0, sz - 1);
    }

    node combine(node a, node b)
    {
        node acc;
        acc.l = &a, acc.r = &b;
        return *(acc.refresh());
    }

    void build(node* &curr, int l, int r)
    {
        curr -> setBounds(l, r);
        if (l == r) {curr -> init(v[l]); return;}
        int m = (l + r) >> 1;
        build(curr -> l = new node(), l, m), build(curr -> r = new node(), m + 1, r);
        curr -> refresh();
    }

    ll query(int l, int r) {return query(root, l, r).sumSquares;}
    node query(node* curr, int l, int r)
    {
        curr -> pushLazy();
        if (curr -> lb > r or curr -> rb < l) return node();
        if (curr -> lb >= l and curr -> rb <= r) return *curr;
        return combine(query(curr -> l, l, r), query(curr -> r, l, r));
    }

    void modify(int l, int r, int v, int t) {modify(root, l, r, v, t);}
    void modify(node* &curr, int l, int r, int v, int t)
    {
        curr -> pushLazy();
        if (curr -> lb > r or curr -> rb < l) return;
        if (curr -> lb >= l and curr -> rb <= r)
        {
            curr -> setLazy(v, t);
            curr -> pushLazy();
            return;
        }
        modify(curr -> l, l, r, v, t), modify(curr -> r, l, r, v, t);
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
