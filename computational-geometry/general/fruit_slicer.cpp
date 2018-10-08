// finding max # of unit-redius circles intersected by line, circle-line intersection, circle-circle tangent creation
// https://open.kattis.com/problems/fruitslicer
// 2018 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;

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
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}
    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
    pt normalize() const {return *this / sqrt(norm2());}

    pt perpCw() const {return {y, -x};}
    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};}
};

struct line
{
    pt a, b, ab;

    line (pt p, pt q)
    {
        a = p, b = q;
        ab = q - p;
    }

    ptT distLine(const pt &p) {return abs((p - a) ^ ab) / sqrt(ab.norm2());}
};

vector <line> tangentToCircles(pt a, pt b)
{
    if (a == b)
        return {line(a, {a.x + 1, a.y + 1})};

    vector <line> res;
    auto c = (a + b) / 2;
    auto d = sqrt(a.dist2(c));
    if (d >= 1)
    {
        auto theta = asin(1 / d);

        pt v = a - c;
        pt v1 = v.rotateCw(theta);
        pt v2 = v.rotateCw(-theta);

        line l1 = line(c, c + v1);
        line l2 = line(c, c + v2);
        res.push_back(l1), res.push_back(l2);
    }
    pt perp = ((c - a).perpCw()).normalize();
    line l3 = line(a + perp, b + perp);
    line l4 = line(a - perp, b - perp);
    res.push_back(l3), res.push_back(l4);

    return res;
}

bool cutCircle(line &l, pt c)
{
    return l.distLine(c) <= 1 + EPS;
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
            auto lines = tangentToCircles(points[i], points[j]);
            for (auto l: lines)
            {
                int possible = 0;
                for (int k = 0; k < n; k++)
                {
                    if (cutCircle(l, points[k]))
                        possible++;
                }
                best = max(best, possible);
            }
        }
    }
    cout << best << '\n';
}
