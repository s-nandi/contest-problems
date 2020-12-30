// greedy, each vertex's contribution is the # of colors it is adjacent to, always optimal to keep a subgraph of color x connected -- change color of 1 edge at a time
// https://codeforces.com/contest/1466/problem/D

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;
    graph g(n);
    rep(i, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }

    priority_queue<int> pq;
    ll base = 0LL;
    trav(i, a) base += i;
    
    rep(i, 0, n) {
      auto deg = sz(g[i]);
      rep(it, 0, deg - 1) {
        pq.push(a[i]);
      }
    }

    vector<ll> res(n - 1);
    res[0] = base;
    rep(i, 1, n - 1) {
      auto delta = pq.top(); pq.pop();
      base += delta;
      res[i] = base;
    }
    trav(i, res) cout << i << " "; cout << '\n';
  }
}
