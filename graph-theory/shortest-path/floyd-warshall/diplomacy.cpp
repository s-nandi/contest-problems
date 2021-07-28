// floyd warshall (0/1 edges), optimal strategy is to flip the same node repeatedly (why?) -- each flip merges with nodes 1 distance further
// https://open.kattis.com/problems/diplomacy
// 2014 NAIPC

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
auto minn(auto& a, auto b){a = min(a, b);}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;;
  vi a(n);
  trav(i, a) cin >> i;
  auto mat = vector(n, vi(n, INF));
  rep(i, 0, n) mat[i][i] = 0;
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    mat[u][v] = mat[v][u] = a[u] != a[v];
  }
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    minn(mat[i][j], mat[i][k] + mat[k][j]);

  int best = INF;
  rep(i, 0, n) {
    int worst = 0;
    rep(j, 0, n) {
      worst = max(worst, mat[i][j]);
    }
    minn(best, worst);
  }
  cout << best << '\n';
}
