// circle tangents, circle-circle inclusion, line-circle intersection, removing overlapping circles convex hull, sector area
// https://open.kattis.com/problems/craters
// 2017 East Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;
const ld PI = acos(-1);

typedef long double ptT;
struct pt
{
    ptT x, y;
    int index;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    ptT norm2() const {return x * x + y * y;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
    pt normalize() const {return *this / sqrt(norm2());}

    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};}
    pt perpCw() const {return {y, -x};}
};

ld angleCcw(const pt &a, const pt &b){return atan2(a ^ b, a * b);}
ld angleCcw(const pt &o, const pt &a, const pt &b){return angleCcw(a - o, b - o);}

int orientation(const pt &o, const pt &a, const pt &b)
{
    ld cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
}

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

int circleInCircle(const circle &a, const circle &b)
{
    auto dr = a.r - b.r;
    if (a.center.dist2(b.center) <= dr * dr + EPS)
        return dr < -EPS ? 1 : (dr > EPS ? -1 : 0);
    else
        return 1;
} // -1: a strictly contains b, 0: a equal to b, 1: a does not contain b

int lineIntersectsCircle(const line &l, const circle &c)
{
    auto diff = l.distLine(c.center) - c.r;
    return diff <= -EPS ? -1 : (diff >= EPS ? 1 : 0);
} // -1 : intersects at 2 points, 0 : intersects at 1 point, 1 : no intersection

vector <line> findTangents(circle a, circle b, bool exterior)
{
    vector <line> res;
    if (!exterior) b.r *= -1;

    pt ab = b.center - a.center;
    auto dr = a.r - b.r, d2 = ab.norm2(), h2 = d2 - dr * dr;
    if (abs(d2) < EPS or h2 < 0)
        return res;
    for (auto sign : {-1, 1})
    {
        ld alpha = atan2(sqrt(h2), dr);
        pt v = ab.rotateCw(sign * alpha) / sqrt(d2);
        res.push_back({a.center + v * a.r, b.center + v * b.r});
    }
    return res;
}

vector <circle> trimOverlap(const vector <circle> &circles)
{
    int n = circles.size();
    vector <circle> res;
    vector <int> redundant(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) if (i != j)
        {
            auto inclusion = circleInCircle(circles[i], circles[j]);
            if (inclusion == -1)
                redundant[j] = true;
            else if (inclusion == 0)
                redundant[max(i, j)] = true;
        }
    }
    for (int i = 0; i < n; i++) if (!redundant[i])
        res.push_back(circles[i]);
    return res;
}

vector <pt> andrewMonotoneChain(vector <pt> &points)
{
    sort(points.begin(), points.end());
    vector <pt> hull;
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <circle> circles(n);
    for (int i = 0; i < n; i++)
    {
        ptT x, y, r;
        cin >> x >> y >> r;
        r += 10;
        circles[i] = {{x, y, i}, r};
    }
    circles = trimOverlap(circles);
    n = circles.size();

    ld sol;
    if (n == 1)
        sol = 2 * PI * circles[0].r;
    else
    {
        vector <pt> boundary;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (auto &tangent: findTangents(circles[i], circles[j], true))
                {
                    tangent.a.index = i, tangent.b.index = j;
                    bool onBoundary = true;
                    bool intersects = false, hasCw = false, hasCcw = false;
                    for (const auto &c: circles)
                    {
                        auto orient = orientation(tangent.a, tangent.b, c.center);
                        hasCw |= orient == 1;
                        hasCcw |= orient == -1;
                        intersects |= lineIntersectsCircle(tangent, c) == -1;
                        if (intersects or (hasCw and hasCcw))
                        {
                            onBoundary = false;
                            break;
                        }
                    }
                    if (onBoundary)
                        boundary.push_back(tangent.a), boundary.push_back(tangent.b);
                }
            }
        }
        sol = 0.0;
        auto sorted = andrewMonotoneChain(boundary);
        for (int i = 0; i < sorted.size(); i++)
        {
            int inext = i + 1 < sorted.size() ? i + 1 : 0;
            if (sorted[i].index == sorted[inext].index)
            {
                int ind = sorted[i].index;
                auto theta = angleCcw(circles[ind].center, sorted[i], sorted[inext]);
                theta = abs(theta);
                sol += circles[ind].r * theta;
            }
            else
                sol += sqrt(sorted[i].dist2(sorted[inext]));
        }
    }
    cout << fixed << setprecision(10) << sol << '\n';
}
