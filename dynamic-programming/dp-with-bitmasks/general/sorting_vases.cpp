// dp with bitmask (max # of disjoint cycles), implicit graph, dfs (edge visited)
// https://www.codechef.com/MAY20A/problems/SORTVS

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to, id;};
using graph = vector<vector<edge>>;

struct DSU {
  vi par;
  DSU(int n) : par(n, -1) {}
  int find(int i){return par[i] < 0 ? i : (par[i] = find(par[i]));}
  void join(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    par[i] += par[j];
    par[j] = i;
  }
};

bool is_cycle(graph& g, int i, int start, auto& used, auto& oncycle, int rem) {
  if (rem == 0) return i == start;
  trav(e, g[i]) if (!used[e.id] and oncycle[e.id]) {
    used[e.id] = true;
    if (is_cycle(g, e.to, start, used, oncycle, rem - 1)) return true;
  }
  return false;
}

const int INF = 1031231234;
void minn(auto& a, auto b){a = min(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vi a(n);
    trav(i, a) {
      cin >> i;
      --i;
    }
    DSU dsu(n);
    rep(i, 0, m) {
      int u, v;
      cin >> u >> v;
      dsu.join(--u, --v);
    }
    auto getedge = [&](int i) {
                     int from = dsu.find(a[i]);
                     int to = dsu.find(i);
                     return pair{from, to};
                   };
    graph g(n);
    rep(i, 0, n) {
      auto [from, to] = getedge(i);
      g[from].PB({to, i});
    }
    vi cost(1 << n, INF);
    rep(bm, 1, 1 << n) {
      int start;
      vi oncycle(n);
      rep(i, 0, n) {
        if (bm & (1 << i)) {
          oncycle[i] = true;
          start = getedge(i).first;
        }
      }
      int num_nodes = accumulate(all(oncycle), 0);
      vi used(n);
      if (is_cycle(g, start, start, used, oncycle, num_nodes))
        cost[bm] = num_nodes - 1;
    }
    vi dp(1 << n, INF);
    dp[0] = 0;
    rep(bm, 0, 1 << n) {
      auto& best = dp[bm];
      for (int sm = bm; sm; sm = (sm - 1) & bm) {
        minn(best, cost[sm] + dp[bm - sm]);
      }
    }
    cout << dp.back() << '\n';
  }
}
