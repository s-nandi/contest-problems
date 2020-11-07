// crt (wrapping around modulo lcm(n, m) to satisfy geq constraints)
// https://open.kattis.com/problems/candydistribution
// 2012 German Subregional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const ll MAXBAG = 1'000'000'000;

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (b) { ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d; }
  return x = 1, y = 0, a;
}

optional<ll> crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  if(!((a - b) % g == 0)) return nullopt;
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m*n/g : x;
}

auto ceildiv(auto a, auto b){return (a + b - 1) / b;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    ll k, c;
    cin >> k >> c;

    auto got = crt(0, c, 1, k);
    if (!got) cout << "IMPOSSIBLE" << '\n';
    else {
      auto res = *got;
      // # of wraps around modulo lcm(c, k) needed to satisfy x > 0 (ie x >= 1), since then res = k * x + 1 => res >= k + 1
      auto need = max(0LL, (k + 1) - res); 
      res += ceildiv(need, lcm(c, k)) * lcm(c, k);

      auto bags = res / c;
      if (bags > MAXBAG) cout << "IMPOSSIBLE" << '\n';
      else cout << bags << '\n';
    }
  }
}
