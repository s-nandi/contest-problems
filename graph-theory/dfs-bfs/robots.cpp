// multisource dfs (on reverse graph), implicit state graph, pairwise check is sufficient & necessary
// https://open.kattis.com/problems/robots
// 2015 Greater NY Regional

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
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

void dfs(const auto& g, int i, auto& vis) {
  if (vis[i]) return;
  vis[i] = true;
  trav(e, g[i]) if (!vis[e.to])
    dfs(g, e.to, vis);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int T;
  cin >> T;
  while(T--) {
    int tc, n;
    cin >> tc >> n;
    vi r(n), g(n);
    trav(i, r) cin >> i;
    trav(i, g) cin >> i;

    auto indexof = [&](int i, int j) {
                     return i * n + j;
                   };
    auto transition = [&](int t, int i) {
                        switch(t) {
                        case 0:
                          return g[i];
                        case 1:
                          return r[i];
                        default:
                          assert(false);
                        }
                      };

    int nn = n * n;
    graph gr(nn);
    rep(i, 0, n) rep(j, 0, n) {
      auto from = indexof(i, j);
      rep(t, 0, 2) {
        auto ni = transition(t, i);
        auto nj = transition(t, j);
        auto to = indexof(ni, nj);
        gr[to].PB({from});
      }
    }
    ;
    vi vis(nn);
    rep(i, 0, n)
      dfs(gr, indexof(i, i), vis);

    auto feas = true;
    rep(i, 0, n) rep(j, 0, n)
      feas &= vis[indexof(i, j)];

    cout << tc << " ";
    cout << (feas ? "YES" : "NO") << '\n';
  }
}
