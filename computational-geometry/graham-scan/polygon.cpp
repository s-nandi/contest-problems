//graham scan
//http://codeforces.com/problemset/problem/166/B

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

struct pt
{
    int x, y;

    bool operator < (const pt &o) const
    {
        return make_pair(y, x) < make_pair(o.y, o.x);
    }

    bool operator == (const pt &o) const
    {
        return x == o.x and y == o.y;
    }

    ll distSq(pt &o)
    {
        return (ll) (x - o.x) * (x - o.x) + (ll) (y - o.y) * (y - o.y);
    }
};

int sgn(ll i)
{
    return (i > 0) - (i < 0);
}

int orientation(pt &a, pt &b, pt &c)
{
    return sgn((ll) (b.y - a.y) * (c.x - b.x) - (ll) (b.x - a.x) * (c.y - b.y));
}

pt pivot;
bool angleOrder(pt &a, pt &b)
{
    int orient = orientation(pivot, a, b);
    if (orient == 0) return pivot.distSq(a) < pivot.distSq(b);
    else return orient == 1;
}

vector <pt> grahamScan(vector <pt> &points)
{
    swap(*points.begin(), *min_element(points.begin(), points.end()));
    pivot = points[0];
    sort(points.begin() + 1, points.end(), angleOrder);

    int curr = points.size() - 1;
    while (orientation(points[0], points[curr], points[curr - 1]) == 0) curr--;
    reverse(points.begin() + curr, points.end());

    vector <pt> hull = {points[0], points[1], points[2]};
    for (int i = 3; i < points.size(); i++)
    {
        while (orientation(hull.rbegin()[1], hull.rbegin()[0], points[i]) == -1) hull.pop_back();
        hull.push_back(points[i]);
    }
    return hull;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n;
    vector <pt> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].x>>a[i].y;
    }
    a = grahamScan(a);

    cin>>m;
    vector <pt> b(m);
    for (int i = 0; i < m; i++)
    {
        cin>>b[i].x>>b[i].y;
    }

    b.insert(b.end(), a.begin(), a.end());
    vector <pt> hull = grahamScan(b);

    if (a == hull) cout<<"YES"<<'\n';
    else cout<<"NO"<<'\n';

    return 0;
}
