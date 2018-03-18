//closest pair of points (line sweep)
//http://www.spoj.com/problems/CLOPPAIR/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long

typedef int ptsT; //PS: otherwise double
typedef ll ptlT; //PS: otherwise long double

const ll INF = 1e18;

struct pt
{
    ptsT x, y;
    int index;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptlT operator * (const pt &o) const {return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2() const {return *this * *this;}
    ptlT dist2(const pt &o) const {return (*this - o).norm2();}
};

inline ptlT square(ptsT i) {return (ptlT) i * i;}

pair <pt, pt> closestPairPoints(vector <pt> &points)
{
    sort(points.begin(), points.end(), [](pt a, pt b){return make_pair(a.x, a.y) < make_pair(b.x, b.y);});
    set <pt> window = {points[0]};

    ptlT closest = INF;
    pair <pt, pt> res;
    for (int i = 1, left = 0; i < points.size(); i++)
    {
        while(i > left and square(points[i].x - points[left].x) > closest) window.erase(points[left++]);

        pt lb = {points[i].x, (ptsT) ceil(points[i].y - sqrt(closest)), -1};
        pt ub = {points[i].x, (ptsT) floor(points[i].y + sqrt(closest)), -1};
        for (auto it = window.lower_bound(lb); it != window.upper_bound(ub); it++)
        {
            auto dist = it -> dist2(points[i]);
            if (dist < closest) closest = dist, res = {*it, points[i]};
        }
        window.insert(points[i]);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <pt> points(n);
    for (int i = 0; i < n; i++)
    {
        cin>>points[i].x>>points[i].y;
        points[i].index = i;
    }

    auto sol = closestPairPoints(points);
    pt a = sol.first, b = sol.second;
    if (a.index > b.index) swap(a, b);
    cout<<setprecision(6)<<fixed<<a.index<<" "<<b.index<<" "<<sqrt(a.dist2(b))<<'\n';

    return 0;
}
