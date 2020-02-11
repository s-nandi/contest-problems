// multi-source bfs (finding node that is equidistant to a given subset of nodes)
// https://codeforces.com/gym/102411/problem/E
// 2019 Northwestern Russia Regional

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(x) (int)size(x)
 
using ll = long long;
using ld = long double;
using vi = vector<int>;
 
struct edge {int to;};
using graph = vector<vector<edge>>;
 
auto bfs(graph& g, vi& a) {
    vi weights(sz(g));
    queue<tuple<int, int, int>> q;
    vi dist(sz(g), -1);
    trav(i, a) {
        q.push({i, -1, 0});
        weights[i] = 1;
        dist[i] = 0;
    }
    
    while (!q.empty()) {
        auto [curr, prev, d] = q.front();
        q.pop();
 
        if (weights[curr] == sz(a))
            return curr;
        
        for (auto [to]: g[curr]) {
            if (d + 1 == dist[to] or dist[to] == -1) {
                if (dist[to] == -1) {
                    q.push({to, curr, d + 1});
                }
                weights[to] += weights[curr];
                dist[to] = d + 1;
            }
        }
    }
    return -1;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    auto g = graph(n);
    rep(i, 0, n - 1) {
        int v, u;
        cin >> v >> u;
        --v; --u;
        g[v].push_back({u});
        g[u].push_back({v});
    }
    auto a = vector<int>(m);
    trav(i, a) {
        cin >> i;
        --i;
    }
 
    auto center = bfs(g, a);
    if (center >= 0) {
        cout << "YES" << '\n';
        cout << (center + 1) << '\n';
    } else {
        cout << "NO" << '\n';
    }
}
