// binary search on answer, floyd-warshall, building metagraph (direct edge for all paths w/ cost <= threshold)
// http://codeforces.com/gym/101655 (problem B)
// 2013 Pacific NW Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1e17;

template <typename T> using vt = vector<T>;
template <typename T> using vvt = vt<vt<T>>;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--)
    {
        int n, lim, m;
        cin >> n >> lim >> m;

        vvt <ll> floyd(n, vt<ll>(n, INF));
        for (int i = 0; i < n; i++)
            floyd[i][i] = 0;

        for (int i = 0; i < m; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;
            floyd[a][b] = floyd[b][a] = w;
        }

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);

        ll l = 0, r = 1e11 + 5;
        while (l < r)
        {
            auto mid = (l + r) / 2;

            vvt <ll> meta(n, vt<ll>(n, INF));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) if (floyd[i][j] <= mid)
                    meta[i][j] = 1;

            for (int k = 0; k < n; k++)
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        meta[i][j] = min(meta[i][j], meta[i][k] + meta[k][j]);

            bool allFound = true;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (meta[i][j] > lim)
                        allFound = false;

            if (allFound)
                r = mid;
            else
                l = mid + 1;
        }
        cout << l << '\n';
    }
}
