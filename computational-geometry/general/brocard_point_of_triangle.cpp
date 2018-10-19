// vector operations (line-line intersection, vector rotation, angle between vectors), binary search on answer
// https://open.kattis.com/problems/brocard
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;
const ld PI = 3.1415296;

typedef long double ptT;
struct pt
{
    ptT x, y;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    pt rotateCcw(ld theta) {return {cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y};}
};

ptT angleCcw(const pt &a, const pt &b){return atan2(a ^ b, a * b);}

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

struct line
{
    pt a, b, ab;

    line(){}
    line(pt p, pt q) : a(p), b(q), ab(q - p) {}
};

// Assumes intersection exists (non-parallel lines and no endpoints)
pt findIntersection(const line &m, const line &n)
{
    ptT denom = m.ab ^ n.ab;
    ptT mt = (n.a - m.a) ^ n.ab;
    ptT nt = (n.a - m.a) ^ m.ab;
    if (denom < 0) denom = -denom, mt = -mt, nt = -nt;
    pt res = m.a + m.ab * mt / denom;
    return res;
}

pt findBrocard(polygon &t)
{
    int n = 3;
    auto minAngle = 2 * PI;
    for (int i = 0; i < 3; i++)
    {
        auto angle = angleCcw(t[next(i, n)] - t[i], t[prev(i, n)] - t[i]);
        minAngle = min(minAngle, angle);
    }

    ld l = EPS, r = minAngle;
    while (true)
    {
        auto m = (l + r) / 2;

        vector <line> lines(3);
        for (int i = 0; i < 3; i++)
        {
            auto v = t[next(i, n)] - t[i];
            lines[i] = line(t[i], t[i] + v.rotateCcw(m));
        }

        auto intersect = findIntersection(lines[0], lines[1]);
        auto orient = orientation(lines[2].a, lines[2].b, intersect);
        if (orient == 1)
            r = m;
        else if(orient == -1)
            l = m;
        else
            return intersect;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << fixed << setprecision(5);

    int T;
    cin >> T;

    while (T--)
    {
        int test;
        cin >> test;

        polygon triangle(3);
        for (int i = 0; i < 3; i++)
            cin >> triangle[i].x >> triangle[i].y;

        auto brocard = findBrocard(triangle);
        cout << test << " " << brocard.x << " " << brocard.y << '\n';
    }
}
