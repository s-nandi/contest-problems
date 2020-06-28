// dp on digits, prime check (sqrt), works in time because only 25 primes <= 100
// https://www.codechef.com/ENJU2020/problems/ECJN207

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using ii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MOD = 1000000007;

int add(ll a, ll b){return (a + b) % MOD;}
void self_add(auto& a, auto b){a = ((ll) a + b) % MOD;}

const int MAXN = 100;
const int MAXS = 26 * MAXN;
const int MAXT = MAXS + 500;
bool prm[MAXT];
int dp[MAXN + 5][MAXS + 5][2]; // i, sum, less than

int ways(const string& bound) {
  int n = sz(bound);
  auto total = 26 * n;
  memset(dp, 0, sizeof(dp));
  dp[0][0][0] = 1;
  rep(i, 0, n) {
    int have = bound[i] - 'a';
    rep(k, 0, total + 1) {
      rep(below, 0, 2) {
        if (dp[i][k][below] == 0) continue;
        rep(choice, 0, 26) {
          if (!below and choice > have) continue;
          int nk = k + (prm[i] ? choice : 0);
          self_add(dp[i + 1][nk][below or choice < have], dp[i][k][below]);
        }
      }
    }
  }
  int res = 0;
  rep(k, 0, total + 1) {
    if (prm[k]) {
      self_add(res, dp[n][k][true]);
      self_add(res, dp[n][k][false]);
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  prm[0] = prm[1] = false;
  rep(i, 2, MAXT) prm[i] = true; 
  rep(i, 2, MAXT) {
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        prm[i] = false;
        break;
      }
    }
  }
  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    auto res = ways(s);
    cout << res << '\n';
  }
}
