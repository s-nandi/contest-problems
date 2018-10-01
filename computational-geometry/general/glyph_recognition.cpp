// point inclusion (convex polygon), vector rotation, binary search on answer
// http://codeforces.com/gym/101623 (problem G)
// 2017 Northwest European Regional

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-7;
const double PI = 3.1415926;

typedef long double ptT;
struct pt
{
    ptT x, y;

    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and (abs(y - o.y) < EPS);}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x , y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}

    ptT operator ^ (const pt &o) const {return {x * o.y - y * o.x};}

    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, -sin(theta) * x + cos(theta) * y};}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;

int next(int i, int n, int st = 1)
{
    return (i + st) % n;
}

int pointInTriangle(polygon &triangle, pt &p)
{
    int orient[3];
    for (int i = 0; i < 3 ; i ++)
        orient[i] = orientation(triangle[i], triangle[next(i, 3)], p);
    if (orient[0] == orient[1] and orient[1] == orient[2]) return -1;
    for (int i = 0; i < 3; i ++)
        if (orient[i] * orient[next(i, 3)] == -1) return 1;
    return 0;
}

// assumes polygon vertices are in clockwise order
pair <int, int> pointInConvexPolygon(polygon &poly, pt &p)
{
    if (poly[0] == p) return {0, 2};
    if (poly.back() == p) return {0, poly.size() - 1};
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() +1,poly.end(), p, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return {1, pos};
    polygon triangle = {poly[pos-1], poly[pos], poly[0]};
    return {pointInTriangle(triangle, p), pos};
} // return -1: inside, 0: on, 1: outside

ptT polygonArea(polygon &poly) // returns doubled oriented area: cw: negative, ccw: positive
{
    int sz = poly.size();
    ptT sol = 0;
    for (int i = 0; i < sz; i++)
        sol += poly[i] ^ poly[next(i, sz)];
    return sol;
}

ptT findArea(const polygon &poly, const vector <pt> &points, bool isInner)
{
    int n = poly.size();

    double l = 0.5, r = 2e6 * sqrt(2) + 5;
    while (r - l > EPS)
    {
        double m = (l + r) / 2.0;

        polygon scaled(n);
        for (int i = 0; i < n; i++)
            scaled[i] = poly[i] * m;

        int numContained = 0;
        for (pt p: points)
        {
            if (pointInConvexPolygon(scaled, p).first != 1)
                numContained++;
        }

        if (isInner)
        {
            if (numContained == 0)
                l = m;
            else
                r = m;
        }
        else
        {
            if (numContained == points.size())
                r = m;
            else
                l = m;
        }
    }
    polygon finalized(n);
    for (int i = 0; i < n; i++)
        finalized[i] = poly[i] * l;
    return polygonArea(finalized);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <pt> points(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    long double best = 0.0;
    int bestFrom = -1;
    for (int sides = 3; sides <= 8; sides++)
    {
        polygon poly(sides);

        pt curr = {1, 0};
        double rot = 2 * PI / sides;

        for (int i = 0; i < sides; i++)
        {
            poly[i] = curr;
            curr = curr.rotateCw(rot);
        }

        auto inner = findArea(poly, points, true);
        auto outer = findArea(poly, points, false);
        auto score = inner / outer;

        if (score > best)
        {
            best = score;
            bestFrom = sides;
        }
    }
    cout << fixed << setprecision(10) << bestFrom << " " << best << '\n';
}
