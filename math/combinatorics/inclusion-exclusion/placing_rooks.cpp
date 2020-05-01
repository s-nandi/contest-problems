// incl-excl, constraints => 1 rook each row(col) & distributed among p diff cols(rows)
// https://codeforces.com/contest/1342/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)

const int MOD = 998244353;
struct mint {
  ll v;
  mint(int val = 0) : v{val} {v = v < 0 ? v + MOD : v > MOD ? v - MOD : v;}
  mint operator + (mint o) {return mint(v + o.v);}
  mint operator - (mint o) {return mint(v - o.v);}
  mint operator * (mint o) {return mint((v * o.v) % MOD);}
  mint operator ^ (ll e) {
    mint r{1};
    for (mint p = *this; e; e >>= 1, p = p * p)
      if (e & 1)
        r = r * p;
    return r;
  }
  mint inverse() {return (*this) ^ (MOD - 2);}
  mint operator / (mint o) {return (*this) * o.inverse();}
};

const int MAXN = 200000;
mint fac[MAXN + 5];
mint nck(int n, int k){
  return fac[n] / (fac[n - k] * fac[k]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  fac[0] = 1;
  rep(i, 1, MAXN + 1)
    fac[i] = fac[i - 1] * mint{i};
  
  int n, k;
  cin >> n >> k;
  int p = n - k;
  if (p <= 0) {puts("0"); exit(0);}
  mint res{0};
  rep(z, 0, p + 1) {
    mint sgn = (z & 1) ? mint{-1} : mint{1};
    res = res + sgn * nck(p, z) * (mint(p - z) ^ n);
  }
  res = nck(n, p) * res;
  if (p != n) res = res + res;
  cout << res.v << '\n';
}
