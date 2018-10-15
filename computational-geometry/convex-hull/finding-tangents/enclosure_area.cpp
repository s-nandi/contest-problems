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

pair <int, int> pointInConvexPolygon(polygon &poly, pt &point) //inside: -1, outside: 1, on: 0
{
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() + 1, poly.end(), point, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return {1, pos};
    polygon triangle = {poly[pos - 1], poly[pos], poly[0]};
    return {pointInTriangle(triangle, point), pos};
}

pair <int, int> findTangentsConvexPolygon(polygon &poly, pt p) //returns {-1, -1} if p in/on poly
{
    int sz = poly.size();
    auto res = pointInConvexPolygon(poly, p);
    if (res.first != 1) return {-1, -1};

    int rp = res.second, lp = prev(res.second, sz);

    int l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = poly[prev(lp, sz, m)];
        pt nxt = poly[next(prev(lp, sz, m), sz)];
        if (orientation(p, curr, nxt) != 1 and orientation(poly[0], curr, p) != -1) l = m;
        else r = m - 1;
    }
    int leftTangent = prev(lp, sz, l);

    l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = poly[next(rp, sz, m)];
        pt nxt = poly[prev(next(rp, sz, m), sz)];
        if (orientation(p, curr, nxt) != -1 and orientation(poly[0], curr, p) != 1) l = m;
        else r = m - 1;
    }
    int rightTangent = next(rp, sz, l);

    return {leftTangent, rightTangent};
}

ptlT modifiedConvexPolygonArea(polygon &poly, vector <ptlT> &shoelace, pt &p)
{
    auto tangents = findTangentsConvexPolygon(poly, p);
    int lt = tangents.first, rt = tangents.second;
    if (lt == -1 and rt == -1) return shoelace[poly.size()];

    ptlT newArea = (poly[lt] ^ p) + (p ^ poly[rt]);
    if (lt < rt) return shoelace[lt] + (shoelace[poly.size()] - shoelace[rt]) + newArea;
    else return shoelace[lt] - shoelace[rt] + newArea;
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

        polygon hull = andrewMonotoneChain(town);
        auto shoelace = getShoelace(hull);
        auto maxArea = shoelace[hull.size()];
        for (pt p: options)
        {
            maxArea = max(maxArea, abs(modifiedConvexPolygonArea(hull, shoelace, p)));
        }
        if (maxArea & 1) cout<<maxArea / 2<<".5"<<'\n';
        else cout<<maxArea / 2<<".0"<<'\n';
    }
}
