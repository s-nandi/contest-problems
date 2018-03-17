//andrew monotone chain, vector geometry, convex polygon containment
//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=3958
//2011 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

typedef double ptsT;
typedef long double ptlT;

const double EPS = 1e-9;

struct pt
{
    ptsT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator + (const pt &o){return {x + o.x, y + o.y};}
    pt operator - (const pt &o){return {x - o.x, y - o.y};}
    pt operator * (ptsT scale){return {x * scale, y * scale};}
    pt operator / (ptsT scale){return {x / scale, y / scale};}

    ptlT operator ^ (const pt &o){return (ptlT) x * o.y - (ptlT) y * o.x;}
    ptlT operator * (const pt &o){return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2(){return *this * *this;}
    ptlT dist2(const pt &o){return (*this - o).norm2();}
    pt normalize(){return *this / sqrt(norm2());}

    pt perpccw(){return {-y, x};}
    pt perpcw(){return perpccw() * -1;}
};

int sgn(ptlT i) {return (i > -EPS) - (i < EPS);}
int orientation(pt &o, pt &a, pt &b) {return sgn((b - o) ^ (a - o));} //cw: 1, ccw: -1, col: 0

typedef vector<pt> polygon;
int prev(int i, int n){return i == 0 ? n - 1 : i - 1;}
int next(int i, int n){return i == n - 1 ? 0 : i + 1;};

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

polygon fixConvexPolygon(polygon &poly)
{
    int shift = min_element(poly.begin(), poly.end()) - poly.begin();
    polygon res(poly.size());
    for (int i = 0; i < poly.size(); i++)
    {
        res[i] = poly[(i + shift) % poly.size()];
    }
    return res;
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

bool pointInConvexPolygon(polygon &poly, pt &point)
{
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() + 1, poly.end(), point, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return false;
    polygon triangle = {poly[pos - 1], poly[pos], poly[0]};
    return pointInTriangle(triangle, point) != 1;
}

polygon makeRectangle(pt a, pt b)
{
    pt v = (b - a).perpcw().normalize();
    polygon rectangle = {a - v, b - v, b + v, a + v};
    return fixConvexPolygon(rectangle);
}

bool pointNearPerimeter(polygon &poly, pt p)
{
    int sz = poly.size();
    for (int i = 0; i < sz; i++)
    {
        polygon rectangle = makeRectangle(poly[i], poly[next(i, sz)]);
        if (pointInConvexPolygon(rectangle, p)) return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while(cin>>n)
    {
        if (n == 0) break;

        vector <pt> water, land;
        for (int i = 0; i < n; i++)
        {
            double x, y; char type;
            cin>>x>>y>>type;

            if (type == 'T') land.push_back({x, y});
            else water.push_back({x, y});
        }
        bool isIsland = false;
        if (water.size() == 2)
        {
            polygon rect = makeRectangle(water[0], water[1]);
            for (pt p: land)
            {
                if (!pointInConvexPolygon(rect, p)) {isIsland = true; break;}
            }
        }
        else
        {
            polygon waterArea = andrewMonotoneChain(water);
            for (pt p: land)
            {
                if (pointInConvexPolygon(waterArea, p))
                {
                    if (!pointNearPerimeter(waterArea, p)) {isIsland = true; break;}
                }
            }
        }
        if (isIsland) cout<<"There must be an island."<<'\n';
        else cout<<"There might not be an island."<<'\n';
    }
    return 0;
}
