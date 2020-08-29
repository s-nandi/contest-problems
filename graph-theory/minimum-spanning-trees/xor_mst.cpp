// boruvka, binary trie (min xor query, increment/decrement count update), amoritized (each component is removed,queried,added once per boruvka iteration)
// https://codeforces.com/contest/888/problem/G
// Note: can also be solved with D&C, look at comments under editorial for examples

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
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int MAXB = 30;
const int MAXN = 200000;
const int INF = 1031231234;
using vertex_pair = tuple<int, int, int>; // weight, u, v
 
struct DSU {
  vi par;
  DSU(int n) : par(n, -1) {}
  int find(int i) {return par[i] < 0 ? i : (par[i] = find(par[i]));}
  bool join(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return false;
    if (par[i] > par[j]) swap(i, j);
    par[i] += par[j];
    par[j] = i;
    return true;
  }
};
 
template <int width>
struct trie {
  struct node {
    array<int, 2> to{-1, -1};
    array<int, 2> cnt{};
    int id{-1};
  };
  
  vector<node> v{};
  trie() {
    v.reserve(MAXB * MAXN);
    make();
  }
  int make() {
    v.emplace_back();
    return sz(v) - 1;
  }
  void add(int val, int id) {
    int curr = 0;
    for (int i = width - 1; i >= 0; i--) {
      auto bit = !!(val & (1 << i));
      if (v[curr].to[bit] == -1) {
        int ind = make();
        v[curr].to[bit] = ind;
      }
      v[curr].cnt[bit]++;
      curr = v[curr].to[bit];
    }
    v[curr].id = id;
  }
  void inc(int val, int w) { // assumes val is contained
    int curr = 0;
    for (int i = width - 1; i >= 0; i--) {
      auto bit = !!(val & (1 << i));
      v[curr].cnt[bit] += w;
      curr = v[curr].to[bit];
    }
  }
  auto min_xor(int val) const {
    int curr = 0;
    int res = 0;
    for (int i = width - 1; i >= 0; i--) {
      auto have = !!(val & (1 << i));
      for (auto bit: {have, !have}) {
        if (v[curr].cnt[bit]) {
          res += (1 << i) * (have ^ bit);
          curr = v[curr].to[bit];
          break;
        }
      }
    }
    return pair{res, v[curr].id};
  }
};
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  sort(all(a)); // cache-locality magic? 2x+ speed-up
 
  vi compressed(n);
  rep(i, 0, n) compressed[i] = lower_bound(all(a), a[i]) - begin(a); // avoid repeated bin searches
 
  trie<MAXB> tr{};
  rep(i, 0, n) tr.add(a[i], i);
  
  ll res = 0;
  DSU dsu(n);
  vector<pii> byvalue(n); // byvalue[val] = (min comp, max comp) with element ind s.t. a[ind] = val
                          //                used to store two distinct components per value; allows us
                          //                to find a candidate neighbor component distinct from our current component
  vector<vi> components(n);
  while (true) {
    bool done = false;
    rep(i, 0, n) {
      byvalue[i] = {INF, -INF};
      components[i].clear();
    }
    rep(i, 0, n) {
      components[dsu.find(i)].PB(i);
      byvalue[compressed[i]].first = min(byvalue[compressed[i]].first, dsu.find(i));
      byvalue[compressed[i]].second = max(byvalue[compressed[i]].second, dsu.find(i));
      if (sz(components[dsu.find(i)]) == n) done = true;
    }
    if (done) break;
 
    rep(i, 0, n)  {
      const auto& comp = components[i];
      if (empty(comp)) continue;
      
      trav(ind, comp) tr.inc(a[ind], -1);
 
      vertex_pair best = {INF, -1, -1};
      trav(ind, comp) {
        auto [contrib, ind_other] = tr.min_xor(a[ind]);
        const auto& candidates = byvalue[compressed[ind_other]];
        auto candidate = candidates.first != i ? candidates.first : candidates.second;
        best = min(best, vertex_pair{contrib, ind, candidate});
      }
      const auto& [w, u, v] = best;
      if (dsu.join(u, v)) res += w;
        
      trav(ind, comp) tr.inc(a[ind], 1);
    }
  }
  cout << res << '\n';
}
