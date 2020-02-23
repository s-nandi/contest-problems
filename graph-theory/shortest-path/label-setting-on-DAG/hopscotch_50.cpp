// sh. path on DAG
// https://open.kattis.com/problems/hopscotch50
// North American Championship 2020

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define PB push_back

const int INF = 1031231234;
auto minn(auto& a, auto b) {
    if (b < a) {a = b;}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    auto grid = vector(n, vi(n));
    auto positions = vector(k, vector<ii>{});
    rep(i, 0, n) {
        rep(j, 0, n) {
            cin >> grid[i][j];
            --grid[i][j];
            positions[grid[i][j]].PB({i, j});
        }
    }
    auto dists = vector(n, vi(n, INF));
    rep(i, 0, n) rep(j, 0, n) {
        if (grid[i][j] == 0)
            dists[i][j] = 0;
    }
    rep(v, 0, k - 1) {
        for(auto [x1, y1]: positions[v]) {
            for (auto [x2, y2]: positions[v + 1]) {
                auto dist = abs(x1 - x2) + abs(y1 - y2);
                minn(dists[x2][y2], dists[x1][y1] + dist);
            }
        }
    }
    auto best = INF;
    rep(i, 0, n) rep(j, 0, n) {
        if (grid[i][j] == k - 1)
            minn(best, dists[i][j]);
    }
    cout << (best < INF ? best : -1) << '\n';
}
