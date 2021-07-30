// greedy dfs, sum a[i] is divisor of n - 1, incl-excl on gcd, if gcd>1, deg. of node determines if i or par deleted first so 0/1 way, gcd=1 => 2^(n - 1) ways by induction on edges
// https://codeforces.com/contest/1554/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
constexpr auto dbg = false;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int MOD = 998244353;
 
int pow2(int p) {
  int res = 1;
  rep(i, 0, p) res = (res * 2) % MOD;
  return res;
}

bool dfs(int target, const auto& g, int i, auto& dead, int p = -1) {
  int edges = (p != -1);
  trav(e, g[i]) if (e.to != p) {
    if (!dfs(target, g, e.to, dead, i)) return false;
    if (!dead[e.to]) edges++;
  }
  if (edges % target != 0 and (edges >= 1 and (edges - 1) % target != 0))
    return false;
  else {
    dead[i] = edges % target == 0;
    return true;
  }
}
 
int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
 
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

    vi dead(n);
    vi res(n + 1);
    res[1] = pow2(n - 1);
    rep(fac, 2, n + 1) if ((n - 1) % fac == 0)
      res[fac] = dfs(fac, g, 0, dead);
    
    for (int i = n; i >= 1; i--)
      for (int j = 2 * i; j <= n; j += i)
        res[i] -= res[j];
    rep(i, 1, n + 1) cout << res[i] << " "; cout << '\n';
  }
}
