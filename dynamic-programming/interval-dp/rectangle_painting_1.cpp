// interval dp (2 dimensions), dp works because if there's no empty row/col it is optimal to just color the whole rectangle => take min of coloring whole rectangle and consider all split partitions (hor/vert)
// https://codeforces.com/contest/1198/problem/D

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

struct edge{int to;};
using graph = vector<vector<edge>>;

auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  auto grid = vector(n, string(n, ' '));
  trav(row, grid) cin >> row;
  
  auto dp = vector(n + 1, vector(n + 1, vector(n, vi(n, -1))));
  // dp[len1][len2][i][j] = min cost for rectangle len1 x len2 w/ lower left corner at (i, j)

  rep(i, 0, n) rep(j, 0, n) {
    rep(len, 0, n + 1) dp[0][len][i][j] = dp[len][0][i][j] = 0;
    dp[1][1][i][j] = (grid[i][j] == '#');
  }
    
  rep(len1, 1, n + 1) rep(len2, 1, n + 1) {
    if (len1 == 1 and len2 == 1) continue;
    rep(i, 0, n - len1 + 1) rep(j, 0, n - len2 + 1) {
      auto& curr = dp[len1][len2][i][j];
      curr = max(len1, len2);
      rep(sublen1, 1, len1) {
        auto rem1 = len1 - sublen1;
        auto i2 = i + sublen1;
        auto possible = dp[sublen1][len2][i][j] + dp[rem1][len2][i2][j];
        minn(curr, possible);
      }
      rep(sublen2, 1, len2) {
        auto rem2 = len2 - sublen2;
        auto j2 = j + sublen2;
        auto possible = dp[len1][sublen2][i][j] + dp[len1][rem2][i][j2];
        minn(curr, possible);
      }
    }
  }
  cout << dp[n][n][0][0] << '\n';
}
