// weighted matching, virtual nodes (to allow partial match, requiring >= 1 match), calc. delta off of worst case
// https://open.kattis.com/problems/cordonbleu
// 2017 Southwestern Europe Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)
#define PB push_back

constexpr int INF = 1031231234;

template <typename costT>
pair<costT, vi> hungarian(const vector<vector<costT>>& a) {
  static constexpr auto oo = numeric_limits<costT>::max();
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  assert(n <= m);
  vector<costT> u(n), v(m);
  vi p(m), ans(n - 1);
  rep(i,1,n) {
    p[0] = i;
    int j0 = 0; // add "dummy" worker 0
    vector<costT> dist(m, oo);
    vi pre(m, -1), done(m + 1);
    do { // dijkstra
      done[j0] = true;
      int i0 = p[j0], j1;
      auto delta = oo;
      rep(j,1,m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      rep(j,0,m) {
        if (done[j]) u[p[j]] += delta, v[j] -= delta;
        else dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) { // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans}; // min cost
}

struct pt {
  int x, y;
  int dist(const auto& o) {return abs(x - o.x) + abs(y - o.y);}
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<pt> b(n), c(m);
  trav(p, b) cin >> p.x >> p.y;
  trav(p, c) cin >> p.x >> p.y;
  pt base;
  cin >> base.x >> base.y;

  auto acc = 0;
  rep(i, 0, n)
    acc += 2 * base.dist(b[i]);
  bool flipped = false;
  int d1 = 2 * n - 1;
  int d2 = m;
  if (d1 > d2) {
    swap(d1, d2);
    flipped = true;
  }
  auto costs = vector(d1, vector<int>(d2));
  rep(i, 0, 2 * n - 1){
    rep(j, 0, m) {
      int ind1 = !flipped ? i: j;
      int ind2 = !flipped ? j : i;
      if (i < sz(b)) {
        auto savings = b[i].dist(base) - b[i].dist(c[j]);
        costs[ind1][ind2] = -savings; // maximize savings
      } else
        costs[ind1][ind2] = 0;
    }
  }
  auto [matched_savings, assignment] = hungarian(costs);
  matched_savings *= -1; // undo earlier negation
  cout << acc - matched_savings << '\n';
}
