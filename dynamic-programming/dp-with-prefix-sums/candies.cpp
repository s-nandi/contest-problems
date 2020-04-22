// dp (prefix sums, space saving)
// https://atcoder.jp/contests/dp/tasks/dp_m

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)

const int MOD = 1000000007;
ll add(ll a, ll b){return (a + b) % MOD;}

const int MAXN = 100;
const int MAXK = 100000;
ll dp[MAXK + 5]; 
ll psum[MAXK + 5];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vi a(n);
  trav(i, a) cin >> i;

  fill(all(psum), 1);
  auto sum = [&](int i, int j){return i ? (psum[j] - psum[i - 1] + MOD) % MOD : psum[j];};
  rep(i, 0, n) {
    rep(j, 0, k + 1) {
      dp[j] = sum(j - min(j, a[i]), j);
    }
    psum[0] = dp[0];
    rep(j, 1, k + 1)
      psum[j] = add(psum[j - 1], dp[j]);
  }
  cout << dp[k] << '\n';
}
