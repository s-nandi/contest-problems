// graph (functional graph), backtracking, graph with n edges can be decomposed into cycles iff each node has exactly 1 indegree and 1 outdegree => check that no 2 chosen edges go into same node
// https://codeforces.com/contest/1394/problem/B
// Note: editorial solution uses hashing to check for conflicting edges instead

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to, w;};
using graph = vector<vector<edge>>;

auto getindex(const pii& i_deg, int k) {
  return i_deg.second * (k + 1) + i_deg.first;
}

int backtrack(int deg, int k, auto& used, const auto& conflict) {
  assert(sz(used) < deg);
  if (deg > k) return 1;
  auto ways = 0;
  rep(i, 0, deg) {
    auto ind = getindex({i, deg}, k);
    if (conflict[ind][ind]) continue;
    if (!all_of(all(used), [&](int j){return !conflict[ind][j];})) continue; // could do the opposite, and blacklist conflicting tuples when a (i, deg) tuple is chosen
                                                                             // this would get O(1) conflict checks, and the added/removed tuples would amortize out to O(k * m)? operations
    used.PB(ind);
    ways += backtrack(deg + 1, k, used, conflict);
    used.pop_back();
  }
  return ways;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;
  graph g(n);
  rep(it, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    g[u].PB({v, w});
  }
  vector<vector<pii>> t(n); // coordinate compressed transpose
  rep(i, 0, n) {
    sort(all(g[i]), [](const auto& e1, const auto& e2){return e1.w < e2.w;});
    auto deg = sz(g[i]);
    rep(d, 0, deg) {
      auto e = g[i][d];
      t[e.to].PB({d, deg});
    }
  }
  auto nn = (k + 1) * (k + 1);
  auto conflict = vector(nn, vi(nn));
  rep(i, 0, n) {
    sort(all(t[i]));
    rep(it, 0, sz(t[i]) - 1) { // take care of case where multiple of the same (i, deg) tuple goes into the same node =>
                               // this tuple cannot be used in solution
      if (t[i][it] == t[i][it + 1]) {
        auto ind = getindex(t[i][it], k);
        conflict[ind][ind] = true;
      }
    }
    t[i].erase(unique(all(t[i])), end(t[i])); // If duplicates aren't trimmed, next two loops incur O(n^2) cost instead of O(nn^2) == O(k^4)
    rep(it1, 0, sz(t[i])) {
      auto ind = getindex(t[i][it1], k);
      rep(it2, it1 + 1, sz(t[i])) {
        auto ind2 = getindex(t[i][it2], k);
        conflict[ind][ind2] = conflict[ind2][ind] = true;
      }
    }
  }
  vi used;
  auto sol = backtrack(1, k, used, conflict);
  cout << sol << '\n';
}
