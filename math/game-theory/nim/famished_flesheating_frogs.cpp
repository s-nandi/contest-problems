// nimber (each odd indexed run of 1 is a pile of stones), FWHT (xor convolution, multiply polynomials with the same length without repeated inverse transforms)
// https://codeforces.com/gym/103059/problem/F

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
constexpr bool dbg = false;
 
struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXP = 23;

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (b) { ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d; }
  return x = 1, y = 0, a;
}

const ll mod = 1'000'000'007;
struct Mod {
  int x;
  Mod(int xx = 0) : x(xx) {}
  Mod operator+(Mod b) { auto res = x + b.x; return Mod(res >= mod ? res - mod : res); }
  Mod operator++(int) { return *this = *this + Mod{1}; }
  Mod operator-(Mod b) { auto res = x - b.x; return Mod(res < 0 ? res + mod : res); }
  Mod operator*(Mod b) { return Mod(((ll) x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod operator/=(Mod b){ return *this = *this / b; }
  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1); return Mod((x + mod) % mod);
  }
};
 
int nimber(const string& s) {
  vi runs1;
  int curr = 0;
  trav(c, s) {
    if (c == '0') {
      runs1.PB(curr);
      curr = 0;
    } else curr++;
  }
  if (curr != 0) runs1.PB(curr);
  int res = 0;
  for (int i = 1; i < sz(runs1); i += 2)
    res ^= runs1[i];
  return res;
}

using Polynomial = vector<Mod>;
void FST(auto& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
        auto &u = a[j], &v = a[j + step]; tie(u, v) = pair(u + v, u - v);
      }
  }
  if (inv) trav(x, a) x /= sz(a);
}
int power2(int n) {
  int res = 0;
  while ((1 << res) < n) res++;
  return res;
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;

  vector<vector<Polynomial>> polys(MAXP);
  rep(it, 0, n) {
    int len; string s;
    cin >> len >> s;
    auto nim1 = nimber(s);
    reverse(all(s));
    auto nim2 = nimber(s);
    
    auto power = power2(max(nim1, nim2) + 1);
    Polynomial p(1 << power);
    p[nim1]++;
    p[nim2]++;
    polys[power].PB(p);
  }

  vi nonempty;
  rep(power, 0, MAXP) if (!empty(polys[power])) nonempty.PB(power);
  
  vector<Polynomial> acc(MAXP);
  trav(power, nonempty) {
    auto& curr = acc[power];
    curr.resize(sz(polys[power][0]));
    curr[0] = 1;
    FST(curr, 0);
    trav(poly, polys[power]) {
      FST(poly, 0);
      rep(k, 0, sz(poly)) curr[k] = curr[k] * poly[k];
    }
  }
  Polynomial res = acc[nonempty[0]];
  rep(it, 1, sz(nonempty)) {
    auto& curr = acc[nonempty[it]];
    FST(res, 1);
    while (sz(res) < sz(curr)) res.PB(0);
    FST(res, 0);
    rep(k, 0, sz(curr)) res[k] = res[k] * curr[k];
  }
  FST(res, 1);
  cout << res[0].x << '\n';
}
