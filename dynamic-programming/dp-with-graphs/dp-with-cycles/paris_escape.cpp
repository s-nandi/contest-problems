// dp with probabilities (dijkstra to handle cycles), markov model (EV of agent being at specific node at time t)
// https://utipc20s.kattis.com/problems/utipc20s.parisescape
// 2020 UT Spring Programming Contest

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 500;
const int MITERS = MAXN * 20 + 10; // didn't prove this; just try large value that will fit in memory/time
ld ev[MAXN + 5][MITERS + 5]; // ev[j][k] = expected # of guards at node j, time k
ld prob[MAXN + 5][MITERS + 5];
bool vis[MAXN + 5][MITERS + 5];

using state = tuple<int, int>; // node, time
void simulate(graph& g, int start) {
  queue<state> q;
  q.push({start, 0});
  rep(i, 0, sz(g)) rep(j, 0, MITERS + 1) prob[i][j] = 0;
  memset(vis, 0, sizeof(vis));
  prob[start][0] = 1.0;
  while (!q.empty()) {
    auto [i, tm] = q.front(); q.pop();
    if (tm == MITERS) continue;
    auto p_out = 1.L / sz(g[i]);
    trav(e, g[i]) {
      prob[e.to][tm + 1] += p_out * prob[i][tm];
      if (!vis[e.to][tm + 1]) {
        q.push({e.to, tm + 1});
        vis[e.to][tm + 1] = true;
      }
    }
  }
}

constexpr auto INF = numeric_limits<ld>::max() / 5;
using node = tuple<ld, int, int>; // distance, index, time
ld distances[MAXN + 5][MITERS + 5];

auto minn(auto& a, auto b) {
  if (b < a){a = b; return true;}
  return false;
}

ld dijkstra(graph &g, int s, int t) {
  priority_queue<node, vector<node>, greater<node>> pq;
  pq.push({0, s, 0});
  rep(i, 0, sz(g)) rep(j, 0, MITERS + 1) distances[i][j] = INF; 
  distances[s][0] = 0.0;
  memset(vis, 0, sizeof(vis));
  while(!pq.empty()) {
    auto [distance, i, tm] = pq.top(); pq.pop();
    if (i == t) return distance;
    if (tm == MITERS) continue;
    if (vis[i][tm]) continue;
    vis[i][tm] = true;
    trav(e, g[i]) {
      auto cost = ev[e.to][tm + 1];
      if (minn(distances[e.to][tm + 1], distance + cost))
        pq.push({distances[e.to][tm + 1], e.to, tm + 1});
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].PB({v});
    g[v].PB({u});
  }
  
  int p;
  cin >> p;
  vi st(p);
  trav(i, st) cin >> i;
  rep(i, 0, p) {
    simulate(g, st[i]);
    rep(j, 0, n) rep(k, 0, MITERS + 1)
      ev[j][k] += prob[j][k];
  }
  auto res = dijkstra(g, 0, n - 1);
  cout << fixed << setprecision(11) << res << '\n';
}
