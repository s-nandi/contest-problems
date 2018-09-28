// dsu on trees, dp (online convex hull optimization)
// https://codeforces.com/contest/932/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct edge{int to;};
typedef vector<vector<edge>> graph;

bool chtQuery;
struct equation
{
    mutable ll a, b;
    mutable long double intersectNxt = 0;

    ll slope() const {return a;}
    ll constant() const {return b;}
    ll y(ll x0) const {return a * x0 + b;}
    ld intersect(equation o) const {return ld (o.b - b) / (a - o.a);}

    bool operator < (const equation &o) const
    {
        return chtQuery ? intersectNxt < o.intersectNxt : slope() < o.slope();
    }
};

struct convexHullTrick : multiset<equation>
{
    static const ll oo = numeric_limits<ll>::max() - 5;
    bool setNext(iterator x, iterator y)
    {
        if (y == end())
        {
            x -> intersectNxt = oo;
            return false;
        }
        if (x -> slope() == y -> slope())
            x -> intersectNxt = x -> constant() > y -> constant() ? oo : -oo;
        else
            x -> intersectNxt = x -> intersect(*y);
        return x -> intersectNxt >= y -> intersectNxt;
    }

    void addEquation(equation e)
    {
        e.intersectNxt = 0;
        auto it = insert(e), nit = next(it);

        while (setNext(it, nit))
            nit = erase(nit);

        if (it == begin())
            return;

        auto pit = it;
        if (setNext(--pit, it))
            setNext(pit, it = erase(it));

        while (pit != begin())
        {
            it = pit;
            pit = prev(pit);
            if (it != begin() and pit -> intersectNxt >= it -> intersectNxt)
                setNext(pit, erase(it));
            else break;
        }
    }

    ll getMax(ll x0)
    {
        if (empty())
            return 0;

        chtQuery = true;
        auto l = *lower_bound({0, 0, x0});
        chtQuery = false;

        return l.y(x0);
    }
};

vector <ll> a, b, sol;
convexHullTrick dfs(graph &g, int curr, int prev = -1)
{
    convexHullTrick current;
    for (edge e: g[curr]) if (e.to != prev)
    {
        convexHullTrick res = dfs(g, e.to, curr);
        if (res.size() > current.size())
            swap(res, current);
        for (auto &e: res)
            current.addEquation(e);
    }
    sol[curr] = -current.getMax(a[curr]);
    current.addEquation({-b[curr], -sol[curr]});
    return current;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    a.resize(n), b.resize(n), sol.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back({v});
        g[v].push_back({u});
    }

    dfs(g, 0);
    for (int i = 0; i < n; i++)
        cout << sol[i] << " ";
    cout << '\n';
}
