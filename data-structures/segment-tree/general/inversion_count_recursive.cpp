//segment tree, finding # of elements below threshold queries, point increment updates
//http://www.spoj.com/problems/INVCNT/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    int sum;
    node *l, *r;

    node(){sum = 0, l = NULL, r = NULL;}
    void init(int i) {sum = i;}
    void modify(int v) {sum += v;}

    node* refresh()
    {
        sum = l -> sum + r -> sum;
        return this;
    }
};

struct segmentTree
{
    int sz;
    node *root;

    segmentTree(){}
    segmentTree(int s)
    {
        root = new node();
        sz = s;
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
        if (l == r) {curr -> init(0); return;}
        int m = (l + r) >> 1;
        curr -> l = new node(), curr -> r = new node();
        build(curr -> l, l, m);
        build(curr -> r, m + 1, r);
        curr -> refresh();
    }

    int query(int l, int r) {return query(root, 0, sz - 1, l, r).sum;}
    node query(node* &curr, int l, int r, int ql, int qr)
    {
        if (l > qr or r < ql) return node();
        if (l >= ql and r <= qr) return *curr;
        int m = (l + r) >> 1;
        return combine(query(curr -> l, l, m, ql, qr), query(curr -> r, m + 1, r, ql, qr));
    }

    void modify(int p, int v) {modify(root, 0, sz - 1, p, v);}
    void modify(node* &curr, int l, int r, int qp, int v)
    {
        if (l > qp or r < qp) return;
        if (l == r) {curr -> modify(v); return;}
        int m = (l + r) >> 1;
        modify(curr -> l, l, m, qp, v), modify(curr -> r, m + 1, r, qp, v);
        curr -> refresh();
    }
};

vector <int> sorted;

int mapping(int i)
{
    return lower_bound(sorted.begin(), sorted.end(), i) - sorted.begin();
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector <int> a(n);

        for (int i = 0; i < n; i++)
        {
            cin>>a[i];
        }
        sorted = a;
        sort(sorted.begin(), sorted.end());

        segmentTree st(n);
        long long res = 0;
        for (int i = 0; i < n; i++)
        {
            int pos = mapping(a[i]);
            st.modify(pos, 1);
            res += st.query(pos + 1, n - 1);
        }
        cout<<res<<'\n';
    }

    return 0;
}
