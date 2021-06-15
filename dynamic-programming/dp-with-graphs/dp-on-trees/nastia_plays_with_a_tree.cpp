// tree dp (min path cover, reconstruct solution)
// https://codeforces.com/problemset/problem/1521/D

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

using state = pair<int, pii>;
constexpr int INF = 1031231234;

auto minn(auto& a, auto b){return b < a ? a = b, true : false;}

void solve(const auto& g, int i, auto& dp, int p = -1) {
  auto bestfor = [&](int nd){return min(dp[nd][0].first, dp[nd][1].first);};
  auto extensionpenalty = [&](int nd){return max(0, dp[nd][1].first - dp[nd][0].first);};

  int switch1 = -1, switch2 = -1;
  int best_acc = 0;
  trav(e, g[i]) if (e.to != p) {
    solve(g, e.to, dp, i);
    best_acc += bestfor(e.to);
    auto penalty = extensionpenalty(e.to);
    if (switch1 == -1 or penalty <= extensionpenalty(switch1)) {
      switch2 = switch1;
      switch1 = e.to;
    } else if (switch2 == -1 or penalty <= extensionpenalty(switch2)) {
      switch2 = e.to;
    }
  }
  minn(dp[i][1], state{best_acc + 1, {-1, -1}}); // new path
  if (switch1 != -1) // extend 1
    minn(dp[i][1], state{best_acc + extensionpenalty(switch1), {switch1, -1}});
  if (switch1 != -1 and switch2 != -1) // extend 2
    minn(dp[i][0], state{best_acc + extensionpenalty(switch1) + extensionpenalty(switch2) - 1, {switch1, switch2}});
}

void reconstruct(const auto& g, int i, const auto& dp, auto& paths, int path_ind, int p = -1) {
  const auto& [cost, extensions] = min(dp[i][0], dp[i][1]);
  const auto& [extend1, extend2] = extensions;

  paths[path_ind].PB(i);
  if (extend1 != -1 and extend2 != -1) {
    reconstruct(g, extend1, dp, paths, path_ind, i);
    reverse(all(paths[path_ind]));
    reconstruct(g, extend2, dp, paths, path_ind, i);
  } else if (extend1 != -1) {
    reconstruct(g, extend1, dp, paths, path_ind, i);
  }
  trav(e, g[i]) if (e.to != p and e.to != extend1 and e.to != extend2)
    reconstruct(g, e.to, dp, paths, e.to, i);
}

int32_t main() {
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
    auto dp = vector(n, vector(2, state{INF, {-1, -1}})); // dp[i][can extend root] = {cost, {extend1, extend2}}
    solve(g, 0, dp);

    vector<vi> paths(n);
    reconstruct(g, 0, dp, paths, 0);
    paths.erase(begin(paths), partition(all(paths), [](const auto& vec){return empty(vec);}));

    vi bypath(n);
    rep(it, 0, sz(paths)) trav(i, paths[it]) bypath[i] = it;
    
    vector<pii> bad, good;
    rep(i, 0, n) trav(e, g[i]) if (i < e.to and bypath[i] != bypath[e.to])
      bad.PB({i, e.to});
    rep(it, 0, sz(paths) - 1)
      good.PB({paths[it].back(), paths[it + 1][0]});
    assert(sz(bad) == sz(good));
    
    int k = sz(bad);
    cout << k << '\n';
    rep(i, 0, k) {
      trav(c, bad[i]) cout << (c + 1) << " ";
      trav(c, good[i]) cout << (c + 1) << " ";
      cout << '\n';
    }
  }
}
