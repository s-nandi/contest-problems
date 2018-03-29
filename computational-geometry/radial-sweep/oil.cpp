//radial sweep (double ended)
//https://icpc.kattis.com/problems/oil2 (2016 ICPC World Finals)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

typedef ll ptT;
struct pt
{
    ptT x, y;
    int val;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    pt reflect(const pt &o) const {return o + o - *this;}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    auto cp = (b - o) ^ (a - o);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0);
}

struct polarCmp
{
    const pt o;

    polarCmp(const pt &origin) : o(origin) {}
    bool operator () (const pt &a, const pt &b) const
    {
        int orient = orientation(o, a, b);
        return orient == 1 or (orient == 0 and a.val > b.val);
    }
};

int findBest(vector <pt> points, const pt &origin)
{
    int best = abs(origin.val);
    polarCmp cmp(origin);
    auto pivot = partition(points.begin(), points.end(), [&origin](const pt &p){return p.y == origin.y;});
    for (pt &p: points) if (p.y != origin.y)
    {
        int sv = p.val;
        if (p.y < origin.y) p = p.reflect(origin), p.val = -1 * sv;
    }
    sort(pivot, points.end(), cmp);
    int cv = best;
    for (pt &p: points) if (p.y != origin.y)
        cv += p.val, best = max(best, cv);
    return best;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <pt> points(2 * n);
    for (int i = 0; i < 2 * n; i += 2)
    {
        int x0, x1, y;
        cin>>x0>>x1>>y;
        if (x0 == x1) continue;
        if (x0 > x1) swap(x0, x1);
        points[i] = {x0, y, x1 - x0};
        points[i + 1] = {x1, y, x0 - x1};
    }

    int maxVal = 0;
    for (pt origin: points) maxVal = max(maxVal, findBest(points, origin));
    cout<<maxVal<<'\n';

    return 0;
}
