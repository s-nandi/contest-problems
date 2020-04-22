// bitmask dp (bitcount state reduction)
// https://atcoder.jp/contests/dp/tasks/dp_o

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const int MOD = 1000000007;
auto add(auto a, auto b){return (a + b) % MOD;}

const int MAXN = 21;
bool a[MAXN][MAXN];
ll dp[2][1 << MAXN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  rep(i, 0, n) rep(j, 0, n)
    cin >> a[i][j];

  dp[0][0] = 1;
  rep(it, 0, n) {
    int i = ~it & 1;
    int prv = 1 - i;
    rep(bm, 0, (1 << n)) {
      if (__builtin_popcount(bm) != it + 1) continue;
      rep(matched, 0, n) {
	if (a[it][matched] and ((1 << matched) & bm) != 0) {
	  dp[i][bm] = add(dp[i][bm], dp[prv][bm - (1 << matched)]);
	}
      }
    }
  }
  cout << dp[n & 1][(1 << n) - 1] << '\n';
}
