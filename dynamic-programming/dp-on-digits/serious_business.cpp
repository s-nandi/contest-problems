// dp on digits, number of even substrings from parity of suffixes
// https://utipc19.kattis.com/problems/utipc19.seriousbusiness
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for (auto i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MOD = 998244353;
const int MAXN = 100000;
int dp[MAXN + 5][2][2][2][2][2][2];
// i, parity of # of even sum substrings, par. of even suffixes, par. of odd suffixes, aove l, below r, started

int add(int a, int b) { return ((ll)a + b) % MOD; }
void self_add(int &a, int b) { a = add(a, b); }

void pad_with_zeros(string& s, int z) {
  reverse(all(s));
  rep(i, 0, z) s += '0';
  reverse(all(s));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string l, r;
  cin >> l >> r;
  if (sz(l) < sz(r)) pad_with_zeros(l, sz(r) - sz(l));
  int n = sz(r);

  dp[0][0][0][0][0][0][0] = 1;
  rep(i, 0, n + 1) {
    rep(esubstr, 0, 2) {
      rep(esuffix, 0, 2) {
        rep(osuffix, 0, 2) {
          rep(above_l, 0, 2) {
            rep(below_r, 0, 2) {
              rep(started, 0, 2) {
                auto &curr = dp[i][esubstr][esuffix][osuffix][above_l][below_r][started];
                if (curr == 0) continue;
                rep(c, '0', '9' + 1) {
                  if (!above_l and c < l[i]) continue;
                  if (!below_r and c > r[i]) continue;
                  auto nabove_l = above_l or c > l[i];
                  auto nbelow_r = below_r or c < r[i];
                  auto nstarted = started or c != '0';
                  if (!started and c == '0') {
                    self_add(dp[i + 1][0][0][0][nabove_l][nbelow_r][nstarted], curr);
                  } else {
                    auto isodd = (c - '0') & 1;
                    auto n_esuffix = !isodd ? esuffix ^ 1 : osuffix; // ^ 1 b/c empty suffix can be extended
                    auto n_osuffix = isodd ? esuffix ^ 1 : osuffix;
                    auto n_esubstr = esubstr ^ n_esuffix;
                    self_add(dp[i + 1][n_esubstr][n_esuffix][n_osuffix][nabove_l][nbelow_r][nstarted], curr);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  auto res = 0;
  rep(esuffix, 0, 2) rep(osuffix, 0, 2) rep(above_l, 0, 2) rep(below_r, 0, 2)
    self_add(res, dp[n][1][esuffix][osuffix][above_l][below_r][1]);
  cout << res << '\n';
}
