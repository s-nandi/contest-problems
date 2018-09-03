// euler tour reordering, lazy segment tree (max-min of range query, range add updates)
// https://codeforces.com/gym/100827
// 2014 Pacific Northwest Regional

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

struct edge{int to;};
typedef vector<vector<edge>> graph;

const int INF = 1231231234;

struct node
{
    int maxVal = -INF, minVal = INF;

    void init(int i){maxVal = minVal = i;}
    node combine(const node &a, const node &b)
    {
        maxVal = max(a.maxVal, b.maxVal);
        minVal = min(a.minVal, b.minVal);
        return *this;
    }
} acc;

struct segmentTree
{
    node n;
    int lb, rb, lazy; bool isLazy;
    segmentTree *l, *r;

    segmentTree(){}
    segmentTree(int s, vector <int> &v) : segmentTree(0, s - 1, v) {}
    segmentTree(int ql, int qr, vector <int> &v) : lb(ql), rb(qr)
    {
        resetLazy();
        if (lb == rb){n.init(v[lb]); return;}
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, v), r = new segmentTree(m + 1, rb, v);
        n.combine(l -> n, r -> n);
    }

    int query(int lv, int rv)
    {
        auto res = queryn(lv, rv);
        return res.maxVal - res.minVal;
    }

    node queryn(int ql, int qr)
    {
        pushLazy();
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l -> queryn(ql, qr), r -> queryn(ql, qr));
    }

    void modify(int ql, int qr, int v)
    {
        pushLazy();
        if (lb > qr or rb < ql) return;
        if (lb >= ql and rb <= qr)
        {
            setLazy(v), pushLazy();
            return;
        }
        l -> modify(ql, qr, v), r -> modify(ql, qr, v);
        n.combine(l -> n, r -> n);
    }

    void pushLazy()
    {
        if (!isLazy) return;
        n.maxVal += lazy;
        n.minVal += lazy;
        if (lb != rb) l -> setLazy(lazy), r -> setLazy(lazy);
        resetLazy();
    }

    void setLazy(int v){lazy += v, isLazy = true;}
    void resetLazy(){lazy = 0, isLazy = false;}
};

int timer;
vector <int> in, out;
vector <int> ordered;
void tour(graph &g, int curr)
{
    in[curr] = timer;
    ordered[timer] = curr;
    timer++;
    for (edge e: g[curr])
    {
        tour(g, e.to);
    }
    out[curr] = timer;
    ordered[timer] = curr;
    timer++;
}

int main()
{
    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        int n;
        cin>>n;

        graph g(n);
        vector <int> salary(n);
        for (int i = 1; i < n; i++)
        {
            int par;
            cin>>par;
            g[--par].push_back({i});
        }
        for(int i = 0; i < n; i++)
        {
            cin>>salary[i];
        }

        timer = 0;
        in.assign(n, 0), out.assign(n, 0);
        ordered.assign(2 * n, 0);
        tour(g, 0);

        vector <int> v;
        for (int i: ordered)
            v.push_back(salary[i]);
        segmentTree st(2 * n, v);

        int q;
        cin>>q;
        for (int i = 0; i < q; i++)
        {
            char type;
            cin>>type;

            int e;
            cin>>e;
            --e;
            int l = in[e], r = out[e];

            if (type == 'Q')
            {
                int res = st.query(l, r);
                cout<<res<<'\n';
            }
            else
            {
                int val;
                cin>>val;
                st.modify(l, r, val);
            }
        }
    }
    return 0;
}
