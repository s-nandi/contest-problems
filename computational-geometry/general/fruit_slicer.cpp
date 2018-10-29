// finding max # of unit-redius circles intersected by line, circle-line intersection, circle-circle tangent creation
// https://open.kattis.com/problems/fruitslicer
// 2018 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;

typedef long double ptT;
struct pt
{
    ptT x, y;

    bool operator == (const pt &o) const
    {
        return abs(x - o.x) < EPS and abs(y - o.y) < EPS;
    }

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    ptT norm2() const {return x * x + y * y;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
    pt normalize() const {return *this / sqrt(norm2());}

    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};}
    pt perpCw() const {return {y, -x};}
};

struct line
{
    pt a, b, ab;

    line(){}
    line (pt p, pt q) : a(p), b(q), ab(q - p) {}

    ptT distLine(const pt &p) const {return abs((p - a) ^ ab) / sqrt(ab.norm2());}
};

struct circle
{
    pt center; ptT r;
};

vector <line> tangents(circle a, circle b, bool exterior)
{
    vector <line> res;
    if (!exterior) b.r *= -1;

    pt ab = b.center - a.center;
    auto dr = a.r - b.r, d2 = ab.norm2(), h2 = d2 - dr * dr;
    if (abs(d2) < EPS or h2 < 0)
    {
        auto tang = a.center + pt({0, 1}) * a.r;
        return {{tang, tang + pt({1, 0})}};
    }
    for (auto sign : {-1, 1})
    {
        ld alpha = acos(dr / sqrt(d2));
        pt v = ab.rotateCw(sign * alpha) / sqrt(d2);
        res.push_back({a.center + v * a.r, b.center + v * b.r});
        if (abs(h2) < EPS)
        {
            auto tang = res.back().a;
            return {{tang - v.perpCw(), tang + v.perpCw()}};
        }
    }
    return res;
}

bool circleLineIntersection(const circle &c, const line &l)
{
    return l.distLine(c.center) <= c.r + EPS;
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
        cin >> points[i].x >> points[i].y;
    }

    int best = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            auto lines = tangents({points[i], 1}, {points[j], 1}, true);
            for (auto l: lines)
            {
                int possible = 0;
                for (int k = 0; k < n; k++)
                {
                    if (circleLineIntersection({points[k], 1}, l))
                        possible++;
                }
                best = max(best, possible);
            }
        }
    }
    cout << best << '\n';
}
