// tree dp (n^2 partition trick), greedy (don't need vote differential in state)
// https://codeforces.com/contest/1280/problem/D

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,ll>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int INF = 1031231234;
const ll LINF = 1e18;
constexpr pii def = pii{-INF, -LINF};

auto maxx(auto& a, auto b){a = max(a, b);}

pii combine(const pii& above, const pii& below) {
  const auto& [a1, b1] = above;
  const auto& [a2, b2] = below;
  return {a1 + a2 + (b2 > 0), b1};
}

pii merge(const pii& above, const pii& below) {
  const auto& [a1, b1] = above;
  const auto& [a2, b2] = below;
  return {a1 + a2, b1 + b2};
}

int dfs_size(const auto& g, int i, auto& sizes, int p = -1) {
  sizes[i] = 1;
  trav(e, g[i]) if (e.to != p)
    sizes[i] += dfs_size(g, e.to, sizes, i);
  return sizes[i];
}

void dfs(const auto& g, int i, const auto& diff, auto& dp, auto& sizes, auto& buffer, int p = -1) {
  dp[i][1] = {0, diff[i]};
  trav(e, g[i]) if (e.to != p) {
    dfs(g, e.to, diff, dp, sizes, buffer, i);
    fill(begin(buffer), begin(buffer) + sizes[i] + 1, def);
    for (int k1 = sizes[i] - sizes[e.to]; k1 >= 1; k1--) {
      for (int k2 = sizes[e.to]; k2 >= 1; k2--) {
        maxx(buffer[k1 + k2], combine(dp[i][k1], dp[e.to][k2]));
        maxx(buffer[k1 + k2 - 1], merge(dp[i][k1], dp[e.to][k2]));   
      }
    }
    copy(begin(buffer), begin(buffer) + sizes[i] + 1, begin(dp[i]));
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vi diff(n);
    rep(i, 0, n) {
      int v;
      cin >> v;
      diff[i] -= v;
    }
    rep(i, 0, n) {
      int v;
      cin >> v;
      diff[i] += v;
    }
      
    graph g(n);
    rep(it, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }

    vi sizes(n);
    dfs_size(g, 0, sizes);

    auto dp = vector(n, vector<pii>{});
    rep(i, 0, n) dp[i].resize(sizes[i] + 1);
    vector<pii> buffer(n + 1);
    dfs(g, 0, diff, dp, sizes, buffer);
    
    auto [best, extra] = combine({0, 0}, dp[0][m]);
    cout << best << '\n';
  }
}
