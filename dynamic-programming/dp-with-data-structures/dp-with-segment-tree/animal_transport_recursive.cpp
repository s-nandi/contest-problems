//dynamic programming with segment tree, lazy propagation, range maximum query, range increment update, binary search
//https://www.hackerrank.com/contests/world-codesprint-12/challenges/animal-transport/problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1231231234

struct segment
{
    int type, start, destination;
    bool operator < (segment o) const
    {
        return destination < o.destination;
    }
};

struct node
{
    int maxVal, lazy;
    bool isLazy;
    node *l, *r;

    node(){maxVal = -INF, lazy = isLazy = 0, l = NULL, r = NULL;}
    void init(int i){maxVal = i;}

    node* refresh()
    {
        maxVal = max(l -> maxVal, r -> maxVal);
        return this;
    }

    void setLazy(int v)
    {
        lazy += v, isLazy = true;
    }

    void resetLazy()
    {
        lazy = 0, isLazy = false;
    }
};

struct segmentTree
{
    int sz;
    node* root;

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
        if (l == r) { curr -> init(0); return; }
        int m = (l + r) >> 1;
        curr -> l = new node(), curr -> r = new node();
        build(curr -> l, l, m);
        build(curr -> r, m + 1, r);
        curr -> refresh();
    }

    void apply(node* &curr, int l, int r)
    {
        if (!curr -> isLazy) return;
        int v = curr -> lazy;
        curr -> maxVal += v;
        if (l != r)
        {
            (curr -> l) -> setLazy(v), (curr -> r) -> setLazy(v);
        }
        curr -> resetLazy();
    }

    int query(int l, int r) {return query(root, 0, sz - 1, l, r).maxVal;}
    node query(node* &curr, int l, int r, int ql, int qr)
    {
        apply(curr, l, r);
        if (l > qr or r < ql) return node();
        if (l >= ql and r <= qr) return *curr;
        int m = (l + r) >> 1;
        return combine(query(curr -> l, l, m, ql, qr), query(curr -> r, m + 1, r, ql, qr));
    }

    void modify(int l, int r, int v) {modify(root, 0, sz - 1, v, l, r);}
    void modify(node* &curr, int l, int r, int v, int ql, int qr)
    {
        apply(curr, l, r);
        if (l > qr or r < ql) return;
        if (l >= ql and r <= qr)
        {
            curr -> setLazy(v);
            apply(curr, l, r);
            return;
        }
        int m = (l + r) >> 1;
        modify(curr -> l, l, m, v, ql, qr), modify(curr -> r, m + 1, r, v, ql, qr);
        curr -> refresh();
    }
};

int main()
{
    int T;
    cin>>T;

    while (T--)
    {
        int n, m;
        cin>>m>>n;

        vector <segment> segments(n);
        for (int i = 0; i < n; i++)
        {
            char c;
            cin>>c;
            segments[i].type = (c == 'D' or c == 'M') ? 0 : 1;
        }
        for (int i = 0; i < n; i++)
        {
            cin>>segments[i].start;
        }
        for (int i = 0; i < n; i++)
        {
            cin>>segments[i].destination;
            --segments[i].start; --segments[i].destination;
        }
        sort(segments.begin(), segments.end());

        vector <int> dp(m);
        segmentTree st[2];
        for (int i = 0; i < 2; i++) st[i] = segmentTree(m);

        int curr = 0;
        for (int i = 0; i < m; i++)
        {
            while (segments[curr].destination == i and curr < segments.size())
            {
                segment s = segments[curr++];
                if (s.destination < s.start) continue;
                st[s.type].modify(0, s.start, 1);
            }
            dp[i] = max(st[0].query(0, i), st[1].query(0, i));
            st[0].modify(i, i, dp[i]);
            st[1].modify(i, i, dp[i]);
        }

        for (int i = 1; i <= n; i++)
        {
            int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin() + 1;
            if (pos <= m)
            {
                cout<<pos<<" ";
            }
            else
            {
                cout<<-1<<" ";
            }
        }
        cout<<'\n';
    }

    return 0;
}
