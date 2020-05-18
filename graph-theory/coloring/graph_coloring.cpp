// bipartite coloring, knapsack (state reduction, reconstruction)
// https://codeforces.com/contest/1354/problem/E

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

bool isbipartite(graph& g, int i, auto& col, auto& comp, int c = 0) {
  if (col[i] != -1) return col[i] == c;
  col[i] = c;
  comp.PB(i);
  trav(e, g[i])
    if (!isbipartite(g, e.to, col, comp, 1 - c))
      return false;
  return true;
}

const int MAXN = 5000;
bool dp[MAXN + 5][MAXN + 5];
pair<int, bool> prv[MAXN + 5][MAXN + 5];

bool orr(bool& a, bool b){
  if (a < b) {a = b; return true;}
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vi cnt(3);
  trav(i, cnt) cin >> i;
  graph g(n);
  rep(i, 0, m) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    g[a].PB({b});
    g[b].PB({a});
  }
  bool valid = true;
  vi color(n, -1);
  vector<array<vi, 2>> bycolor;    
  rep(i, 0, n) if (color[i] == -1) {
    vi comp;
    if (!(valid &= isbipartite(g, i, color, comp))) break;
    auto& curr = bycolor.emplace_back();
    trav(j, comp) curr[color[j]].PB(j);
  }
  if (!valid) cout << "NO" << '\n';
  else {
    dp[0][0] = true;
    int total = 0;
    rep(i, 0, sz(bycolor)) {
      auto& curr = bycolor[i];
      int s1 = sz(curr[0]), s2 = sz(curr[1]);
      rep(j, 0, cnt[1] + 1) {
        auto k = total - j;
        if (k < 0 or k > cnt[0] + cnt[2]) continue;
        rep(flip, 0, 2) {
          int nj = j + s1;
          int nk = k + s2;
          if (nj <= cnt[1] and nk <= cnt[0] + cnt[2])
            if (orr(dp[i + 1][nj], dp[i][j]))
              prv[i + 1][nj] = {j, flip};
          swap(s1, s2);
        }
      }
      total += s1 + s2;
    }
    if (!dp[sz(bycolor)][cnt[1]]) cout << "NO" << '\n';
    else {
      cout << "YES" << '\n';
      string sol(n, '?');
      for (int it = sz(bycolor), tot = cnt[1]; it > 0; it--) {
        auto [ntot, flip] = prv[it][tot];
        auto& curr = bycolor[it - 1];
        if (flip) swap(curr[0], curr[1]);
        trav(c, curr[0]) sol[c] = '2';
        trav(c, curr[1]) {
          sol[c] = cnt[0] ? '1' : '3';
          --cnt[sol[c] - '1'];
        }
        tot = ntot;
      }
      cout << sol << '\n';
    }
  }
}
