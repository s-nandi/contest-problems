//dynamic programming, convex hull optimization (static)
//http://codeforces.com/contest/319/problem/C

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

struct equation
{
    ll m, b;

    ll y(ll x0){return m * x0 + b;}
    double intersect(equation o){return double(o.b - b) / (m - o.m);}
};

struct convexHullTrick
{
    deque <equation> hull;

    void addEquation(const equation &e)
    {
        while (hull.size() > 1 and hull.rbegin()[1].intersect(e) < hull.rbegin()[1].intersect(hull.rbegin()[0]))
            hull.pop_back();
        hull.push_back(e);
    }

    ll getValue(ll x0)
    {
        if (hull.empty()) return 0;
        while (hull.size() > 1 and hull[0].y(x0) > hull[1].y(x0))
            hull.pop_front();
        return hull[0].y(x0);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> a(n), b(n);
    for (int i = 0; i < n; i ++)
    {
        cin>>a[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin>>b[i];
    }

    convexHullTrick cht;

    for (int i = 0; i < n; i++)
    {
        ll bestCost = cht.getValue(a[i]);
        cht.addEquation({b[i], bestCost});
    }

    cout<<cht.getValue(a[n - 1])<<'\n';

    return 0;
}
