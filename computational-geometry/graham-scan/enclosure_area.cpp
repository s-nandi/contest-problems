//dynamic convex hull, shoelace theorem, prefix sum, binary search, convex polygon containment
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=757&problem=5971
//2016 Mid-Atlantic Regional

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#define ii pair<int, int>
#define ll long long
#define EPS .0000001

struct pt
{
    ll x, y;

    bool operator < (pt b) const
    {
        if (y < b.y)
        {
            return true;
        }
        else if(abs(y - b.y) < EPS)
        {
            if (x < b.x)
            {
                return true;
            }

        }
        return false;
    }
};

int orientation(pt a, pt b, pt c)
{
    long long val1 = (long long) (b.y - a.y) * (c.x - b.x);
    long long val2 = (long long) (b.x - a.x) * (c.y - b.y);

    if (val1 < val2)
    {
        return -1; //counterclockwise
    }
    else if (val1 > val2)
    {
        return 1; //clockwise
    }
    else
    {
        return 0; //collinear
    }
}


bool inTriangle(pt a, pt b, pt c, pt p)
{
    if (orientation(a, b, c) != orientation(a, b, p))
    {
        return false;
    }
    if (orientation(b, c, a) != orientation(b, c, p))
    {
        return false;
    }
    if (orientation(c, a, b) != orientation(c, a, p))
    {
        return false;
    }
    return true;

}


vector <pt> grahamScan(vector <pt> points) //creates clockwise convex polygon
{
    pt bottom = points[0];
    int bottomInd = -1;

    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].y == bottom.y)
        {
            if (points[i].x < bottom.x)
            {
                bottom = points[i];
                bottomInd = i;
            }
        }
        else if(points[i].y < bottom.y)
        {
            bottom = points[i];
            bottomInd = i;
        }
    }


    sort(points.begin(), points.end(),
         [bottom](pt a, pt b)
    {
        if (bottom.x == a.x and bottom.y == a.y)
        {
            return true;
        }
        if (bottom.x == b.x and bottom.y == b.y)
        {
            return false;
        }
        int orient = orientation(bottom, a, b);
        if (orient == 0)
        {
            int dista = abs(a.x - bottom.x);
            int distb = abs(b.x - bottom.x);

            if (dista == distb)
            {
                return b < a;
            }
            return dista > distb;
        }
        return orient == 1;
    });

    bool includeNext = true;

    vector <pt> vPoints = {points[0]};
    vector <pt> skipped;
    for (int i = 1; i < points.size(); i++)
    {
        if (includeNext)
        {
            vPoints.push_back(points[i]);
        }
        else
        {
            skipped.push_back(points[i]);
        }

        includeNext = true;
        if(orientation(points[0], points[i], points[i + 1]) == 0)
        {
            includeNext = false;
        }
    }

    vector <pt> hull;
    hull.push_back(vPoints[0]);
    hull.push_back(vPoints[1]);
    hull.push_back(vPoints[2]);

    for (int i = 3; i < vPoints.size(); i++)
    {
        while (orientation(hull[hull.size() - 2], hull[hull.size() - 1], vPoints[i]) != 1) // != 1 if you don't want points on hull, == -1 if include points on hull
        {
            hull.pop_back();
        }
        hull.push_back(vPoints[i]);
    }

    return hull;
}

int ump_ccw(int i, int offset, int sz)
{
    return (sz + offset - i) % sz;
}

int ump_cw(int i, int offset, int sz)
{
    return (sz + offset + i) % sz;
}

pair <int, int> findTangent(vector <pt> &hull, pt p, pt center)
{
    int sz = hull.size();
    int rightInit;
    int leftInit;

    if (orientation(center, hull[0], p) != 1 and orientation(center, hull[sz - 1], p) != -1)
    {
        rightInit = 0;
    }
    else
    {
        rightInit = lower_bound(hull.begin(), hull.end(), p, [center](pt a, pt b)
                          {
                                return orientation(center, a, b) == 1;
                          }) - hull.begin();
    }

    leftInit = (sz + rightInit - 1) % sz;

    if (inTriangle(center, hull[leftInit], hull[rightInit], p))
    {
        return {-1, -1};
    }


    int left, right;

    int l, r;
    l = 0;
    r = sz - 1;

    while (l < r)
    {
        int m = (l + r + 1) / 2;

        pt curr = hull[ump_ccw(m, leftInit, sz)];
        pt next = hull[(ump_ccw(m, leftInit, sz) + 1) % sz];

        if (orientation(p, curr, next) != 1 and orientation(center, curr, p) != -1)
        {
            l = m;
        }
        else
        {
            r = m - 1;
        }
    }

    left = ump_ccw(l, leftInit, sz);

    l = 0;
    r = sz - 1;

    while (l < r)
    {
        int m = (l + r + 1) / 2;

        pt curr = hull[ump_cw(m, rightInit, sz)];
        pt next = hull[(sz + ump_cw(m, rightInit, sz) - 1) % sz];

        if (orientation(p, curr, next) != -1 and orientation(center, curr, p) != 1)
        {
            l = m;
        }
        else
        {
            r = m - 1;
        }
    }

    right = ump_cw(l, rightInit, sz);

    pair <int, int> res =  {left, right};
    return res;
}

ll shoelaceLink(pt a, pt b)
{
    return (ll) a.x * b.y - (ll) a.y * b.x;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin>>n>>k)
    {
        vector <pt> town(k);
        for (int i = 0; i < k; i++)
        {
            cin>>town[i].x>>town[i].y;
        }

        vector <pt> options(n - k);
        for (int i = 0; i < n - k; i++)
        {
            cin>>options[i].x>>options[i].y;
        }

        vector <pt> poly = grahamScan(town);

        vector <ll> shoelace (poly.size() + 1);
        shoelace[0] = 0;

        pt center = {0, 0};

        for (int i = 1; i <= poly.size(); i++)
        {
            pt prevPt = poly[i - 1];
            pt currPt = poly[i % poly.size()];
            shoelace[i] = shoelace[i - 1] + shoelaceLink(prevPt, currPt);

            center.x += double (poly[i - 1].x) / poly.size();
            center.y += double (poly[i - 1].y) / poly.size();
        }

        ll maxArea = 0;
        maxArea = abs(shoelace[poly.size()]);

        for (pt p: options)
        {
            pair <int, int> tangents = findTangent(poly, p, center);

            int leftTangent = tangents.first;
            int rightTangent = tangents.second;

            if (leftTangent == -1) //point is in polygon
            {
                continue;
            }

            ll area = 0;
            if (leftTangent < rightTangent)
            {
                area = (ll) shoelace[leftTangent] + (ll) shoelace[poly.size()] - (ll) shoelace[rightTangent] + shoelaceLink(poly[leftTangent], p) + shoelaceLink(p, poly[rightTangent]);
            }

            else
            {
                area = (ll) shoelace[leftTangent] - (ll) shoelace[rightTangent] + shoelaceLink(poly[leftTangent], p) + shoelaceLink(p, poly[rightTangent]);
            }

            area = abs(area);
            maxArea = max(area, maxArea);
        }

        if (maxArea & 1)
        {
            cout<<maxArea / 2<<".5"<<'\n';

        }
        else
        {
            cout<<maxArea / 2<<".0"<<'\n';

        }

    }
}

