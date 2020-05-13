// dp on tree (prefix max, amortized kinda), cases in lines 38-43 are sufficient, no need to loop over all distances in another nested loop
// https://codeforces.com/contest/1249/problem/F
// Note: This is  N^2, but can be done in O(N): https://codeforces.com/blog/entry/70822

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 200;
const int MAXK = 200;
int a[MAXN + 5];
int dp[MAXN + 5][MAXK + 5];
int prv[MAXN + 5][MAXK + 5];
int n, k;

void maxx(auto& a, auto b){a = max(a, b);}

void solve(const auto& g, int i, int p = -1) {
  memset(dp[i], 0, sizeof(dp[i]));
  dp[i][0] = a[i]; 
  trav(e, g[i]) if (e.to != p) {
    solve(g, e.to, i);
  }
  trav(e, g[i]) if (e.to != p) {
    memcpy(prv[i], dp[i], sizeof(dp[i]));
    rep(dist, 0, k + 1) {
      auto ndist = min(dist + 1, k);
      if (ndist < k - ndist) {
        maxx(dp[i][ndist], dp[e.to][dist] + prv[i][k - ndist]);
      } else {
        maxx(dp[i][k - ndist], dp[e.to][dist] + prv[i][k - ndist]);
        maxx(dp[i][ndist], dp[e.to][dist] + prv[i][ndist]);
      }
    }
    for (int dist = k - 1; dist >= 0; dist--)
      maxx(dp[i][dist], dp[i][dist + 1]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  ++k;
  rep(i, 0, n) cin >> a[i];
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  solve(g, 0);
  auto res = *max_element(all(dp[0]));
  cout << res << '\n';
}
