// scale and rotate trick to reach max. # of objects given ratio of horizontal/vertical speed, longest increasing subsequence
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5396
// 2015 Pacific Northwest Regional

#include <bits/stdc++.h>

using namespace std;

struct pt
{
    long long x, y;

    pt rotateCw45()
    {
        return {x + y, y - x};
    }

    pt scaleX(long long k)
    {
        return {k * x, y};
    }

    bool operator < (const pt &o) const
    {
        return make_pair(x, y) < make_pair(o.x, o.y);
    }
};

int longestNonDecreasingSubsequence(vector <pt> &points)
{
    vector <pt> dp;
    for (pt p: points)
    {
        auto cmpByY = [](const pt &a, const pt &b)
        {
            return a.y <= b.y;
        };
        int pos = lower_bound(dp.begin(), dp.end(), p, cmpByY) - dp.begin();
        if (pos == dp.size())
            dp.push_back(p);
        else
            dp[pos] = p;
    }
    return dp.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, r, w, h;
    while (cin >> n >> r >> w >> h)
    {
        vector <pt> points(n);
        for (int i = 0; i < n; i++)
        {
            pt p;
            cin>>p.x>>p.y;
            points[i] = p.scaleX(r).rotateCw45();
        }
        sort(points.begin(), points.end());
        cout << longestNonDecreasingSubsequence(points) << '\n';
    }
    return 0;
}
