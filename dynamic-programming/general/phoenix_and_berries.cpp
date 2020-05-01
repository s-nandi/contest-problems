// dp (state compression), greedy (no point saving more than k berries from a basket - dp tells us how many of each type we should save)
// https://codeforces.com/contest/1348/problem/E

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define all(a) begin(a),end(a)

const int MAXN = 500;
ll dp[MAXN + 5][MAXN + 5]; 

auto maxx(auto& a, auto b){a = max(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, k;
  cin >> n >> k;
  vi b(n), r(n);
  rep(i, 0, n)
    cin >> b[i] >> r[i];

  ll res = 0;
  ll behind = 0;
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  rep(i, 0, n) {
    rep(blue_rem, 0, k) {
      if (dp[i][blue_rem] == -1) continue;
      auto red_rem = (behind - blue_rem + k) % k;
      rep(ignore_blue, 0, k) {
        auto max_self = (b[i] - ignore_blue + r[i]) / k;
        auto blue_for_basket = b[i] - ignore_blue;
        auto red_for_basket = max_self * k - blue_for_basket;
        auto ignore_red = r[i] - red_for_basket;
        if (blue_for_basket < 0 or ignore_red < 0 or red_for_basket < 0) continue;
        auto have_blue = ignore_blue + blue_rem;
        auto have_red = ignore_red + red_rem;
        auto delta = max_self;
        delta += have_blue / k;
        delta += have_red / k;
        maxx(dp[i + 1][have_blue % k], dp[i][blue_rem] + delta);
      }
    }
    behind += b[i] + r[i];
  }
  cout << *max_element(all(dp[n])) << '\n';
}
