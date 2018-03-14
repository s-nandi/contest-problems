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
    int lb, rb;

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
        curr -> lb = l, curr -> rb = r;
        if (l == r) {curr -> init(0); return;}
        build(curr -> l = new node(), l, (l + r) >> 1), build(curr -> r = new node(), (l + r) >> 1 + 1, r);
        curr -> refresh();
    }

    int query(int l, int r) {return query(root, l, r).sum;}
    node query(node* &curr, int l, int r)
    {
        if (curr -> lb > r or curr -> rb < l) return node();
        if (curr -> lb >= l and curr -> rb <= r) return *curr;
        return combine(query(curr -> l, l, r), query(curr -> r, l, r));
    }

    void modify(int p, int v) {modify(root, p, v);}
    void modify(node* &curr, int p, int v)
    {
        if (curr -> lb > p or curr -> rb < p) return;
        if (curr -> lb == curr -> rb) {curr -> modify(v); return;}
        modify(curr -> l, p, v), modify(curr -> r, p, v);
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
    ios_base::sync_with_stdio(NULL);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--)
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
