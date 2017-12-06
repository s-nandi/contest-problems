//radial sweep
//https://icpc.kattis.com/problems/oil2 (2016 ICPC World Finals)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

struct pt
{
    int x;
    int y;
};

int orientation(pt a, pt b, pt c)
{
    ll val1 = (ll) (b.y - a.y) * (c.x - b.x);
    ll val2 = (ll) (b.x - a.x) * (c.y - b.y);

    if (val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct event
{
    pt p;
    int val;

    bool operator < (event o) const
    {
        int orient = orientation({0, 0}, p, o.p);
        if (orient == 0)
        {
            return val > o.val;
        }
        return orient == 1;
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n;

    cin>>n;

    vector <event> pts(2*n);

    int x0, x1, y, f, s;
    for (int i = 0; i < 2*n; i+=2)
    {
        cin>>f>>s>>y;
        x0 = min(f, s);
        x1 = max(f, s);
        pts[i] = {{x0, y}, x1 - x0};
        pts[i + 1] = {{x1, y}, x0 - x1};
    }

    int maxVal = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        pt origin = pts[i].p;
        int currVal = abs(pts[i].val);
        maxVal = max(maxVal, currVal);

        vector <event> validPoints;

        for (int j = 0; j < 2 * n; j++)
        {
            pt candidate = pts[j].p;

            if (candidate.y > origin.y)
            {
                validPoints.push_back({{candidate.x - origin.x, candidate.y - origin.y}, pts[j].val});
            }
            else if (candidate.y < origin.y) //reflect across origin
            {
                validPoints.push_back({{-(candidate.x - origin.x), -(candidate.y - origin.y)}, -pts[j].val});
            }
        }

        pt pto = {0, 0};

        sort(validPoints.begin(), validPoints.end());


        for (int j = 0; j < validPoints.size(); j++)
        {
            currVal += validPoints[j].val;
            maxVal = max(maxVal, currVal);
        }
    }

    cout<<maxVal<<'\n';
    return 0;
}
