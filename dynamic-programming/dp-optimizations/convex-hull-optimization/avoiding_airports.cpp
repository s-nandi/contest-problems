// dynamic programming, convex hull trick (online, parabolic function of distance from start)
// https://open.kattis.com/problems/avoidingairports
// 2017 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1231231231231234;

struct equation
{
    ll m, b; // y = (x - m) ^ 2 + b

    ll y(ll x0)
    {
        ll dx = x0 - m;
        return dx * dx + b;
    }

    double intersect(const equation &o) const
    {
        double q = double (o.b - b) / (o.m - m);
        return (q + o.m + m) / 2.0;
    }
};

struct cht
{
    vector <equation> hull;

    ll getMinAfter(ll x0)
    {
        equation e = {x0, 0};
        int max_valid = upper_bound(hull.begin(), hull.end(), e, [](equation a, equation b){return a.m < b.m;}) - hull.begin() - 1;

        if (max_valid == -1)
            return INF;

        int l = 0, r = max_valid;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (hull[m].intersect(hull[m + 1]) >= x0)
                r = m;
            else
                l = m + 1;
        }
        return hull[l].y(x0);
    }

    void addEquation(const equation &e)
    {
        while (hull.size() >= 2 and hull[hull.size() - 2].intersect(e) < hull[hull.size() - 2].intersect(hull[hull.size() - 1]))
            hull.pop_back();
        hull.push_back(e);
    }
};

struct edge
{
    int from, to, startTime, endTime;
    bool operator < (const edge &o) const
    {
        return endTime < o.endTime;
    }
};

int main()
{
    int n, m;
    cin>>n>>m;
    vector <edge> edges;
    for (int i = 0; i < m; i++)
    {
        int a, b, s, e;
        cin>>a>>b>>s>>e;
        --a; --b;
        edges.push_back({a, b, s, e});
    }
    sort(edges.begin(), edges.end());

    vector <cht> hulls(n);
    hulls[0].hull.push_back({0, 0});

    ll sol = INF;
    for (edge e: edges)
    {
        ll minCost = hulls[e.from].getMinAfter(e.startTime);
        hulls[e.to].addEquation({e.endTime, minCost});

        if (e.to == n - 1)
            sol = min(sol, minCost);
    }
    cout<<sol<<'\n';

    return 0;
}
