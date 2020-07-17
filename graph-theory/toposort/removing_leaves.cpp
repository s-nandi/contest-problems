// toposort, dynamic edge removal/addition, greedy (order of removing leaves doesn't matter)
// https://codeforces.com/contest/1385/problem/F

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

using graph = vector<set<int>>;

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    graph g(n), sg(n);
    rep(i, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].insert(v);
      g[v].insert(u);
    }
    if (k == 1) {cout << (n - 1) << '\n'; continue;}
    set<int> enough;
    rep(i, 0, n) {
      trav(to, g[i]) {
        if (sz(g[to]) == 1)
          sg[i].insert(to);
      }
      if (sz(sg[i]) >= k) enough.insert(i);
    }
    int ops = 0;
    while (!empty(enough)) {
      auto i = *begin(enough);
      ops++;
      vi removed;
      rep(it, 0, k) {
        int to = *begin(sg[i]);
        sg[i].erase(to);
        g[i].erase(to);
      }
      if (sz(sg[i]) < k) {
        enough.erase(i);
      }
      if (sz(g[i]) == 1) {
        auto par = *begin(g[i]);
        sg[par].insert(i);
        if (sz(sg[par]) == k) enough.insert(par);
      }
    }
    cout << ops << '\n';
  }
}
