// dsu on trees, finding min edge from node to any other node in given query subsets
// https://codeforces.com/group/ZFgXbZSjvp/contest/273473/problem/C
// 2020 NAPC -1

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int INF = 1231231234;
const int MOD = 998244353;
 
void minn(auto& a, auto b) {a = min(a, b);}
map<ii, int> mins; // node, query : value
struct DSU {
  vi par, ranks;
  vector<map<int, vi>> byquery; // [dsu par] => query : node
 
  DSU(int n) : par(n), ranks(n), byquery(n) {
    iota(all(par), 0);
  }
  void add_query(int u, int q) {byquery[u][q].PB(u);}
  int find(int i){return (par[i] == i) ? i : (par[i] = find(par[i]));}
  void merge(int i, int j, int cost) {
    int pi = find(i);
    int pj = find(j);
    if (ranks[pi] < ranks[pj]) swap(pi, pj);
    if (ranks[pi] == ranks[pj]) ranks[pi]++;
    par[pj] = pi;
    for(auto& [query, nodes_j]: byquery[pj]) {
      bool overlap = byquery[pi].count(query);
      auto& nodes_i = byquery[pi][query];
      if (overlap) {
        trav(matched, nodes_i) {
          assert(mins.count({matched, query}));
          minn(mins[{matched, query}], cost);
        }
        trav(matched, nodes_j) {
          assert(mins.count({matched, query}));
          minn(mins[{matched, query}], cost);
        }
        nodes_i.clear();
        nodes_i.shrink_to_fit();
        
        nodes_j.clear();
        nodes_j.shrink_to_fit();
      } else {
        trav(unmatched, nodes_j) {
          nodes_i.PB(unmatched);
        }
        nodes_j.clear();
        nodes_j.shrink_to_fit();
      }
    }
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vector<ii> edges(n - 1);
  for (auto& [u, v]: edges) {
    cin >> u >> v;
    --u; --v;
  }
  int q;
  cin >> q;
  DSU dsu(n);
  vector<vi> queries(q);
  rep(i, 0, q) {
    int k;
    cin >> k;
    queries[i].resize(k);
    rep(j, 0, k) {
      int u;
      cin >> u;
      --u;
      queries[i][j] = u;
      dsu.add_query(u, i);
      mins[{u, i}] = n;
    }
  }
  rep(i, 0, n - 1) {
    auto [u, v] = edges[i];
    dsu.merge(u, v, i + 1);
  }
  rep(i, 0, q) {
    auto res = 1LL;
    trav(u, queries[i]) {
      res *= mins[{u, i}];
      res %= MOD;
    }
    cout << res << '\n';
  }
}
