// heavy-light amortized analysis (summing deg(v)^2 for all light vertices v of each edge is m * sqrt(m)), count # of triangles in graph
// https://open.kattis.com/problems/gottacatchemall
// 2018 Vietnam ICPC National Programming Contest

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

using edge = int;
using graph = vector<vector<edge>>;

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

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
  rep(i, 0, n) {
    sort(all(g[i]));
    g[i].erase(unique(all(g[i])), end(g[i])); // trim duplicate edges
  }

  auto before = [&](int i, int j) {
                  return sz(g[i]) != sz(g[j]) ? sz(g[i]) < sz(g[j]) : i < j;
                };
  
  ll base = 0;
  rep(i, 0, n) {
    auto deg = sz(g[i]);
    base += ((ll) deg * (deg - 1)); // count all 2 paths, triangles are overcounted
                                    // since the 2-paths are actually 1-paths
  }

  ll triangles = 0;
  vi adjacent(n);
  vector<vi> candidate(n);
  rep(a, 0, n) {
    trav(b, g[a]) adjacent[b] = true;
    trav(b, g[a]) {
      if (before(a, b)) continue; // A is heavy, B is light
      trav(c, g[b]) { // have A-B and B-C, need to check A-C
        if (adjacent[c]) triangles += 2; // each triangle is overcounted by 3, 1 for each edge,
                                         // but we need to overcount by 6
      }
    }
    trav(b, g[a]) adjacent[b] = false;
  }  
  auto res = base - triangles;
  cout << res << '\n';
}
