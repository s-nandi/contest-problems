// toposort, dp-ish, greedy (delete nodes as far down as possible), constructive
// https://codeforces.com/contest/1368/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    graph g(n);
    vi ideg(n);
    rep(i, 0, m) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      ideg[v]++;
    }
 
    queue<int> q;
    vi state(n), res;
    rep(i, 0, n) {
      if (ideg[i] == 0)
        q.push(i);
    }
    while(!q.empty()) {
      int i = q.front(); q.pop();
      if (state[i] == 2) {
        res.PB(i);
        state[i] = -1;
      }
      trav(e, g[i]) {
        state[e.to] = max(state[e.to], state[i] + 1);
        if (--ideg[e.to] == 0)
          q.push(e.to);
      }
    }
    cout << sz(res) << '\n';
    trav(i, res) cout << i + 1 << " "; cout << '\n';
  }
}
