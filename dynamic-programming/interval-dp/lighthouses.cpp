// interval dp (on circular chain, differentiate between orientation)
// https://codeforces.com/group/ZFgXbZSjvp/contest/274852 (problem G)
// NAPC 4

#include <bits/stdc++.h>
using namespace std;
 
using ld = long double;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
 
using ptT = ld;
struct pt {
  ptT x, y;
  ptT dist(const auto& o) const {
    auto dx = x - o.x, dy = y - o.y;
    return sqrt(dx * dx + dy * dy);
  }
};
 
const int MAXN = 300;
bool exists[MAXN + 5][MAXN + 5];
ptT dp[MAXN + 5][2 * MAXN + 5][2];
 
auto maxx(auto& a, auto b){a = max(a, b);}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<pt> points;
    points.resize(n);
    rep(i, 0, n) {
      cin >> points[i].x >> points[i].y;
    }
    int m;
    cin >> m;
    memset(exists, 0, sizeof(exists));
    rep(i, 0, m) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      exists[a][b] = exists[b][a] = true;
    }
    memset(dp, 0, sizeof(dp)); 
    rep(len, 1, n) {
      rep(i, 0, n) {
        rep(ccw, 0, 2) {
          rep(it, 1, len + 1) {
            int j = ccw ? (i + it) % n : (i + n - it) % n;
            auto contrib = exists[i][j] ? points[i].dist(points[j]) : ptT(0);
            if (!exists[i][j]) continue;
            maxx(dp[i][len][ccw], dp[j][it - 1][1 - ccw] + contrib);
            maxx(dp[i][len][ccw], dp[j][len - it][ccw] + contrib);
          }
        }
      }
    }
    auto res = ptT(0);
    rep(i, 0, n) { // try all starting points
      maxx(res, dp[i][n - 1][0]);
    }
    cout << fixed << setprecision(11) << res << '\n';
  }
}
