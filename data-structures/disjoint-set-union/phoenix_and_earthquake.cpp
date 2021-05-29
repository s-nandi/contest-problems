// augmented DSU (smaller to bigger merging of neighbors), amortized analysis, pigeonhole principle (node w/ max asphalt can always merge with some neighbor)
// https://codeforces.com/problemset/problem/1515/F

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

struct UF {
  vi e;
  graph g;
  UF(int n) : e(n, -1), g(n) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    
    trav(e, g[b]) {
      g[a].PB(e);
    }
    g[b].clear();
    g[b].shrink_to_fit();
    
    return true;
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m, x;
  cin >> n >> m >> x;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  vector<pii> edges(m);
  trav(i, edges) {cin >> i[0] >> i[1]; --i[0]; --i[1];}

  auto tot = accumulate(all(a), 0LL);
  auto req = (ll) x * (n - 1);
  if (tot < req) cout << "NO" << '\n';
  else {
    UF dsu(n);
    rep(i, 0, m) {
      const auto& [u, v] = edges[i];
      dsu.g[u].PB({v, i});
      dsu.g[v].PB({u, i});
    }

    vi res(n - 1);
    set<pair<ll, int>, greater<>> pq;
    rep(i, 0, n) {
      pq.insert({a[i], i});
    }
    
    rep(it, 0, n - 1) {
      auto [w, i] = *begin(pq); pq.erase(begin(pq));
      while (dsu.sameSet(dsu.g[i].back().to, i)) dsu.g[i].pop_back();
      
      auto [j, id] = dsu.g[i].back();
      j = dsu.find(j);
      
      res[it] = id;
      dsu.join(i, j);

      auto root = dsu.find(i);
      pq.erase({a[i], i});
      pq.erase({a[j], j});
      a[root] = a[i] + a[j] - x;
      pq.insert({a[root], root});
    }
    cout << "YES" << '\n';
    trav(i, res) cout << (i + 1) << '\n';
  }
}
