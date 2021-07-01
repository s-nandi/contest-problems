// toposort, find nodes that can reach or be reached by every other node
// https://codeforces.com/gym/103091/problem/L
// 2021 Stanford ProCo

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
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
auto solve(const auto& g) {
  int n = sz(g);
 
  vi indegree(n);
  rep(i, 0, n) trav(e, g[i]) indegree[e.to]++;
  queue<int> q;
  rep(i, 0, n) if (indegree[i] == 0) q.push(i);
  int rem = n;
  vi canreach(n);
  while (!empty(q)) {
    auto i = q.front(); q.pop();
    rem--;
    if (sz(q) == 0) canreach[i] = rem;
    trav(e, g[i]) {
      if (--indegree[e.to] == 0) {
        q.push(e.to);
      }
    }
  }
  return canreach;
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;
 
  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
  }
 
  graph t(n);
  rep(i, 0, n) trav(e, g[i]) t[e.to].PB({i});
  
  vi bad(n);
  auto canreach1 = solve(g);
  auto canreach2 = solve(t);
  rep(i, 0, n)
    bad[i] = canreach1[i] + canreach2[i] < n - 1;
 
  int res = n - accumulate(all(bad), 0);
  cout << res << '\n';
}
