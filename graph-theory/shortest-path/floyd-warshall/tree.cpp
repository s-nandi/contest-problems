// floyd warshall, finding k-size set of black nodes w/ minimal diameter (fix extreme points of diameter + count # of black nodes in range)
// http://codeforces.com/gym/101964 (problem C)
// 2018 Southeastern European Regional

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1031231234;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector <int> color(n);
    for (int i = 0; i < n; i++)
        cin >> color[i];

    vvi distances(n, vi(n, INF));
    for (int i = 0; i < n; i++)
        distances[i][i] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        --a, --b;
        distances[a][b] = distances[b][a] = 1;
    }

    if (m == 1)
        cout << 0 << '\n';
    else
    {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);

        int best = INF;
        for (int i = 0; i < n; i++) if (color[i])
        {
            for (int j = i + 1; j < n; j++) if (color[j])
            {
                int dist = distances[i][j];
                int withinDist = 0;
                for (int k = 0; k < n; k++) if (color[k])
                {
                    if (distances[i][k] <= dist and distances[j][k] <= dist)
                        withinDist++;
                }
                if (withinDist >= m)
                    best = min(best, dist);
            }
        }
        cout << best << '\n';
    }
}
