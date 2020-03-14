// bfs, max # of forced color changes (red/blue) between i and j = min dist from i to j [prove this]
// https://open.kattis.com/problems/onaveragetheyrepurple
// 2019 Mid-Atlantic Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)size(x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
auto bfs(auto& g, int s, int d) {
  queue<int> q;
  q.push(s);
  vi dist(sz(g), INF);
  dist[s] = 0;
  while (!q.empty()) {
    auto curr = q.front();
    q.pop();
    for (auto [to]: g[curr]) {
      if (dist[curr] + 1 < dist[to]) {
        dist[to] = dist[curr] + 1;
        q.push(to);
      }
    }
  }
  return dist[d];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph g(n);
    rep(i, 0, m) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      g[a].PB({b});
      g[b].PB({a});
    }
    cout << bfs(g, 0, n - 1) - 1 << '\n';
}
