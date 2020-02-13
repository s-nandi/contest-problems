// two pointer method, cycle finding in graph where edge(a, b) => arr[a..b] = k, cutting circle into equal partitions
// https://nena19.kattis.com/problems/cuttingthenecklace
// 2019 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)x.size()

struct edge{int to;};
using graph = vector<vector<edge>>;

auto get_edges(const auto& a, auto target) {
    auto n = sz(a);
    vector<pair<int, int>> pairs;
    long long acc = a[0];
    for (int l = 0, r = 0; l < n; ++l) {
        while (r + 1 < n and acc < target) {
            acc += a[r + 1];
            ++r;
        }
        if (acc == target) {
            pairs.push_back({l, r});
        }
        if (l < n) acc -= a[l];
    }
    return pairs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<int> a(n);
    trav(i, a) cin >> i;

    auto total = accumulate(all(a), 0LL);
    if (total % k != 0) {
        cout << "NO" << '\n';
        return 0;
    }
    auto avg = total / k;
    if (any_of(all(a), [avg](auto num){return num > avg;})) {
        cout << "NO" << '\n';
        return 0;
    }
    
    vector<int> b(2 * n);
    rep(i, 0, n) {
        b[i] = a[i];
        b[i + n] = a[i];
    }

    auto edges = get_edges(b, avg);
    graph g(n);
    for (auto& [a, b]: edges) {
        if (a >= n) a -= n;
        if (b >= n) b -= n;
        auto ato = (b + 1) % n;

        g[a].push_back({ato});
    }

    vector<int> visited(n);
    vector<int> onstack(n);
    function<int(int)> dfs =
        [&](int curr) {
            if (visited[curr]) return onstack[curr];
            visited[curr] = true;
            onstack[curr] = true;

            auto has_cycle = 0;
            for (auto [to]: g[curr]) {
                has_cycle |= dfs(to);
            }
            onstack[curr] = false;
            return has_cycle;
        };
    
    auto feas = false;
    rep(i, 0, n) {
        if (!visited[i]) {
            feas |= dfs(i);
        }
    }
    cout << (feas ? "YES" : "NO") << '\n';
}
