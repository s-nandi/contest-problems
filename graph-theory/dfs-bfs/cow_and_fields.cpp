// BFS, greedy, binary search
// https://codeforces.com/contest/1307/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1231231234;
auto bfs(auto& g, int s) {
    vi dist(sz(g), INF), vis(sz(g));
    dist[s] = 0; vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        for (auto [to]: g[curr]) {
            dist[to] = min(dist[to], dist[curr] + 1);
            if (!vis[to]) {
                q.push(to);
                vis[to] = true;
            }
        }
    }
    return dist;
}

optional<int> max_not_greater(auto& cont, auto dist) {
    int it = upper_bound(all(cont), dist) - begin(cont);
    if (it >= 2) return cont[it - 2];
    else return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vi special(k);
    rep(i, 0, k) {
        cin >> special[i];
        --special[i];
    }
    graph g(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].PB({b});
        g[b].PB({a});
    }
    auto s_dist = bfs(g, 0);
    auto d_dist = bfs(g, n - 1);
    auto base = s_dist[n - 1];
    vi spec_dists(k);
    rep(i, 0, k) {
        spec_dists[i] = s_dist[special[i]];
    }
    sort(all(spec_dists));

    auto best = -1;
    trav(s, special) {
        auto new_from_source = max_not_greater(spec_dists, s_dist[s]);
        if (!new_from_source) continue;
        auto possible = *new_from_source + 1 + d_dist[s];
        best = max(best, possible);
    }
    if (best != -1) best = min(best, base);
    cout << best << '\n';
}
