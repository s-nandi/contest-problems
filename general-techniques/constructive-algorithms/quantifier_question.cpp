// constructive (proofy), dp on DAG / toposort, greedily only use E's when necessary
// https://codeforces.com/contest/1344/problem/C

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>; 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
auto minn(auto& a, auto b){a = min(a, b);}
 
auto min_reachable(const graph& g) {
  int n = sz(g);
  vi ideg(n);
  rep(i, 0, n) trav(e, g[i])
    ideg[e.to]++;
  queue<int> q;
  vi minreach(n);
  iota(all(minreach), 0);
  rep(i, 0, n) if (ideg[i] == 0) {
    q.push(i);
    minreach[i] = i;
  }
  int vis = 0;
  for(; !q.empty(); vis++, q.pop()) {
    int i = q.front();
    trav(e, g[i]) {
      minn(minreach[e.to], minreach[i]);
      if (--ideg[e.to] == 0)
        q.push(e.to);
    }
  }
  return pair{vis == n, minreach};
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, m;
  cin >> n >> m;
  graph g(n), t(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    t[v].PB({u});
  }
  auto [no_cycle, fwd] = min_reachable(g);
  auto [__, bck] = min_reachable(t);
  if (no_cycle) {
    int na = n;
    string quantifier(n, 'A');
    rep(i, 0, n) {
      if (fwd[i] < i or bck[i] < i) {
        quantifier[i] = 'E';
        na--;
      }
    }
    cout << na << '\n';
    cout << quantifier << '\n';
  } else cout << -1 << '\n';
}
