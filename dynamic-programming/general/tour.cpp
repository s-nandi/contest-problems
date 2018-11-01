// bitonic tour (2d points, euclidean distance)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1306
// 2005 Southeastern European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld INF = 1e20;

typedef int ptT;
struct pt
{
    ptT x, y;

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT norm2() const {return x * x + y * y;}
    ld dist(const pt &o) const {return sqrt((*this - o).norm2());};
};

ld bitonicTour(vector <pt> &points)
{
    int n = points.size();
    if (n < 2)
        return 0;

    auto cmp = [](const pt &a, const pt &b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    };
    sort(points.begin(), points.end(), cmp);

    vector <vector<ld>> dp(n, vector<ld>(n, INF)), costs(n, vector<ld>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            costs[i][j] = points[i].dist(points[j]);

dp[0][1] = costs[0][1];
    for (int j = 2; j < n; j++)
    {
        for (int i = 0; i < j; i++)
        {
            if (i < j - 1)
                dp[i][j] = dp[i][j - 1] + costs[j - 1][j];
            else
            {
                for (int k = 0; k < j - 1; k++)
                    dp[j - 1][j] = min(dp[j - 1][j], dp[k][j - 1] + costs[k][j]);
            }
        }

    }
    return dp[n - 2][n - 1] + costs[n - 2][n - 1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n)
    {
        vector <pt> points(n);
        for (int i = 0; i < n; i++)
        {
            cin >> points[i].x >> points[i].y;
        }
        cout << fixed << setprecision(2) << bitonicTour(points) << '\n';
    }
}
