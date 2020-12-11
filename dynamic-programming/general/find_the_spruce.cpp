// dp (broken profiles-ish but simpler, similar to max square in 0/1 grid)
// https://codeforces.com/contest/1461/problem/B
// Note: There are alternate solutions (including editorial sol) in O(N^3) that use prefix sums + brute force

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;
  
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    auto grid = vector(n, string(m, ' '));
    rep(i, 0, n) rep(j, 0, m)
      cin >> grid[i][j];

    auto dp = vector(n, vi(m));
    rep(i, 0, n) {
      rep(j, 0, m) {
        if (grid[i][j] == '.') continue;
        if (i - 1 >= 0 and j - 2 >= 0)
          dp[i][j] = min({dp[i - 1][j - 1], dp[i][j - 2], dp[i][j - 1]}) + 1; // if i, j is bottom right square of spruce,
                                                                              // then note that a k-size spruce recursively contains (k-1)-size spruces
                                                                              // with bottom right squares at (i - 1, j - 1), (i, j - 2), (i, j - 1)
                                                                              // so we can take the min at these positions and add 1
        else
          dp[i][j] = 1; // if we can't extend any smaller spruces, we at least have a size 1 spruce
      }
    }
    auto acc = 0;
    rep(i, 0, n) rep(j, 0, m) acc += dp[i][j];
    cout << acc << '\n';
  }
}
