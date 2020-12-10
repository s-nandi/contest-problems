// shortest path properties (sh[v] <= sh[u] + w_uv), floyd-warshall (neg cycle check), bipartite check, proofy
// https://codeforces.com/contest/1450/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto
 
struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto INF = 1031231234;
auto minn(auto& a, auto b){a = min(a, b);}
auto maxx(auto& a, auto b){a = max(a, b);}
 
bool is_bipartite(const graph& g, int i, auto& color, int col = 0) {
  if (~color[i]) return color[i] == col;
  color[i] = col;
  trav(e, g[i])
    if (!is_bipartite(g, e.to, color, 1 - col)) return false;
  return true;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  /*
   * If the input graph is not bipartite, no assignment is possible since each edge (either +1 or -1) flips the parity by 1
   * and thus the parity on an odd-cycle leads to a constradiction
   *
   * Fix a node i with label 0 (this person has minimum income), then we know that any node j cannot have a label larger than
   * shpath[i][j]. It is possible to show that such an assignment (using shpath) is optimal and leads to a feasible solution due
   * to bipartiteness
   */
 
  int n, m;
  cin >> n >> m;
  graph bip(n);
  auto dist = vector(n, vi(n, INF));
  rep(it, 0, m) {
    int u, v, t;
    cin >> u >> v >> t;
    --u; --v;
    bip[u].PB({v});
    bip[v].PB({u});
    if (t == 0) {
      dist[u][v] = 1;
      dist[v][u] = 1;
    } else {
      dist[u][v] = 1;
      dist[v][u] = -1;
    }
  }
  rep(i, 0, n) dist[i][i] = 0;
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    minn(dist[i][j], dist[i][k] + dist[k][j]);

  rep(i, 0, n) if (dist[i][i] < 0) {
    cout << "NO" << '\n';
    exit(0);
  }
  {
    vi color(n, -1);
    if (!is_bipartite(bip, 0, color)) {
      cout << "NO" << '\n';
      exit(0);
    }
  }
  
  auto best = -INF;
  auto src = -1;
  rep(source, 0, n) {
    auto maxdist = -INF;
    rep(i, 0, n) maxx(maxdist, dist[source][i]);
    if (maxdist > best) {
      best = maxdist;
      src = source;
    }
  }
 
  vi res(n);
  rep(i, 0, n) res[i] = dist[src][i];
  
  cout << "YES" << '\n';
  cout << best << '\n';
  trav(i, res) cout << i << " "; cout << '\n';
}
