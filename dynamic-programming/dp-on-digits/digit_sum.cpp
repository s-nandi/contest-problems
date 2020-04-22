// digit dp (keep track if below some threshold number in state)
// https://atcoder.jp/contests/dp/tasks/dp_s

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()

const int MOD = 1000000007;
const int MAXD = 10000;
const int MAXK = 100;
ll dp[MAXD + 5][MAXK][2]; // # digits, modulo k, isbelow

void add(auto& a, auto b){a = (a + b) % MOD;}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int k;
  cin >> k;
  int n = sz(s);
  dp[0][0][0] = 1;
  rep(i, 0, n) {
    rep(j, 0, k) {
      rep(c, '0', '9' + 1) {
        rep(below, 0, 2) {
          if (!below and c > s[i]) continue;
          int j2 = (j + (c - '0')) % k;
          bool below2 = below || c < s[i];
          add(dp[i + 1][j2][below2], dp[i][j][below]);
        }
      }
    }
  }
  dp[n][0][1] = (dp[n][0][1] - 1 + MOD) % MOD; // exclude 0...00 since it's not a valid answer
  cout << (dp[n][0][1] + dp[n][0][0]) % MOD << '\n';
}
