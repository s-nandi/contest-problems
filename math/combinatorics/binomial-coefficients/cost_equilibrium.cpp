// combo, min = max cost when source/sinks are partitioned or no cross-over point (only happens w/ unique source or sink)
// https://codeforces.com/contest/1513/problem/E

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr auto dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MOD = 1'000'000'007;

int mult(ll a, ll b) { return a * b % MOD; }
int add(ll a, ll b) { return (a + b) % MOD; }
int modpow(ll a, ll p) {
  ll res = 1;
  for (; p; p /= 2, a = mult(a, a))
    if (p & 1)
      res = mult(res, a);
  return res;
}
int modinv(ll a) { return modpow(a, MOD - 2); }
int moddiv(ll a, ll b) {return mult(a, modinv(b));}
int fac(int v) {
  ll res = 1;
  rep(i, 1, v + 1) res = mult(res, i);
  return res;
}

int nck(ll n, ll k) {
  auto num = fac(n);
  auto denom = mult(fac(k), fac(n - k));
  return moddiv(num, denom);
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  auto tot = accumulate(all(a), 0LL);
  if (tot % n != 0) cout << 0 << '\n';
  else {
    auto target = tot / n;
    int pos = 0;
    int neg = 0;
    int zer = 0;
    map<int, int> freq;
    trav(i, a) {
      if (i < target) pos++;
      else if (i > target) neg++;
      else zer++;
      freq[i]++;
    }
    int res;
    if (pos <= 1 or neg <= 1) res = fac(n);
    else {
      auto ways1 = mult(mult(2, fac(pos), fac(neg)));
      auto ways2 = fac(zer);
      auto interleave = nck(n, zer);
      res = mult(mult(ways1, ways2), interleave);
    }
    for (const auto& [elem, cnt]: freq) {
      auto overcnt = fac(cnt);
      res = moddiv(res, overcnt);
    }
    cout << res << '\n';
  }
}
