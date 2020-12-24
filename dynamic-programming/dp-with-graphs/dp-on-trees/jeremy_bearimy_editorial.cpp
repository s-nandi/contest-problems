// dp on trees, proofy (exchange argument to prove lower/upper bound, then show we can achieve it)
// https://codeforces.com/contest/1281/problem/E
// Note: There is a constructive solution that is already in the repo which is longer to implement

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

struct edge{int to, w;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

void dfs(cauto& g, int i, auto& sizes, int p = -1) {
  sizes[i] = 1;
  trav(e, g[i]) if (e.to != p) {
    dfs(g, e.to, sizes, i);
    sizes[i] += sizes[e.to];
  }
}

ll maximize(cauto& g, int i, cauto& sizes, int p = -1) {
  ll acc = 0;
  trav(e, g[i]) if (e.to != p) {
    cauto above = sz(g) - sizes[e.to];
    cauto below = sizes[e.to];
    acc += (ll) min(above, below) * e.w;
    acc += maximize(g, e.to, sizes, i);
  }
  return acc;
}

ll minimize(cauto& g, int i, cauto& sizes, int p = -1) {
  ll acc = 0;
  trav(e, g[i]) if (e.to != p) {
    cauto above = sz(g) - sizes[e.to];
    cauto below = sizes[e.to];
    assert((above % 2) == (below % 2)); // since above + below == 2k
    acc += (ll) (above % 2) * e.w;
    acc += minimize(g, e.to, sizes, i);
  }
  return acc;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int k;
    cin >> k;
    auto n = 2 * k;
    graph g(n);
    rep(i, 0, n - 1) {
      int u, v, w;
      cin >> u >> v >> w;
      --u, --v;
      g[u].PB({v, w});
      g[v].PB({u, w});
    }
    vi sizes(n);
    dfs(g, 0, sizes);
    auto res1 = minimize(g, 0, sizes);
    auto res2 = maximize(g, 0, sizes);
    cout << res1 << " " << res2 << '\n';
  }
}
