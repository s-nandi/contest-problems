// dfs (bipartite checking), joining two disjoint bipartite graphs with one edge will be bipartite
// https://open.kattis.com/problems/hoppers
// 2018 Singapore Regional

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to;
};
using graph = vector<vector<edge>>;

auto dfs_bipartite(graph& g, int curr, auto& visited, auto& color) {
    if (visited[curr]) return true;
    visited[curr] = true;

    auto bipartite = true;
    for (auto [to] : g[curr]) {
        auto expected_color = 1 - *color[curr];
        if (color[to] && *color[to] != expected_color) bipartite = false;
        if (visited[to]) continue;
        color[to] = expected_color;
        bipartite &= dfs_bipartite(g, to, visited, color);
    }
    return bipartite;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph g(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    auto num_components = 0;
    auto is_bipartite = true;
    auto visited = vector<int>(n);
    auto color = vector<optional<int>>(n, nullopt);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            color[i] = 0;
            is_bipartite &= dfs_bipartite(g, i, visited, color);
            num_components++;
        }
    }
    auto sol = (num_components - 1) + is_bipartite;
    cout << sol << '\n';
}
