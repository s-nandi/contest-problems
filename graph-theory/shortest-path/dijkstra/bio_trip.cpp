// dijkstra, expanded state graph, basic geo
// https://open.kattis.com/problems/biotrip
// 2019 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

struct edge {int to, w, angle;};
typedef vector<vector<edge>> graph;

struct node {
  int index, prev, reached; ll distance;
  bool operator > (const node &o) const {
    return tie(distance, index, prev, reached) > tie(o.distance, o.index, o.prev, o.reached);
  }
};

bool valid_angle(auto a1, auto a2, auto alpha1, auto alpha2) {
  auto hi = a1 + alpha1;
  auto lo = a1 - alpha2;
  for (int i = -3; i <= 3; i++) {
    auto possible = a2 + (360 * i);
    if (lo <= possible and possible <= hi)
      return true;
  }
  return false;
}

map<pair<int, int>, int> angles; 
vector <ll> dijkstra(graph &g, int s, int d, auto alpha1, auto alpha2) {
  priority_queue<node, vector<node>, greater<node>> pq;
  // distances[i][j] = Min distance to i when coming from j
  auto distances = vector(g.size(), vector(g.size(), vector<ll>(2, INF)));
  auto visited = vector(g.size(), vector(g.size(), vector<int>(2)));
  pq.push({s, s, false, 0});
  distances[s][s][0] = 0;
  while(!pq.empty()) {
    node curr = pq.top();
    pq.pop();
    
    auto [index, prev, reached, distance] = curr;
    if(visited[curr.index][curr.prev][reached]) continue;
    visited[curr.index][curr.prev][reached] = true;

    for(edge e : g[curr.index]) {
      auto next_reached = reached or e.to == d;
      if (curr.distance + e.w < distances[e.to][curr.index][next_reached]) {
        bool is_good = true;
        if (curr.index != s) {
          auto entry_angle = (180 + angles[{index, prev}]) % 360;
          is_good = valid_angle(e.angle, entry_angle, alpha1, alpha2);
        }
        if (!is_good) continue;
        distances[e.to][curr.index][next_reached] = curr.distance + e.w;
        pq.push(node{e.to, curr.index, next_reached,
                     distances[e.to][curr.index][next_reached]});
      }
    }
  }
  vector<ll> best(g.size(), INF);
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g.size(); j++) {
      best[i] = min(best[i], distances[i][j][true]);
    }
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, d, a1, a2;
  cin >> n >> d >> a1 >> a2;
  --d;

  graph g(n);
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int to, weight, angle;
      cin >> to >> weight >> angle;
      --to;
      g[i].push_back({to, weight, angle});
      angles[{i, to}] = angle;
    }
  }
  auto distances_to = dijkstra(g, 0, d, a1, a2);
  auto res = distances_to[0];
  if (res >= INF) {
    cout << "impossible" << '\n';
  } else {
    cout << res << '\n';
  }
}
