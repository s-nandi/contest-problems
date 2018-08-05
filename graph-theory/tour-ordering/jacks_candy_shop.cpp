// segment tree, euler tour ordering (entry and exit), finding max in subtree query and updating node updates
// https://www.facebook.com/hackercup/problem/638251746380051/
// Facebook Hacker Cup 2018 Round 2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct edge{int to;};
typedef vector<vector<edge>> graph;

const int INF = 1231231234;
const int MAXN = 200005;

struct node
{
    int mx = -INF;

    void init(int i){mx = i;}
    void modify(int v){mx = v;}

    node combine(node &o)
    {
        node res;
        res.mx = max(mx, o.mx);
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;

    segmentTree(vector <int> &v)
    {
        sz = v.size();
        elements.resize(2 * sz);
        build(v);
    }

    void build(vector <int> &v)
    {
        for (int i = 0; i < sz; i++) elements[i + sz].init(v[i]);
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    void modify(int p, int v)
    {
        elements[p += sz].modify(v);
        for (p >>= 1; p >= 1; p >>= 1)
        {
            elements[p] = elements[p << 1].combine(elements[p << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        node lacc, racc;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r & 1)) racc = elements[r].combine(racc);
        }
        return lacc.combine(racc).mx;
    }
};

int depth[MAXN];
void dfs(graph &g, int curr, int d = 0)
{
    depth[curr] = d;
    for (edge e: g[curr])
    {
        dfs(g, e.to, d + 1);
    }
}

int timer;
int in[MAXN], out[MAXN];
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        int n, m, a, b;
        cin>>n>>m>>a>>b;

        graph g(n);
        for (int i = 1; i < n; i++)
        {
            int p;
            cin>>p;
            g[p].push_back({i});
        }
        dfs(g, 0);

        vector <int> customers(m);
        for (int i = 0; i < m; i++)
        {
            customers[i] = (a * i + b) % n;
        }

        sort(customers.begin(), customers.end(), [](int a, int b)
        {
            return depth[a] > depth[b];
        });

        timer = 0;
        ordered.assign(2 * n, 0);
        tour(g, 0);

        segmentTree st(ordered);
        ll sol = 0;
        for (int root: customers)
        {
            int best = st.query(in[root], out[root]);
            if (best >= 0)
            {
                sol += best;
                st.modify(in[best], -INF);
                st.modify(out[best], -INF);
            }
        }
        cout<<"Case #"<<test<<": "<<sol<<'\n';
    }

    return 0;
}
