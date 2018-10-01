// segment tree, tour ordering, presorting to remove overlap
// http://codeforces.com/gym/101174 (problem F)
// 2016 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct edge{int to;};
typedef vector<vector<edge>> graph;

const int MAXR = 100005;

struct employee
{
    int technical_rank, index;

    bool operator < (const employee &o) const
    {
        return technical_rank < o.technical_rank;
    }
};

struct node {
    ll sum = 0;

    void modify(ll v) { sum += v; }

    node combine(node &o) {
        node res;
        res.sum = sum + o.sum;
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
        build();
    }

    void build()
    {
        for (int i = sz - 1; i >= 1 ; i--)
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

    ll query(int l, int r)
    {
        node lacc, racc;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r& 1)) racc = elements[r].combine(racc);
        }
        return lacc.combine(racc).sum;
    }
};

int timer = 0;
vector <int> in, out, ordered;
void tour(graph &g, int curr)
{
    in[curr] = timer, ordered[timer] = curr;
    timer++;
    for (edge e: g[curr])
        tour(g, e.to);
    out[curr] = timer, ordered[timer] = curr;
    timer++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int root = -1;
    graph g(n);

    vector <int> cost(n);
    vector <employee> employees(n);
    for (int i = 0; i < n; i++)
    {
        int m, r, t;
        cin >> m >> r >> t;

        if (m == -1)
            root = i;
        else
            g[--m].push_back({i});
        employees[i] = {r, i};
        cost[i] = t;
    }
    sort(employees.begin(), employees.end());

    in.resize(n), out.resize(n), ordered.resize(2 * n);
    tour(g, root);

    segmentTree st(2 * n);
    vector <ll> sol(n);
    for (int rnk = 1, it = 0; rnk <= MAXR; rnk++)
    {
        vector <int> changed;
        while (it < employees.size() and employees[it].technical_rank == rnk)
        {
            int ind = employees[it].index;
            sol[ind] = st.query(in[ind], out[ind]) / 2;
            changed.push_back(ind);
            it++;
        }
        for (int ind: changed)
        {
            st.modify(in[ind], cost[ind]);
            st.modify(out[ind], cost[ind]);
        }
    }

    for (auto i: sol)
        cout << i << '\n';
}
