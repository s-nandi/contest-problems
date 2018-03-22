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

    node(){maxVal = -INF, resetLazy();}
    void combine(node &a, node &b){l = &a, r = &b, refresh();}
    void init(int i){maxVal = i;}

    void refresh()
    {
        maxVal = max(l -> maxVal, r -> maxVal);
    }

    void pushLazy(int lb, int rb)
    {
        if (isLazy)
        {
            maxVal += lazy;
            if (lb != rb) l -> setLazy(lazy), r -> setLazy(lazy);
            resetLazy();
        }
    }

    void setLazy(int v){lazy += v, isLazy = true;}
    void resetLazy(){lazy = 0, isLazy = false;}
};

struct segmentTree
{
    int sz, defaultValue = 0;
    vector <node> elements;
    vector <int> lb, rb;

    segmentTree(){}
    segmentTree(int s)
    {
        sz = s;
        elements.resize(4 * sz), lb.resize(4 * sz), rb.resize(4 * sz);
        build(0, sz - 1);
    }

    void build(int l, int r, int p = 1)
    {
        lb[p] = l, rb[p] = r;
        if (l == r) {elements[p].init(defaultValue); return;}
        int m = (l + r) >> 1;
        build(l, m, p << 1), build(m + 1, r, p << 1 | 1);
        elements[p].combine(elements[p << 1], elements[p << 1 | 1]);
    }

    int query(int l, int r){return query(l, r, 1).maxVal;}
    node query(int l, int r, int p)
    {
        push(p);
        if (lb[p] > r or rb[p] < l) return node();
        if (lb[p] >= l and rb[p] <= r) return elements[p];
        node res, ql = query(l, r, p << 1), qr = query(l, r, p << 1 | 1);
        res.combine(ql, qr);
        return res;
    }

    void modify(int l, int r, int v, int p = 1)
    {
        push(p);
        if (lb[p] > r or rb[p] < l) return;
        if (lb[p] >= l and rb[p] <= r)
        {
            elements[p].setLazy(v), push(p);
            return;
        }
        modify(l, r, v, p << 1), modify(l, r, v, p << 1 | 1);
        elements[p].refresh();
    }

    void push(int p){elements[p].pushLazy(lb[p], rb[p]);}
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
