// tree center, nested dfs, each node is hit once for each node above it => O(tree height * n) operations
// https://codesprintla21open-team.kattis.com/problems/codesprintla21.orangestonenetwork

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
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to; bool on;};
using graph = vector<vector<edge>>;

vi findCenters(const graph& g) {
  int n = sz(g), removed = 0;
  vi degree(n), leaves;
  rep(i, 0, n) {
    degree[i] = g[i].size();
    if (degree[i] <= 1)
      leaves.push_back(i), removed++;
  }
  while (removed < n) {
    vi temp;
    trav(leaf, leaves) trav(e, g[leaf])
      if (--degree[e.to] == 1)
        temp.push_back(e.to), removed++;
    leaves = temp;
  }
  return leaves;
}

vi ops;
void toggle(auto& g, int i, bool& pon, int p = -1) {
  trav(e, g[i]) if (e.to != p) {
    if (e.on != pon) toggle(g, e.to, e.on, i);
  }
  ops.PB(i);
  pon ^= true;
  trav(e, g[i]) if (e.to != p) {
    e.on ^= true;
  }
}

void dfs(auto& g, int i, int p = -1) {
  trav(e, g[i]) if (e.to != p) {
    if (!e.on) toggle(g, e.to, e.on, i);
  }
  trav(e, g[i]) if (e.to != p) {
    dfs(g, e.to, i);
  }
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  graph g(n);
  rep(it, 0, n - 1) {
    int i, j; bool on;
    cin >> i >> j >> on;
    --i; --j;
    g[i].PB({j, on});
    g[j].PB({i, on});
  }
  auto root = findCenters(g)[0];
  dfs(g, root);

  cout << sz(ops) << '\n';
  trav(i, ops) cout << (i + 1) << '\n';  
}
