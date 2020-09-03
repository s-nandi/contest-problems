// dp w/ bitmasks (tsp style), fine-grained analysis (naive bound is n * 4^n which would TLE), state representing i items chosen has 2^i states (uneven rows)
// https://codeforces.com/contest/1326/problem/F1

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

constexpr auto nck(int n, int k) {
  ll res = 1;
  rep(i, 0, k) res *= (n - i);
  rep(i, 1, k + 1) res /= i;
  return res;
}

constexpr auto numops(int n) {
  ll res = 0;
  rep(i, 1LL, n + 1)
    res += nck(n, i) * n * n * (1LL << (i - 1));
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  constexpr auto maxops = numops(14);
  static_assert(maxops < 5 * 1e8);
  
  int n;
  cin >> n;
  auto mat = vector(n, vi(n));
  trav(row, mat) trav(elem, row) {
    char c;
    cin >> c;
    elem = c - '0';
  }

  auto dp = vector(1 << n, vector(n, vector<ll>{})); // dp[bm][k][s] = # of ways to order popcount(bm) people where
                                                     //                bm represents people used so far,
                                                     //                k denotes last person in list,
                                                     //                s is generated string from diffs (has popcount(bm) - 1 bits)
  ll ops = 0;
  rep(bm, 1, 1 << n) {
    rep(k, 0, n) if (bm & (1 << k)) {
      auto cnt = __builtin_popcount(bm);
      if (cnt < 2) continue;
      dp[bm][k].resize(1 << (cnt - 1));
      auto sm = bm - (1 << k);
      rep(pk, 0, n) if (sm & (1 << pk)) {
        auto bit = mat[pk][k];
        if (cnt == 2) { // base case: 2 people used w/ last person k
          dp[bm][k][bit] = 1;
          ops++;
        } else {
          rep(ps, 0, sz(dp[sm][pk])) {
            dp[bm][k][ps << 1 | bit] += dp[sm][pk][ps];
            ops++;
          }
        }
      }
    }
  }
  assert(ops <= maxops);
  vector<ll> res(1 << (n - 1));
  const auto full = (1 << n) - 1;
  rep(k, 0, n) rep(s, 0, 1 << (n - 1)) res[s] += dp[full][k][s];
  trav(i, res) cout << i << " "; cout << '\n';
}
