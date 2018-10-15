// rotating calipers (width of convex polygon), convex hull
// http://codeforces.com/gym/101635 (problem K)
// 2017 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double EPS = 1e-9;
const long double INF = 1e20;

typedef long double ptT;
struct pt
{
    ptT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    ptT norm2() const {return x * x + y * y;}
};

ptT distLine(const pt &a, const pt &b, const pt &p)
{
    return abs((p - a) ^ (b - a)) / sqrt((b - a).norm2());
}

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int next(int i, int n, int st = 1){return (i + st) % n;};

polygon andrewMonotoneChain(polygon &points)
{
    sort(points.begin(), points.end());
    polygon hull;
    for (int i = 0; i < 2; i++)
    {
        int s = hull.size();
        for (pt &p: points)
        {
            while(hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.rbegin()[0], p) != 1)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    if (hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}

const pt origin = {0, 0};
ptT width(const polygon &poly)
{
    int n = poly.size();
    if (n < 2)
      return 0;
    long double res = INF;
    for (int i = 0, j = 1; i < n; ++i)
    {
        for(; ; j = next(j, n))
        {
            if (orientation(origin, poly[i + 1] - poly[i], poly[next(j, n)] - poly[j]) != 1)
                break;
        }
        res = min(res, distLine(poly[i], poly[i + 1], poly[j]));
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, r;
    cin >> n >> r;

    vector <pt> points(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    auto poly = andrewMonotoneChain(points);
    auto res = width(poly);

    cout << fixed << setprecision(10) << res << '\n';
}
