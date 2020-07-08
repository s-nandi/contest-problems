// amortized analysis, dsu, mst (inspiration from kruskal)
// https://codeforces.com/contest/1243/problem/D
// Note: comments under editorial describe 2-3 different solutions (heavy-light/pigeonhole ideas)

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

struct DSU {
  vi par;
  DSU(int n) : par(n, -1) {}
  int find(int i){return par[i] < 0 ? i : (par[i] = find(par[i]));}
  int size(int i){return -par[find(i)];}
  bool join(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return false;
    par[i] += par[j];
    par[j] = i;
    return true;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    adj[u].PB(v);
    adj[v].PB(u);
  }
  DSU dsu(n);
  set<int> roots;
  rep(i, 0, n) roots.insert(i);
  rep(i, 0, n) {
    map<int, int> percomp;
    trav(e, adj[i]) percomp[dsu.find(e)]++;
    vi merged;
    trav(j, roots) if (j != dsu.find(i)) {
      if (percomp[j] < dsu.size(j))
        merged.PB(j);
    }
    trav(j, merged) {
      dsu.join(i, j);
      roots.erase(j);
    }
  }
  cout << sz(roots) - 1 << '\n';
}
