// greedy (if a >= b and c >= d, then a * (c + d) + b >= a * c + b * d => optimal to reduce highest primes), subtree sum (finding # of paths through edge)
// https://codeforces.com/contest/1401/problem/D

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
 
const int MOD = 1000000007;
int add(ll a, ll b){return (a + b) % MOD;}
int mult(ll a, ll b){return a * b % MOD;}
 
int dfs(graph& g, int i, int p, auto& weight) {
  int s = 1;
  trav(e, g[i]) if (e.to != p) {
    int below = dfs(g, e.to, i, weight);
    int above = sz(g) - below;
    auto w = (ll) below * above;
    weight.PB(w);
    s += below;
  }
  return s;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
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
    int m;
    cin >> m;
    vi p(m);
    trav(i, p) cin >> i;
    while (sz(p) < n - 1) {
      p.PB(1);
    }
    m = sz(p);
    
    sort(all(p));
    while (sz(p) > n - 1 and sz(p) >= 2) {
      auto p1 = p.back();
      p.pop_back();
      auto p2 = p.back();
      p.pop_back();
      p.push_back(mult(p1, p2));
    }
    assert(sz(p) == n - 1);
 
    vector<ll> weight;
    auto tot = dfs(g, 0, 0, weight);
    assert(tot == n);
    assert(sz(weight) == n - 1);
 
    sort(all(weight));
    trav(w, weight) w %= MOD;
 
    ll res = 0;
    rep(i, 0, n - 1) {
      res = add(res, mult(weight[i], p[i]));
    }
    cout << res << '\n';
  }
}
