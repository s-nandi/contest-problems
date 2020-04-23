// dp (reconstruct, greedy -- first digit dominates, knapsack)
// https://codeforces.com/contest/1340/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const vector<string> nums = {"1110111",
                             "0010010",
                             "1011101",
                             "1011011",
                             "0111010",
                             "1101011",
                             "1101111",
                             "1010010",
                             "1111111",
                             "1111011"};
vi bs;
int tobin(const string& s) {
  int res = 0;
  rep(i, 0, sz(s)) {
    res <<= 1;
    res += (s[i] == '1');
  }
  return res;
}

const int MAXN = 2000;
const int MAXK = 2000;
short sentinel = -1;
short dp[MAXN + 20][MAXK + 20][10];
auto maxx(auto& a, auto b){a = max<short>(a, b);}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  trav(s, nums)
    bs.PB(tobin(s));

  int n, k;
  cin >> n >> k;
  vi a(n);
  rep(i, 0, n) {
    string s;
    cin >> s;
    a[i] = tobin(s);
  }
  reverse(all(a));
  
  rep(i, 0, MAXN + 20) rep(j, 0, MAXN + 20) rep(c, 0, 10)
    dp[i][j][c] = sentinel;
  
  dp[0][0][0] = 0;
  rep(i, 0, n) {
    rep(j, 0, k + 1) {
      rep(c1, 0, 10) {
        if (dp[i][j][c1] == sentinel) continue;
        rep(c2, 0, 10) {
          if ((bs[c2] & a[i]) != a[i]) continue;
          int delta = __builtin_popcount(bs[c2] - a[i]);
          maxx(dp[i + 1][j + delta][c2], c1);
        }
      }
    }
  }
  string best;
  bool feas = false;
  rep(c, 0, 10) {
    if (dp[n][k][c] != sentinel) {
      string res;
      int ci = n, cj = k, ck = c;
      while (ci > 0) {
        auto& nk = dp[ci][cj][ck];
        res += '0' + ck;
        cj -= __builtin_popcount(bs[ck] - a[ci - 1]);
        ck = nk;
        ci--;
      }
      best = !feas ? res : max(res, best);
      feas = true;
    }
  }
  cout << (feas ? best : "-1") << '\n';
}
