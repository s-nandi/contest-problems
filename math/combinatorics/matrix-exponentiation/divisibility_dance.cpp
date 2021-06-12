// difference arrays (a+b={v,v,...} <=> diff(a)+diff(b) = {0,0,...}), kmp (find matching rotations w/ dupl. string), dp (abuse symmetry -> linear recurrence)
// https://codeforces.com/gym/102861/problem/D
// 2021 Brazil Subregional

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
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

using istring = basic_string<int>;

vi pi(const auto& s) {
  vi p(sz(s));
  rep(i,1,sz(s)) {
    int g = p[i-1];
    while (g && s[i] != s[g]) g = p[g-1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}

vi match(const auto& s, const auto& pat) {
  const auto sentinel = 1031231234;
  vi p = pi(pat + sentinel + s), res;
  rep(i,sz(p)-sz(s),sz(p))
    if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
  return res;
}

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (b) { ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d; }
  return x = 1, y = 0, a;
}

const ll mod = 1'000'000'007;
struct Mod {
  ll x;
  Mod(ll xx = 0) : x(xx) {}
  Mod operator+(Mod b) const { return Mod((x + b.x) % mod); }
  Mod operator+=(Mod b) {return *this = (*this + b);}
  Mod operator-(Mod b) const { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) const { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) const { return *this * invert(b); }
  Mod invert(Mod a) const {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1); return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) const {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2); r = r * r;
    return e&1 ? *this * r : r;
  }
};

template<class T, int N> struct Matrix {
  typedef Matrix M;
  array<array<T, N>, N> d{};
  M operator*(const M& m) const {
    M a;
    rep(i,0,N) rep(j,0,N)
      rep(k,0,N) a.d[i][j] += d[i][k]*m.d[k][j];
    return a;
  }
  vector<T> operator*(const vector<T>& vec) const {
    vector<T> ret(N);
    rep(i,0,N) rep(j,0,N) ret[i] += d[i][j] * vec[j];
    return ret;
  }
  M operator^(ll p) const {
    assert(p >= 0);
    M a, b(*this);
    rep(i,0,N) a.d[i][i] = 1;
    while (p) {
      if (p&1) a = a*b;
      b = b*b;
      p >>= 1;
    }
    return a;
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;
  istring a(n, 0), b(n, 0);
  trav(i, a) {cin >> i; i %= m;}
  trav(i, b) {cin >> i; i %= m;}

  auto partialdiff = [&](const istring& s) {
                       istring res(sz(s), 0);
                       rep(i, 0, sz(s)) {
                         auto j = i + 1 < sz(s) ? i + 1 : 0;
                         res[i] = (s[j] - s[i] + m) % m;
                       }
                       return res;
                     };
  // can end at each rotation where differences arrays add to {0,0,...} after rotation of A (wlog could rotate B and fix A instead too)
  istring adiff = partialdiff(a);
  istring bdiff = partialdiff(b);
  trav(i, bdiff) {i = (m - i) % m;}
  auto adiff2 = adiff + adiff;
  adiff2.pop_back();
  auto matches = match(adiff2, bdiff);

  /*
   * dp[t][i] = # of ways to make t rotations and end at i
   * 
   * dp[0][0] = 1
   * dp[0][i != 0] = 0
   * 
   * dp[t][i] = sum_{j != i} dp[t - 1][j]
   * 
   * Note that the recurrence and base case are symmetric for all i != 0
   * We can use this symmetry to simplify our state space:
   *
   * dp[t][0] = sum(j != 0) dp[t - 1][j]
   *          = (n - 1) * dp[t - 1][not 0]
   *
   * dp[t][i != 0] = sum(j \notin {0, i}) dp[t - 1][j] + dp[t - 1][0]
   *               = (n - 2) * dp[t - 1][not 0] + dp[t - 1][0]
   *
   * ie. the only relevant states are dp[t][0] and dp[t][not 0]
   * this is a linear recurrence that we can solve in O(lg k) time
   */

  
  auto nmatches = sz(matches);
  auto initmatch = count(all(matches), 0);
  auto noninitmatch = nmatches - initmatch;

  Matrix<Mod, 2> matrix;
  matrix.d[0][0] = Mod{0};
  matrix.d[0][1] = Mod{n - 1};
  matrix.d[1][0] = Mod{1};
  matrix.d[1][1] = Mod{n - 2};

  auto exp = matrix^k;
  vector<Mod> init = {1, 0};
  auto ways = exp * init;
  auto res = ways[0] * Mod{initmatch} + ways[1] * Mod{noninitmatch};
  cout << res.x << '\n';
}
