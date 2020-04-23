// combinatorics, overcounting then fixing, modular inverse
// https://atcoder.jp/contests/dp/tasks/dp_y

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const ll mod = 1000000007;
struct Mod {
  ll x;
  Mod(ll xx = 0) : x(xx % mod) {}
  Mod operator+(Mod b) const { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) const { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) const { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) const { return *this * (b ^ (mod - 2)); }
  Mod operator ^ (ll p) const {
    Mod acc{1}, pwr = *this;
    while (p) {
      if (p & 1) acc = acc * pwr;
      pwr = pwr * pwr;
      p /= 2;
    }
    return acc;
  }
};

const int MAXN = 3001;
const int MAXR = 100000;
Mod dp[MAXN + 5];
Mod fac[2 * MAXR + 5];
void precompute(int n) {
  rep(i, 0, n + 1) fac[i] = !i ? 1 : fac[i - 1] * Mod(i);
}
Mod nck(int n, int k) {return fac[n] / (fac[n - k] * fac[k]);}
Mod ways(int dx, int dy){return nck(dx + dy, dy);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c, n;
  cin >> r >> c >> n;
  precompute(r + c);
  vector<ii> a(n);
  trav(i, a) cin >> i.first >> i.second;
  sort(all(a), [](auto u, auto v){return u.first + u.second < v.first + v.second;});
  a.PB({r, c});
  auto precedes = [&](int i, int j){return a[i].first <= a[j].first and a[i].second <= a[j].second;};
  rep(i, 0, sz(a)) {
    dp[i] = ways(a[i].first - 1, a[i].second - 1);
    auto overcnt = Mod{};
    rep(j, 0, sz(a)) {
      if (!precedes(j, i) or i == j) continue;
      auto ways_ij = ways(a[i].first - a[j].first, a[i].second - a[j].second);
      overcnt = overcnt + dp[j] * ways_ij;
    }
    dp[i] = dp[i] - overcnt;
  }
  cout << dp[n].x << '\n';
}
