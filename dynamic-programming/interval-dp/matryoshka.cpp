// interval (MCM) dp, mex (cost of merge is max mex among lhs,rhs w/ compressed vals), partition cover dp
// https://codeforces.com/gym/101208/problem/H
// 2013 World Finals

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int MAXN = 500 + 50;
const int INF = 1031231234;
bool ok[MAXN][MAXN];
int cost[MAXN][MAXN];
int inleft[MAXN], inright[MAXN];
int dp[MAXN];
void minn(auto& a, auto b){ a = min(a, b); }

int mincost(int n) {
  rep(i, 0, n + 1) dp[i] = INF;
  dp[0] = 0;
  rep(i, 0, n) {
    rep(j, i, n) if (ok[i][j])
      minn(dp[j + 1], dp[i] + cost[i][j]);
  }
  return dp[n];
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) {cin >> i; --i;}

  rep(i, 0, n) {
    vi vals;
    rep(j, i, n) {
      vals.insert(lower_bound(all(vals), a[j]), a[j]);
      ok[i][j] = true;
      rep(it, 0, sz(vals)) ok[i][j] &= it == vals[it];
    }
  }

  rep(i, 0, n) rep(j, i, n) cost[i][j] = INF;
  rep(i, 0, n) cost[i][i] = 0;
  rep(len, 2, n + 1) {
    rep(i, 0, n - len + 1) {
      auto j = i + len - 1;
      // Can this log factor be removed?
      vi vals;
      rep(pos, i, j + 1) vals.PB(a[pos]);
      sort(all(vals));
      vals.erase(unique(all(vals)), end(vals));
      if (sz(vals) != len) continue;
      auto indexof = [&](int val) -> int {return lower_bound(all(vals), val) - begin(vals);};

      int mexleft = 0, mexright = sz(vals);
      rep(i, 0, sz(vals)) inleft[i] = 0, inright[i] = 1;
      rep(k, i, j) { // [i, k] and [k + 1, j] partition
        auto val = indexof(a[k]);
        inleft[val]++, inright[val]--;
        while (mexleft < sz(vals) and inleft[mexleft]) mexleft++;
        mexright = min(mexright, val);
        auto best = max(mexleft, mexright);
        
        minn(cost[i][j], cost[i][k] + cost[k + 1][j] + (len - best));
      }
    }
  }
  auto res = mincost(n);
  if (res == INF) cout << "impossible" << '\n';
  else cout << res << '\n';
}
