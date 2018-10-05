// geometry (tangent to circle is perp., range of x for circle inclusion), binary search on answer, overflow handling
// https://codeforces.com/contest/1059/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ld INF = 1e19;

struct pt
{
    ld x, y;
};

bool check(ld r, vector <pt> &points)
{
    ld last_start = -INF, first_end = INF;
    for (pt p: points)
    {
        if (p.y > 2 * r)
            return false;
        ld dy = abs(p.y - r);
        ld dx = sqrt((r - dy) * (r + dy));
        last_start = max(last_start, p.x - dx);
        first_end = min(first_end, p.x + dx);
    }
    return last_start <= first_end;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector <pt> a(n);
    bool below = false, above = false;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        a[i] = {x, abs(y)};

        below = below | (y < 0);
        above = above | (y > 0);
    }

    if (below and above)
        cout << -1 << '\n';
    else
    {
        ld l = 0.0, r = 1.0;
        while (!check(r, a))
            r *= 2.0;

        for (int i = 0; i < 500; i++)
        {
            ld m = (l + r) / 2;

            if (check(m, a))
                r = m;
            else
                l = m;
        }
        cout << fixed << setprecision(12) << l << '\n';
    }
}
