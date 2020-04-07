// dp on trees (reconstruct sol), greedy, constructive
// https://codeforces.com/gym/101612 (problem H)
// 2017 NEERC Northern Subregional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 100000;
int dp[2][MAXN + 5];
int best_child[MAXN + 5];
bool taken[MAXN + 5];

auto maxx(auto& a, auto b) {
  if (a < b) {a = b; return true;}
  else return false;
}

void recur(graph& g, int i) {
  dp[0][i] = dp[1][i] = 0;
  best_child[i] = -1;
  trav(e, g[i]) {
    recur(g, e.to);
    dp[0][i] += dp[1][e.to];
  }
  dp[1][i] = dp[0][i];
  trav(e, g[i])
    if (maxx(dp[1][i], dp[0][i] - dp[1][e.to] + dp[0][e.to] + 1))
      best_child[i] = e.to;
}

void find_free(graph& g, int i, auto& fr, bool parent_paired = false) {
  taken[i] = (parent_paired or dp[1][i] > dp[0][i]);
  if (!taken[i]) fr.PB(i);
  trav(e, g[i]) {
    auto pair_with_child = (!parent_paired and taken[i] and e.to == best_child[i]);
    find_free(g, e.to, fr, pair_with_child);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  // Uncomment to submit
  // freopen("hidden.in", "r", stdin);
  // freopen("hidden.out", "w", stdout);
    
  int n;
  cin >> n;
  vi par(n, -1), roots{0};
  graph g(n);
  rep(i, 1, n) {
    cin >> par[i]; --par[i];
    if (par[i] == -1) roots.PB(i);
    else g[par[i]].PB({i});
  }
  map<int, vi> free_nodes;
  trav(i, roots) {
    recur(g, i);
    find_free(g, i, free_nodes[i]);
  }
  int sol = 0;
  vi tops, bottoms;
  trav(i, roots) {
    sol += dp[taken[i]][i];
    if (!taken[i] and i != 0)
      bottoms.PB(i);
    else {
      par[i] = 0;
      trav(j, free_nodes[i])
        tops.PB(j);
    }
  }
  sort(all(bottoms), [&](int i, int j){return sz(free_nodes[i]) > sz(free_nodes[j]);});

  trav(i, bottoms) {
    bool merged = false;
    if (!tops.empty()) {
      par[i] = tops.back();
      tops.pop_back();
      merged = true;
      ++sol;
    } else par[i] = 0;
    trav(j, free_nodes[i])
      if (!merged or i != j)
        tops.PB(j);
  }
  cout << sol << '\n';
  rep(i, 1, n)
    cout << par[i] + 1 << " ";
  cout << '\n';
}
