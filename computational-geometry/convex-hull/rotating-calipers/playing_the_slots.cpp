// convex polygon width (rotating calipers)
// https://open.kattis.com/problems/playingtheslots
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

const long double EPS = 1e-9;
const long double INF = 1e20;

typedef long double ptT;
struct pt
{
    ptT x, y;

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    ptT norm2() const {return x * x + y * y;}
};

ptT distLine(const pt &a, const pt &b, const pt &p) {return abs((p - a) ^ (b - a)) / sqrt((b - a).norm2());}

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int next(int i, int n, int st = 1){return (i + st) % n;};

const pt origin = {0, 0};
ptT width(const polygon &poly)
{
    int n = poly.size();
    long double res = INF;
    for (int i = 0, j = 1; i < n; ++i)
    {
        for(; ; j = next(j, n))
        {
            if (orientation(origin, poly[next(i, n)] - poly[i], poly[next(j, n)] - poly[j]) != 1)
                break;
        }
        res = min(res, distLine(poly[i], poly[next(i, n)], poly[j]));
    }
    return res;
}

int main()
{
    int n;
    cin >> n;

    polygon poly(n);
    for (auto &p: poly)
        cin >> p.x >> p.y;
    cout << fixed << setprecision(11) << width(poly) << endl;
}
