// tree dp
// https://atcoder.jp/contests/dp/tasks/dp_p

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MOD = 1000000007;
const int MAXN = 100000;
int dp[MAXN][2]; // node, node can be black

void dfs(graph& g, int i, int p = -1) {
  ll ifwhite = 1LL;
  ll ifblack = 1LL;
  trav(e, g[i]) if (e.to != p)
    dfs(g, e.to, i);

  trav(e, g[i]) if (e.to != p) {
    ifwhite = (1LL * ifwhite * dp[e.to][1]) % MOD;
    ifblack = (1LL * ifblack * dp[e.to][0]) % MOD;
  }
  dp[i][0] = ifwhite;
  dp[i][1] = (ifwhite + ifblack) % MOD;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  dfs(g, 0);
  cout << dp[0][1] << '\n';
}
