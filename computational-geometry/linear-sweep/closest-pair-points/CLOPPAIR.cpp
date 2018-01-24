#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <iomanip>

using namespace std;

#define INF 1231231234

struct pt
{
    int x, y, index;

    bool operator < (pt o) const
    {
        if (y != o.y) return y < o.y;
        else return x < o.x;
    }

    double dist(pt o) const
    {
        return sqrt((o.x - x) * (o.x - x) + (o.y - y) * (o.y - y));
    }
};

pair <pt, pt> closestPairPoints(vector <pt> &points)
{
    set <pt> window;
    sort(points.begin(), points.end(), [](pt a, pt b){ return a.x != b.x ? a.x < b.x : a.y < b.y; });
    window.insert(points[0]);

    double closest = INF;
    int leftMost = 0;
    pair <pt, pt> res;

    for (int i = 1; i < points.size(); i++)
    {
        while(i > leftMost and points[i].x - points[leftMost].x > closest) window.erase(points[leftMost++]);

        pt bottomMost = {points[i].x, int(points[i].y - closest + .5), -1};
        pt topMost = {points[i].x, int(points[i].y + closest), -1};
        for (auto it = window.lower_bound(bottomMost); it != window.upper_bound(topMost); it++)
        {
            double distBetween = it -> dist(points[i]);
            if (distBetween < closest)
            {
                closest = distBetween;
                res = {*it, points[i]};
            }
        }
        window.insert(points[i]);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setprecision(6);

    int n;
    cin>>n;

    vector <pt> points(n);

    for (int i = 0; i < n; i++)
    {
        cin>>points[i].x>>points[i].y;
        points[i].index = i;
    }

    auto solution = closestPairPoints(points);
    pt a = solution.first, b = solution.second;
    if (a.index > b.index) swap(a, b);
    cout<<fixed<<a.index<<" "<<b.index<<" "<<a.dist(b)<<'\n';

    return 0;
}
