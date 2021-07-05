// digit dp, # of possible products is small (~log(k)^4, editorial has proof)
// https://atcoder.jp/contests/abc208/tasks/abc208_e

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

const int MAXN = 19;
const int MAXD = 10;
const int MAXK = 1000000000;
map<int, ll> dp[MAXN + 1][2][2];

int mult(int a, int b, int k) {
  auto res = (ll) a * b;
  return res <= k ? res : MAXK + 1;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s; int k;
  cin >> s >> k;

  int n = sz(s);
  vi a(n);
  rep(i, 0, n) a[i] = s[i] - '0';

  dp[0][false][false][1] = 1;
  rep(i, 0, n) rep(has_nonzero, 0, 2) rep(is_below, 0, 2) {
    for (const auto& [prod, cnt]: dp[i][has_nonzero][is_below]) {
      rep(dig, 0, MAXD) {
        if (!is_below and dig > a[i]) continue;
        auto nhas_nonzero = has_nonzero or dig != 0;
        auto nis_below = is_below or dig < a[i];
        auto nprod = nhas_nonzero ? mult(prod, dig, k) : 1;
        dp[i + 1][nhas_nonzero][nis_below][nprod] += cnt;
      }
    }
  }
  ll res = 0;
  rep(is_below, 0, 2) for (const auto& [prod, cnt]: dp[n][true][is_below]) {
    if (prod <= k) res += cnt;
  }
  cout << res << '\n';
}
