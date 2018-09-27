// tsp, binary search on solution
// https://open.kattis.com/problems/catandmice
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

const double INF = 1031231234.0;
const double EPS = 1e-4;

struct pt
{
    double x, y;

    double dist(const pt &o) const
    {
        double dx = x - o.x, dy = y - o.y;
        return sqrt(dx * dx + dy * dy);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <pt> positions(n + 1);
    vector <double> times(n + 1);

    positions[0] = {0, 0};
    times[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        double x, y, s;
        cin >> x >> y >> s;
        positions[i] = {x, y};
        times[i] = s;
    }

    double scale;
    cin >> scale;

    double l = 0.0, r = INF;
    while (r - l > EPS)
    {
        double init = (l + r) / 2;

        vector <vector<double>> tsp(1 << (n + 1), vector <double>(n + 1, INF));
        tsp[1 << 0][0] = 0.0;
        for (int mask = 1; mask < 1 << (n + 1); mask++)
        {
            int nb = 0;
            for (int i = 0; i <= n; i++) if (mask & (1 << i))
                nb++;
            if (nb <= 1)
                continue;

            double prevSpeed = init;
            for (int i = 0; i < nb - 2; i++) // no penalty for the last mouse (prevSpeed) and for first mouse (since there's no mouse at point 0)
                prevSpeed *= scale;

            for (int i = 0; i <= n; i++) if (mask & (1 << i))
            {
                int submask = mask ^ (1 << i);
                for (int j = 0; j <= n; j++) if (submask & (1 << j))
                {
                    double possible = tsp[submask][j] + positions[i].dist(positions[j]) / prevSpeed;
                    if (possible <= times[i])
                        tsp[mask][i] = min(tsp[mask][i], possible);
                }
            }
        }

        int FULL = (1 << (n + 1)) - 1;
        double best = INF;
        for (int i = 0; i <= n; i++)
            best = min(best, tsp[FULL][i]);

        if (best < INF)
            r = init;
        else
            l = init;
    }
    cout << fixed << setprecision(6) << l << '\n';
}
