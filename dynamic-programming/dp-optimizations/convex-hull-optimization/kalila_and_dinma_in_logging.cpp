//dynamic programming, convex hull optimization (static)
//http://codeforces.com/contest/319/problem/C

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

vector <int> a, b;

struct equation
{
    ll m, b;

    ll y(ll x0)
    {
        return m * x0 + b;
    }

    double intersect(equation o)
    {
        return double(o.b - b) / (m - o.m);
    }
};

struct convexHullOptimization
{
    deque <equation> hull;

    void addEquation(equation e)
    {
        while (hull.size() > 1 and hull[hull.size() - 2].intersect(e) < hull[hull.size() - 2].intersect(hull[hull.size() - 1]))
        {
            hull.pop_back();
        }
        hull.push_back(e);
    }

    ll getValue(ll x0)
    {
        if (hull.size() == 0) return 0;
        while (hull.size() > 1 and hull[0].y(x0) > hull[1].y(x0))
        {
            hull.pop_front();
        }
        return hull[0].y(x0);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    a.resize(n), b.resize(n);

    for (int i = 0; i < n; i ++)
    {
        cin>>a[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin>>b[i];
    }

    convexHullOptimization cht;

    for (int i = 0; i < n; i++)
    {
        ll bestCost = cht.getValue(a[i]);
        cht.addEquation({b[i], bestCost});
    }

    cout<<cht.getValue(a[n - 1])<<'\n';

    return 0;
}
