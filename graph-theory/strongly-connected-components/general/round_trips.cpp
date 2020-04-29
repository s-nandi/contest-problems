// scc, counting/combo
// https://open.kattis.com/problems/roundtrips
// 2020 Mount Allison Showdown (MAPS)

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

using graph = vector<vector<int>>;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
  int low = val[j] = ++Time, x; z.push_back(j);
  trav(e,g[j]) if (comp[e] < 0)
    low = min(low, val[e] ?: dfs(e,g,f));
  if (low == val[j]) {
    do {
      x = z.back(); z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    f(cont); cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
  int n = sz(g);
  val.assign(n, 0); comp.assign(n, -1);
  Time = ncomps = 0;
  rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].PB(v);
  }
  int prev_component_sizes = 0;
  auto can_add_intercomp = 0LL, already_added_intercomp = 0LL;
  scc(g, [&](const auto& v){
           can_add_intercomp += 1LL * sz(v) * prev_component_sizes;
           prev_component_sizes += sz(v);
           trav(i, v)
             trav(to, g[i])
               already_added_intercomp += comp[to] != comp[i];
         });
  cout << can_add_intercomp - already_added_intercomp << '\n';
}
