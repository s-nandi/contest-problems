// point inclusion in general polygon
// https://www.spoj.com/problems/INOROUT/

#include <bits/stdc++.h>

using namespace std;

const long double EPS = 1e-9;

typedef long double ptT;
struct pt
{
    ptT x, y;

    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

int pointInPolygon(polygon &poly, pt &p)
{
    int winding = 0, n = poly.size();
    for (int i = 0; i < n; i++)
    {
        int j = next(i, n);
        if (p == poly[i])
            return 0;
        if (abs(poly[i].y - poly[j].y) < EPS and abs(poly[i].y - p.y) < EPS)
        {
            auto mn = min(poly[i].x, poly[j].x), mx = max(poly[i].x, poly[j].x);
            if (mn <= p.x and p.x <= mx)
                return 0;
        }
        else
        {
            bool above = p.y > poly[i].y;
            if (above != (p.y > poly[j].y))
            {
                auto orient = orientation(p, poly[j], poly[i]);
                if (orient == 0)
                    return 0;
                else if(above == (orient == 1))
                    winding += above ? 1 : -1;
            }
        }
    }
    return winding == 0 ? 1 : -1;
} // inside: -1, outside: 1, on: 0

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    polygon poly(n);
    for (int i = 0; i < n; i++)
    {
        cin >> poly[i].x >> poly[i].y;
    }
    reverse(poly.begin(), poly.end());

    for (int i = 0; i < q; i++)
    {
        pt p;
        cin >> p.x >> p.y;
        if (pointInPolygon(poly, p) != 1)
            cout << 'D' << '\n';
        else
            cout << 'F' << '\n';
    }
}
