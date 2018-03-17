//andrew monotone chain
//http://codeforces.com/problemset/problem/166/B

#include <iostream>
#include <algorithm>
#include <vector>

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

    pt operator - (const pt &o){return {x - o.x, y - o.y};}

    ptlT operator ^ (const pt &o){return (ptlT) x * o.y - (ptlT) y * o.x;}
    ptlT operator * (const pt &o){return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2(){return *this * *this;}
    ptlT dist2(const pt &o){return (*this - o).norm2();}
};

int sgn(ptlT i) {return (i > -EPS) - (i < EPS);}
int orientation(pt &a, pt &b, pt &c)
{
    return sgn((c - b) ^ (b - a)); //cw: 1, ccw: -1, col: 0
}

typedef vector<pt> polygon;

polygon andrewMonotoneChain(polygon &points)
{
    sort(points.begin(), points.end());
    polygon hull; hull.reserve(points.size() + 1);
    for (int i = 0; i < 2; i++)
    {
        int s = hull.size();
        for (pt &p: points)
        {
            while(hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.rbegin()[0], p) == -1) hull.pop_back();
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n;
    polygon a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].x>>a[i].y;
    }
    a = andrewMonotoneChain(a);

    cin>>m;
    polygon b(m);
    for (int i = 0; i < m; i++)
    {
        cin>>b[i].x>>b[i].y;
    }

    b.insert(b.end(), a.begin(), a.end());
    polygon hull = andrewMonotoneChain(b);

    if (a == hull) cout<<"YES"<<'\n';
    else cout<<"NO"<<'\n';

    return 0;
}
