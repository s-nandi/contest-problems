// dfs (subtree aggregate), bipartite, greedy (swap nodes s.t. a-b and c-d pairs have minimal intersections)
// https://www.codechef.com/COOK121A/problems/RBTREES

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = array<int, 2>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;

void bipartite(const graph& g, int i, auto& color, int p = -1, int col = 0) {
  color[i] = col;
  trav(e, g[i]) if (e.to != p)
    bipartite(g, e.to, color, i, 1 - col);
}

pii dfs(const graph& g, int i, const vi& s, const vi& color, ll& acc, int p = -1) {
  pii cnt{};
  if (color[i] != s[i]) cnt[color[i]] = 1;
  trav(e, g[i]) if (e.to != p) {
    auto got = dfs(g, e.to, s, color, acc, i);
    rep(t, 0, 2) cnt[t] += got[t];
  }
  auto pairs = min(cnt[0], cnt[1]);
  cnt[0] -= pairs;
  cnt[1] -= pairs;
  acc += cnt[0] + cnt[1]; // all unpaired nodes gain 1 distance as you go up tree
                          // could also explicitly track distance w/ venice sets
  return cnt;
}

int solve(const graph& g, const vi& s, const vi& color) {
  ll res = 0;
  auto rem = dfs(g, 0, s, color, res);
  if (any_of(all(rem), [](int r){return r > 0;})) return INF;
  else return res;
}

int main() {
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
    vi s(n);
    rep(i, 0, n) {
      char c;
      cin >> c;
      s[i] = c - '0';
    }
    vi color(n, -1);
    bipartite(g, 0, color);
    auto best1 = solve(g, s, color);
    trav(i, s) i = 1 - i;
    auto best2 = solve(g, s, color);
    auto best = min(best1, best2);
    cout << (best == INF ? -1 : best) << '\n';
  }
}
