// dp on tree (max distance from each node to some other node, reroot), game theory (dominating node on tree, bob must be able to skip over alice == db > 2da), dfs (distance, subtree aggregate)
// https://codeforces.com/contest/1404/problem/B
// Note: Can also solve using the diameter (2da >= diameter => alice win)

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
int dfs_distance(graph& g, int i, int dest, int p = -1) {
  if (i == dest) return 0;
  int best = INF;
  trav(e, g[i]) if (e.to != p)
    best = min(best, dfs_distance(g, e.to, dest, i) + 1);
  return best;
}

int dfs_depth(graph& g, int i, auto& mx, auto& mx2, int p = -1) {
  trav(e, g[i]) if (e.to != p) {
    auto dist_to_leaf = dfs_depth(g, e.to, mx, mx2, i) + 1;
    if (dist_to_leaf > mx[i]) tie(mx2[i], mx[i]) = tuple{mx[i], dist_to_leaf};
    else if (dist_to_leaf > mx2[i]) mx2[i] = dist_to_leaf;
  }
  return mx[i]; // dist to furthest leaf in subtree
}

void dfs_furthest(graph& g, int i, auto& mx, auto& mx2, auto& furthest, int p = -1, int above = 0) {
  furthest[i] = max(mx[i], above);
  trav(e, g[i]) if (e.to != p) {
    int other_branch = mx[e.to] + 1 == mx[i] ? mx2[i] : mx[i];
    dfs_furthest(g, e.to, mx, mx2, furthest, i, max(other_branch, above) + 1);
  }
}

bool dfs_escape(const graph& g, int i, int blocked, int da, auto& furthest, int p = -1) {
  if (furthest[i] > 2 * da) return true;
  trav(e, g[i]) if (e.to != p and e.to != blocked) {
    if(dfs_escape(g, e.to, blocked, da, furthest, i)) return true;
  }
  return false;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n, a, b, da, db;
    cin >> n >> a >> b >> da >> db;
    --a; --b;
    graph g(n);
    rep(it, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }
    auto initial_dist = dfs_distance(g, a, b);
    if (initial_dist <= da or db <= 2 * da) {
      cout << "Alice" << '\n';
    } else {
      vi mxdepth(n), mxdepth2(n);
      dfs_depth(g, 0, mxdepth, mxdepth2);
      vi furthest(n);
      dfs_furthest(g, 0, mxdepth, mxdepth2, furthest);
      bool canescape = dfs_escape(g, a, b, da, furthest);
      cout << (canescape ? "Bob" : "Alice") << '\n';
    }
  }
}
