// greedy dfs (max edge pairs s.t. paired edges share a node and no edge occurs in two pairs), implicit graph (between the two possible slopes for each point)
// https://codeforces.com/contest/1519/problem/E

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
 
struct edge{int to, id;};
using graph = vector<vector<edge>>;
 
void dfs(const auto& g, int i, auto& vis, auto& used, auto& sol, int pid = -1) {
  if (vis[i]) return;
  vis[i] = true;
  trav(e, g[i])
    dfs(g, e.to, vis, used, sol, e.id);
  
  vi oedges;
  trav(e, g[i]) if (e.id != pid and !used[e.id]) oedges.PB({e.id});
  if (sz(oedges) & 1 and pid != -1 and !used[pid]) oedges.PB(pid);
  
  for (int it = 1; it < sz(oedges); it += 2){
    auto id1 = oedges[it - 1];
    auto id2 = oedges[it];
    sol.PB({id1, id2});
    assert(!used[id1] and !used[id2]);
    used[id1] = used[id2] = true;
  }
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;
  vector<array<int, 4>> a(n);
  trav(pt, a) {
    trav(coord, pt) cin >> coord;
  }
  map<array<ll, 2>, int> indexer;
  auto indexof = [&](const array<ll, 2>& pt) {
                   if (!indexer.count(pt)) {
                     auto res = sz(indexer);
                     indexer[pt] = res;
                   }
                   return indexer[pt];
                 };
 
  vector<array<int, 3>> edge_list;
  rep(it, 0, n) {
    const auto& [x1, x2, y1, y2] = a[it];
    int ind1, ind2;
    {
      auto num = (ll) x2 * y1;
      auto denom = (ll) (x1 + x2) * y2;
      auto g = gcd(num, denom);
      num /= g;
      denom /= g;
      ind1 = indexof({num, denom});
    }
    {
      auto num = (ll) (y1 + y2) * x2;
      auto denom = (ll) y2 * x1;
      auto g = gcd(num, denom);
      num /= g;
      denom /= g;
      ind2 = indexof({num, denom});
    }
    edge_list.PB({ind1, ind2, it});
  }
  int nn = sz(indexer);
  graph g(nn);
  for (const auto& [u, v, id]: edge_list) {
    g[u].PB({v, id});
    g[v].PB({u, id});
  }
  vector<pii> sol;
  vi used(sz(a));
  vi vis(nn);
  rep(i, 0, nn) if (!vis[i]) {
    dfs(g, i, vis, used, sol);
  }
  cout << sz(sol) << '\n';
  for (const auto& [p1, p2]: sol) {
    cout << (p1 + 1) << " " << (p2 + 1) << '\n';
  }
}
