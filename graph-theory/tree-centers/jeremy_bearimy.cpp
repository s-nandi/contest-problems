// pairing across centroid, greedy + bfs crawl, pairing nodes on tree s.t. sum of path lengths is maximized/minimized
// https://codeforces.com/contest/1280/problem/C

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
struct edge {
    int to, w;
};
using graph = vector<vector<edge>>;
 
int calc_size(const auto& g, auto& sizes, int curr, int prev = -1) {
    sizes[curr] = 1;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        sizes[curr] += calc_size(g, sizes, e.to, curr);
    }
    return sizes[curr];
}
 
void find_centroids(const auto& g, const auto& sizes, int all, auto& res, int curr, int prev = -1) {
    auto is_centroid = true;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        is_centroid &= sizes[e.to] <= all / 2;
        if (sizes[e.to] >= all / 2 and all - sizes[e.to] <= all / 2)
            find_centroids(g, sizes, all, res, e.to, curr);
    }
    if (is_centroid) res.push_back(curr);
}
 
auto centroids(const graph& g) {
    vector<int> centroids, sizes(g.size());
    auto total = calc_size(g, sizes, 0);
    find_centroids(g, sizes, total, centroids, 0);
    return centroids;
}
 
void dfs_dist(auto& g, int curr, auto& distances, ll dist = 0, int prev = -1) {
    distances[curr] = dist;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        dfs_dist(g, e.to, distances, dist + e.w, curr);
    }
}
 
auto getworst(const auto& g) {
    auto my_centroids = centroids(g);
    auto c = my_centroids[0];
    auto n = (int)g.size();
    vector<ll> distances(n);
    dfs_dist(g, c, distances);
    return accumulate(begin(distances), end(distances), 0LL);
}
 
long long getbest(const auto& g) {
    using state = pair<ll, int>;  // distance, index
    auto n = (int)g.size();
    vector<priority_queue<state, vector<state>, greater<state>>> contained(n);
    vector<int> degrees(n);
    for (int i = 0; i < n; i++) {
        degrees[i] = g[i].size();
        contained[i].push({0, i});
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (degrees[i] == 1) {
            q.push(i);
            degrees[i] = 0;
        }
    }
    ll sol = 0;
    vector<int> visited(n);
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        visited[curr] = true;
 
        while (contained[curr].size() >= 2) {
            auto mx1 = contained[curr].top();
            contained[curr].pop();
            auto mx2 = contained[curr].top();
            contained[curr].pop();
            sol += mx1.first + mx2.first;
        }
 
        for (auto e : g[curr]) {
            if (visited[e.to]) continue;
            if (contained[curr].size() > 0) {
                assert(contained[curr].size() == 1);
                auto only = contained[curr].top();
                contained[curr].pop();
                only.first += e.w;
                contained[e.to].push(only);
            }
            if (--degrees[e.to] == 1) {
                q.push(e.to);
            }
        }
    }
    return sol;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
    while (T--) {
        int k;
        cin >> k;
        int n = 2 * k;
        graph g(n);
        for (int i = 0; i < n - 1; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            --a;
            --b;
            g[a].push_back({b, w});
            g[b].push_back({a, w});
        }
        auto best = getbest(g);
        auto worst = getworst(g);
        cout << best << " " << worst << '\n';
    }
}
