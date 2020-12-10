// dp on trees, greedy
// https://codeforces.com/contest/1453/problem/E
// Note: There is a conceptually simpler solution based on binary searching on the answer: https://codeforces.com/blog/entry/85288?#comment-729601,
//       my first AC submission was based on this idea

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

const int INF = 1031231234;

/*
 * Returns the distance from the last-visited leaf node in i's subtree to i's parent if i is not the root
 *         otherwise, returns the same distance to i if i is the root
 */
int solve(auto& g, int i, int& k, int p = -1) {
  vi dists;
  trav(e, g[i]) if (e.to != p) {
    auto dist = solve(g, e.to, k, i);
    dists.PB(dist);
  }
  if (empty(dists)) dists.PB(0); // leaf node; could return 1 instead

  int mx = -INF, mx2 = -INF, mn = INF;
  trav(d, dists) {
    if (d > mx) mx2 = mx, mx = d;
    else if (d > mx2) mx2 = d;
    if (d < mn) mn = d;
  }
  if (i == 0) k = max({k, mx, mx2 + 1}); // every d in dist EXCEPT for the max gets incremented
                                         // since we can visit the deepest leaf node last and avoid +1'ing it
  else k = max(k, mx + 1); // every d in dist gets incremented by 1; we either need to go from a leaf to another leaf (+1) or to i's parent (+1)
  return mn + 1; // the shallowest leaf is the best leaf to visit last since everything else can be thrown away
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    graph g(n);
    rep(it, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }
    int k{0};
    solve(g, 0, k);
    cout << k << '\n';
  }
}
