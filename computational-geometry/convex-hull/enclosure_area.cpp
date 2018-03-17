//andrew monotone chain, tangents of convex polygon to point, shoelace theorem (prefix sum)
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=757&problem=5971
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

typedef int ptsT;
typedef ll ptlT;

const double EPS = 1e-9;

struct pt
{
    ptsT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator + (const pt &o){return {x + o.x, y + o.y};}
    pt operator - (const pt &o){return {x - o.x, y - o.y};}

    ptlT operator ^ (const pt &o){return (ptlT) x * o.y - (ptlT) y * o.x;}
    ptlT operator * (const pt &o){return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2(){return *this * *this;}
    ptlT dist2(const pt &o){return (*this - o).norm2();}
};

int sgn(ptlT i) {return (i > -EPS) - (i < EPS);}
int orientation(pt &o, pt &a, pt &b) {return sgn((b - o) ^ (a - o));} //cw: 1, ccw: -1, col: 0

typedef vector<pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

vector <ptlT> getShoelace(polygon &poly)
{
    int sz = poly.size();
    vector <ptlT> shoelace(sz + 1);
    for (int i = 0; i < sz; i++)
    {
        shoelace[i + 1] = shoelace[i] + (poly[i] ^ poly[next(i, sz)]);
    }
    return shoelace;
}

int pointInTriangle(polygon &triangle, pt &p) //inside: -1, outside: 1, on: 0
{
    int orient[3];
    for (int i = 0; i < 3; i++)
        orient[i] = orientation(triangle[i], triangle[next(i, 3)], p);
    if (orient[0] == orient[1] and orient[1] == orient[2]) return -1;
    for (int i = 0; i < 3; i++) if (orient[i] * orient[next(i, 3)] == -1) return 1;
    return 0;
}

polygon andrewMonotoneChain(vector <pt> &points)
{
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
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

pair <bool, int> pointInConvexPolygon(polygon &poly, pt &point)
{
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() + 1, poly.end(), point, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return {false, pos};
    polygon triangle = {poly[pos - 1], poly[pos], poly[0]};
    return {pointInTriangle(triangle, point) != 1, pos};
}

pair <int, int> findTangent(polygon &hull, pt p)
{
    int sz = hull.size();
    auto res = pointInConvexPolygon(hull, p);
    if (res.first) return {-1, -1};

    int rightInit = res.second, leftInit = prev(res.second, sz);

    int l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = hull[prev(leftInit, sz, m)];
        pt nxt = hull[next(prev(leftInit, sz, m), sz)];
        if (orientation(p, curr, nxt) != 1 and orientation(hull[0], curr, p) != -1) l = m;
        else r = m - 1;
    }
    int leftTangent = prev(leftInit, sz, l);

    l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = hull[next(rightInit, sz, m)];
        pt nxt = hull[prev(next(rightInit, sz, m), sz)];
        if (orientation(p, curr, nxt) != -1 and orientation(hull[0], curr, p) != 1) l = m;
        else r = m - 1;
    }
    int rightTangent = next(rightInit, sz, l);

    return {leftTangent, rightTangent};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    while (cin>>n>>k)
    {
        vector <pt> town(k), options(n - k);
        for (int i = 0; i < k; i++)
        {
            cin>>town[i].x>>town[i].y;
        }
        for (int i = 0; i < n - k; i++)
        {
            cin>>options[i].x>>options[i].y;
        }

        vector <pt> poly = andrewMonotoneChain(town);
        auto shoelace = getShoelace(poly);

        ptlT maxArea = abs(shoelace[poly.size()]);
        for (pt p: options)
        {
            pair <int, int> tangents = findTangent(poly, p);
            int lt = tangents.first, rt = tangents.second;
            if (lt == -1 and rt == -1) continue;

            ptlT area = (poly[lt] ^ p) + (p ^ poly[rt]);
            if (lt < rt)  area += shoelace[lt] + (shoelace[poly.size()] - shoelace[rt]);
            else area += shoelace[lt] - shoelace[rt];

            maxArea = max(abs(area), maxArea);
        }

        if (maxArea & 1) cout<<maxArea / 2<<".5"<<'\n';
        else cout<<maxArea / 2<<".0"<<'\n';
    }
}
