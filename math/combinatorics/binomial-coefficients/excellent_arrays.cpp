// combo, nck
// https://codeforces.com/contest/1550/problem/D

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

const int MAXS = 2 * (2 * 100'000 + 1) + 1;
const int MOD = 1'000'000'007;
 
int fac[MAXS];
int invfac[MAXS];
 
int add(ll a, ll b){return (a + b) % MOD;}
int mult(ll a, ll b){return a * b % MOD;}
int modpow(ll a, ll p) {
  ll res = 1;
  for (; p; p /= 2, a = mult(a, a))
    if (p & 1)
      res = mult(res, a);
  return res;
}
int inv(ll a){return modpow(a, MOD - 2);}
 
void precompute() {
  fac[0] = 1;
  rep(i, 1, MAXS) fac[i] = mult(fac[i - 1], i);
  rep(i, 0, MAXS) invfac[i] = inv(fac[i]);
}
 
int nck(int n, int k) {
  return mult(mult(fac[n], invfac[k]), invfac[n - k]);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  precompute();

  int T;
  cin >> T;
  while(T--) {
    int n, l, r;
    cin >> n >> l >> r;
    auto h = n / 2;
    auto h2 = n - h; // best f = h * h2

    auto minabs = min(-(l - 1), (r - n));
    auto maxabs = max(-(l - n), (r - 1));
    int ways = mult(minabs, mult((h == h2 ? 1 : 2), nck(n, h)));

    auto numneg = [&](int val) { // ub = r-1-i < val => n - 1 >= i > r - 1 - val
                    return max(0, (n - 1) - (r - 1 - val));
                  };
    auto numpos = [&](int val) { // lb = l-1-i > -val => 0 <= i < l - 1 + val
                    return max(0, (l - 1 + val) - 0);
                  };
    rep(diff, minabs + 1, maxabs + 1) {
      auto neg = numneg(diff);
      auto pos = numpos(diff);
      auto numrem = n - neg - pos;
      if (numrem < 0) break;
      rep(it, 0, 2) {
        if (it == 1 and h == h2) break;
        int delta = 0;
        auto rem1 = h - neg;
        auto rem2 = h2 - pos;
        if (rem1 >= 0 and rem2 >= 0) { // partition numrem into two groups
          delta = nck(numrem, rem1);
        }
        ways = add(ways, delta);
        swap(h, h2);
      }
    }
    cout << ways << '\n';
  }
}
