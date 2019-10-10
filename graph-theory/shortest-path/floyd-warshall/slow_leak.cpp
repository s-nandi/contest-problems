// floyd-warshall, building metagraph only with bounded cost edges
// https://open.kattis.com/problems/slowleak
// 2019 North American Qualifier

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr auto INF = (1LL << 31);

auto floyd_warshall(auto costs) {
    for (int k = 0; k < size(costs); k++) {
        for (int i = 0; i < size(costs); i++) {
            for (int j = 0; j < size(costs); j++) {
                costs[i][j] = min(costs[i][j], costs[i][k] + costs[k][j]);
            }
        }
    }
    return costs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t, d;
    cin >> n >> m >> t >> d;

    auto stations = vector<int>(t);
    for (auto& station : stations) {
        cin >> station;
        --station;
    }
    stations.push_back(0);

    auto dists = vector(n, vector(n, INF));
    for (int i = 0; i < m; i++) {
        int a, b, dist;
        cin >> a >> b >> dist;
        --a, --b;
        dists[a][b] = dists[b][a] = dist;
    }
    dists = floyd_warshall(dists);

    auto allowed = vector(n, vector(n, INF));
    for (int station : stations) {
        transform(begin(dists[station]), end(dists[station]), begin(allowed[station]),
                  [d](auto dist) { return (dist <= d) ? dist : INF; });
    }
    allowed = floyd_warshall(allowed);

    auto sol = allowed[0][n - 1];
    if (allowed[0][n - 1] != INF)
        cout << allowed[0][n - 1] << '\n';
    else
        cout << "stuck" << '\n';
}
