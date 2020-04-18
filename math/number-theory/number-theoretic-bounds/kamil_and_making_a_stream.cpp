// maximum number of gcd changes is log(MAX), dfs
// https://codeforces.com/contest/1229/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MOD = 1'000'000'007;

ll dfs(auto& g, auto& a, int i, const map<ll, int>& freq, int p = -1) {
  auto acc = 0LL;
  map<ll, int> freq2;
  for (auto& [elem, cnt]: freq) {
    auto gc = gcd(elem, a[i]);
    freq2[gc] += cnt;
    acc += gc * cnt % MOD;
    acc %= MOD;
  }
  freq2[a[i]]++;
  acc += a[i];
  acc %= MOD;
  trav(e, g[i])
    if (e.to != p)
      acc = (acc + dfs(g, a, e.to, freq2, i)) % MOD;
  return acc;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  auto res = dfs(g, a, 0, {});
  cout << res << '\n';
}
