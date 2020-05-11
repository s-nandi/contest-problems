// combo (overcount then fix), # of ways to color elements s.t. <= k adjacent pairs have the same color
// https://atcoder.jp/contests/abc167/tasks/abc167_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const int MOD = 998244353;
auto add(ll a, ll b){return (a + b) % MOD;}
auto sub(ll a, ll b){return (a - b + MOD) % MOD;}
auto mult(ll a, ll b){return a * b % MOD;}
auto exp(ll n, ll p) {
  ll acc = 1;
  for (auto pwr = n; p; pwr = mult(pwr, pwr), p >>= 1)
    if (p & 1)
      acc = mult(acc, pwr);
  return acc;
}
auto mdiv(ll a, ll b){return mult(a, exp(b, MOD - 2));}

const int MAXN = 3 * 1e5;
ll factorial[MAXN + 5];
ll nck(ll n, ll k) {
  return mdiv(factorial[n], mult(factorial[k], factorial[n - k]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  factorial[0] = 1;
  rep(i, 1, MAXN + 5) {
    factorial[i] = mult(factorial[i - 1], i);
  }

  int n, m, k;
  cin >> n >> m >> k;
  ll total = exp(m, n);
  ll acc = 0;
  rep(i, k + 1, n) {
    ll rem = n - i;
    ll choices = nck(n - 1, i);
    ll ways = mult(m, exp(m - 1, rem - 1));
    ll delta = mult(choices, ways);
    acc = add(acc, delta);
  }
  auto res = sub(total, acc);
  cout << res << '\n';
}
