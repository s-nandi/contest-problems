// tree isomorphism (hashing), finding root s.t. all subtrees of root are isomorphic
// https://codeforces.com/contest/1252/problem/F
// 2019 Asia Jakarta Regional

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to;
};
using graph = vector<vector<edge>>;

int get_size(const auto& g, auto& sizes, int curr, int prev = -1) {
    sizes[curr] = 1;
    for (auto [to] : g[curr]) {
        if (to == prev) continue;
        sizes[curr] += get_size(g, sizes, to, curr);
    }
    return sizes[curr];
}

int centroid(const auto& g) {
    int root = 0;
    vector<int> sizes(g.size());
    int total = get_size(g, sizes, root);

    int curr = root;
    for (int prev = -1, old; prev != curr; prev = old) {
        old = curr;
        for (auto [to] : g[curr]) {
            if (to != prev and sizes[to] > total / 2) {
                curr = to;
            }
        }
    }
    return curr;
}

constexpr auto ALPHA = 37;
constexpr auto MOD = 1000000007;

using hash_type = int;
auto hash_if_root(const auto& g, const auto& blocked, int curr, int prev = -1) -> hash_type {
    auto child_sum = 1LL;
    for (auto [to] : g[curr]) {
        if (to == prev or blocked[to]) continue;
        child_sum = (child_sum + hash_if_root(g, blocked, to, curr)) % MOD;
    }
    return ALPHA * child_sum % MOD;
}

void find_reached(const auto& g, const auto& blocked, auto& reached, int curr, int prev = -1) {
    reached.push_back(curr);
    for (auto [to] : g[curr]) {
        if (to == prev or blocked[to]) continue;
        find_reached(g, blocked, reached, to, curr);
    }
}

auto identical_subtrees(const auto& g, int root) -> bool {
    vector<int> blocked(g.size());
    blocked[root] = true;

    auto num_subgraphs = g[root].size();
    vector<vector<int>> subgraph_nodes(num_subgraphs);
    for (int i = 0; i < num_subgraphs; i++) {
        auto to = g[root][i].to;
        find_reached(g, blocked, subgraph_nodes[i], to);
    }

    vector<vector<hash_type>> hashes(num_subgraphs);
    for (int i = 0; i < num_subgraphs; i++) {
        for (auto r : subgraph_nodes[i]) {
            auto h = hash_if_root(g, blocked, r);
            hashes[i].push_back(h);
        }
        sort(begin(hashes[i]), end(hashes[i]));
        hashes[i].erase(unique(begin(hashes[i]), end(hashes[i])), end(hashes[i]));
    }

    map<hash_type, int> num_hashes;
    for (int i = 0; i < num_subgraphs; i++) {
        for (auto h : hashes[i]) {
            if (++num_hashes[h] == num_subgraphs) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    graph g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    auto root = centroid(g);
    if (!identical_subtrees(g, root)) {
        cout << -1 << '\n';
    } else {
        auto num_subtrees = g[root].size();
        cout << num_subtrees << '\n';
    }
}
