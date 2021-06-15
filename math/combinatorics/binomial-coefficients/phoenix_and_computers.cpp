// combo / dp (count # ways to partition), # of ways to interleave operations (nck)
// https://codeforces.com/contest/1515/problem/E

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

int MOD;

int add(int a, int b){return a + b >= MOD ? a + b - MOD : a + b;}
int mult(ll a, ll b){return a * b % MOD;}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n >> MOD;

  // solution always looks like (0 = automatically turned on, 1 = manually turned on)
  // 1 1 ... 1 0 1 1 ... 1 1 0 1 1 .... 1

  n++; // add sentinel 0 on the far left,
       // now can divide solution into runs of (0,1,1,1,...,1)

  auto pascal = vector(n + 1, vector(n + 1, 0));
  auto nck = [&](int i, int j) {
               if (j < 0 or j > i) return 0;
               return pascal[i][j];
             };
  pascal[0][0] = 1;
  rep(i, 1, n + 1) rep(j, 0, i + 1) {
    pascal[i][j] = add(nck(i - 1, j), nck(i - 1, j - 1));
  }

  auto powers = vector(n + 1, 0);
  powers[0] = 1;
  rep(i, 1, n + 1) powers[i] = mult(powers[i - 1], 2);

  auto dp = vector(n + 1, vector(n + 1, 0));
  dp[0][0] = 1;
  rep(i, 1, n + 1) {
    rep(j, 1, n + 1) {
      rep(i2, 2, i + 1) { // 0,1,1,...,1 => i2 length
        auto within = powers[i2 - 2]; // # ways to activate all 1's within a block (look in reverse -> can only activate front or back)
        auto orderings = nck(i - j, i2 - 1); // # ways to interleave the manual activations b/w this block and previous blocks
        dp[i][j] = add(dp[i][j], mult(mult(within, orderings), dp[i - i2][j - 1]));
      }
    }
  }
  
  int res = 0;
  rep(j, 0, n + 1) res = add(res, dp[n][j]);
  cout << res << '\n';
}
