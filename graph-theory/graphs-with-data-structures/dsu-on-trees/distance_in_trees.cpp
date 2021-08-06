// small to large, venice trick (offset all values by 1)
// https://codeforces.com/contest/161/problem/D

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
constexpr auto check = false;
constexpr auto custom = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

template <typename T>
struct Venice : public deque<T> {
  using deque<T>::deque;
  void shift() {this -> push_front(0);}
};

Venice<ll> dfs(int target, const auto& g, int i, auto& res, int p = -1) {
  Venice<ll> dp(1, 1);
  trav(e, g[i]) if (e.to != p) {
    auto got = dfs(target, g, e.to, res, i);
    got.shift();
    if (sz(dp) < sz(got)) swap(dp, got);
    rep(k, 0, sz(got)) {
      if (0 <= target - k and target - k < sz(dp))
        res[i] += got[k] * dp[target - k];
    }
    rep(k, 0, sz(got)) {
      dp.at(k) += got[k];
    }
  }
  return dp;
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int n, k;
  cin >> n >> k;
  graph g(n);
  rep(it, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  auto res = vector<ll>(n);
  dfs(k, g, 0, res);
  cout << accumulate(all(res), 0LL) << '\n';
}
