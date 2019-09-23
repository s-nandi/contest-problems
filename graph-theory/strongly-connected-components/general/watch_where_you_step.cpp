// strongly connected components (naive), max # of addable edges without changing SCC
// https://open.kattis.com/problems/watchyourstep
// 2018 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using edge = tuple<int>;  // {to}
using graph = vector<vector<edge>>;

auto dfs(const auto& g, int i, int root, auto& visited, auto& reachable) {
    if (visited[i]) return;
    visited[i] = true;

    reachable[root][i] = true;
    for (const auto& [to] : g[i]) {
        dfs(g, to, root, visited, reachable);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    graph g(n);
    auto matrix = vector(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) {
                g[i].push_back({j});
            }
        }
    }

    auto reachable = matrix;
    for (int i = 0; i < n; i++) {
        auto visited = vector<int>(n);
        dfs(g, i, i, visited, reachable);
    }

    int sol = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j or matrix[i][j]) continue;
            sol += reachable[i][j];
        }
    }
    cout << sol << '\n';
}
