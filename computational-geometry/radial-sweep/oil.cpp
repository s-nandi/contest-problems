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
    for (pt origin: points)
    {
        int currVal = abs(origin.val);
        maxVal = max(maxVal, currVal);

        vector <pt> reflected;
        for (const pt &p: points) if (p.y != origin.y)
        {
            pt r = p;
            if (p.y < origin.y) r = p.reflect(origin), r.val = -1 * p.val;
            reflected.push_back(r);
        }
        polarCmp cmp(origin);
        sort(reflected.begin(), reflected.end(), cmp);

        for (pt p: reflected)
        {
            currVal += p.y > origin.y ? p.val : -p.val;
            maxVal = max(maxVal, currVal);
        }
    }

    cout<<maxVal<<'\n';
    return 0;
}
