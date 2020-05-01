// inclusion-exclusion, stars and bars, # of ways to connect two sets of nodes s.t. no node has 0 degree
// https://utipc19.kattis.com/problems/utipc19.neuralnetworks
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)

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

const int MAXN = 5 * 1e5;
ll factorial[MAXN + 5];
ll pow2[MAXN + 5];
ll nck(ll n, ll k) {
  return mdiv(factorial[n], mult(factorial[k], factorial[n - k]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  factorial[0] = pow2[0] = 1;
  rep(i, 1, MAXN + 5) {
    pow2[i] = mult(pow2[i - 1], 2);
    factorial[i] = mult(factorial[i - 1], i);
  }
  
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  ll res = 1LL;
  rep(i, 0, sz(a) - 1) { // count # of ways to connect layers i and i+1
    auto u = a[i];
    auto v = a[i + 1];
    if (u > v) swap(u, v); // this is fine, we loop from 0 to a[i] at most twice for any i

    ll acc = 0LL;
    rep(zeros, 0, v) {
      auto ways = nck(v, zeros);
      auto delta = exp(sub(pow2[v - zeros], 1), u);
      if (zeros & 1) acc = sub(acc, mult(ways, delta));
      else acc = add(acc, mult(ways, delta));
    }
    res = mult(res, acc);
  }
  cout << res << '\n';
}
