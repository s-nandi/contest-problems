// dfs, interactively finding root by performing <= n/2 lca queries 
// https://codeforces.com/contest/1305/problem/D
// Note: Not necessary to query endpts of diameter, can use any two leaves as query

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)size(x)
#define PB push_back

struct edge{int to, id;};
using graph = vector<vector<edge>>;

int timer = 1;
vi leaves;
void get_leaves(auto& g, auto& blk, auto& vis, int curr) {
  if (vis[curr] == timer) return;
  vis[curr] = timer;
  int deg = sz(g[curr]);
  for (auto e: g[curr]) {
    if (blk[e.id]) deg--;
    else get_leaves(g, blk, vis, e.to);
  }
  if (deg <= 1) leaves.PB(curr);
}

void killedges(auto& g, auto& blk, auto& vis, int curr, int target) {
  if (vis[curr] == timer or curr == target) return;
  vis[curr] = timer;
  for (auto e: g[curr]) {
    if (blk[e.id]) continue;
    blk[e.id] = true;
    killedges(g, blk, vis, e.to, target);
  }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    graph g(n);
    rep(i, 0, n - 1) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      g[a].PB({b, i});
      g[b].PB({a, i});
    }
    auto on = 0;
    vi blocked(n - 1), visited(n);
    while (true) {
      // reset visited & leaves
      timer++;
      leaves.clear();
      get_leaves(g, blocked, visited, on);
      assert(!empty(leaves));
      if (sz(leaves) == 1) {
        cout << "! " << leaves[0] + 1 << endl;
        exit(0);
      } else {
        auto a = leaves[0], b = leaves[1];
        cout << "? " << a + 1 << " " << b + 1 << endl;
        int lca;
        cin >> lca;
        if (lca == -1) exit(0);
        on = --lca;

        timer++;
        killedges(g, blocked, visited, a, lca);
        killedges(g, blocked, visited, b, lca);
      }
    }
}
