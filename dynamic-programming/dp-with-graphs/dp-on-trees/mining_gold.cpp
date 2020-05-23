// dp on trees (postorder)
// https://codesprintla20-team.kattis.com/problems/codesprintla20.mininggold

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

struct edge{int to; ll w;};
using graph = vector<vector<edge>>;

const int MAXN = 2 * 100000;
ll sol[MAXN + 1];
const ll INF = 1e18;
void dfs(graph& g, int i, int p) {
  ll min_child = INF;
  trav(e, g[i]) if (e.to != p) {
    dfs(g, e.to, i);
    min_child = min(min_child, e.w + min(0LL, sol[e.to]));
  }
  sol[i] = min_child == INF ? 0 : min_child;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    g[u].PB({v, w});
    g[v].PB({u, w});
  }
  dfs(g, 0, -1);
  rep(i, 0, q) {
    int u;
    cin >> u;
    cout << sol[--u] << '\n';
  }
}
