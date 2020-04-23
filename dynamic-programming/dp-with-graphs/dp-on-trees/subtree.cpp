// dp on trees (reroot), # of ways to color tree s.t. B nodes are connected given starting B node queries
// https://atcoder.jp/contests/dp/tasks/dp_v

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int MOD;
const int MAXN = 100000;
ll dp[MAXN + 5]; // dp[i] = # of ways to color i's subtree black
ll res[MAXN + 5];

auto mult(auto a, auto b){return (a * b) % MOD;}

void dfs(graph &g, int i, int p = -1) {
  dp[i] = 1;
  trav(e, g[i]) if (e.to != p) {
    dfs(g, e.to, i);
    dp[i] = mult(dp[i], 1 + dp[e.to]);
  }
}

void calc(graph& g, int i, ll above = 1, int p = -1) {
  res[i] = mult(dp[i], above);
  vector<ll> pref, suff;
  rep(k, 0, sz(g[i])) {
    int to = g[i][k].to;
    if (to == p) continue;
    auto contrib = (1 + dp[to]) % MOD;
    pref.PB(!pref.empty() ? mult(pref.back(), contrib) : contrib);
  }
  for (auto k = sz(g[i]) - 1; k >= 0; k--){
    int to = g[i][k].to;
    if (to == p) continue;
    auto contrib = (1 + dp[to]) % MOD;
    suff.PB(!suff.empty() ? mult(suff.back(), contrib) : contrib);
  }
  reverse(all(suff));
  rep(k, 0, sz(g[i])) {
    int to = g[i][k].to;
    if (to == p) continue;
    auto before = k - 1 >= 0 ? pref[k - 1] : 1LL;
    auto after = k + 1 < sz(suff) ? suff[k + 1] : 1LL;
    auto exclude_this_subtree = mult(before, after);
    auto nabove = 1 + mult(above, exclude_this_subtree);
    calc(g, e.to, nabove, i);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n >> MOD;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  dfs(g, 0);
  calc(g, 0);
  rep(i, 0, n) cout << res[i] << '\n';
}
