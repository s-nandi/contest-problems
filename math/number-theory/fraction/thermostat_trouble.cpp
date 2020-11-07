// fraction class, math (temperature conversion)
// https://open.kattis.com/contests/iitu7b/problems/thermostat

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

constexpr auto dbg = false;

struct fraction {
  ll num{0}, denom{1};
  fraction(ll val) : fraction(val, 1) {}
  fraction(ll num_, ll denom_) : num{num_}, denom{denom_} {
    auto g = gcd(abs(num), abs(denom));
    num /= g, denom /= g;
    if (denom < 0) num = -num, denom = -denom;
  }
  fraction operator + (const auto& o) const {
    return fraction{num * o.denom + denom * o.num, denom * o.denom};
  }
  fraction operator - (const auto& o) const {
    return (*this) + fraction{-o.num, o.denom};
  }
  fraction operator * (const auto& o) const {
    return fraction{num * o.num, denom * o.denom};
  }
  fraction operator / (const auto& o) const {
    return (*this) * fraction{o.denom, o.num};
  }
};

ostream& operator << (ostream& os, const fraction& f) {
  return os << f.num << '/' << f.denom;
}

fraction conv_to_celcius(ll a, ll b, fraction v) {
  return (v - fraction(a)) * fraction(100, b - a);
}

fraction conv_from_celcius(ll a, ll b, auto v) {
  return v * fraction(b - a, 100) + fraction(a);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vector<pair<ll, ll>> ab(n);
  rep(i, 0, n) cin >> ab[i].first >> ab[i].second;
  
  rep(it, 0, q) {
    int i, j; ll val;
    cin >> i >> j >> val;
    --i; --j;
    auto in_celcius = conv_to_celcius(ab[i].first, ab[i].second, fraction(val));
    auto res = conv_from_celcius(ab[j].first, ab[j].second, in_celcius);
    cout << res << '\n';
  }
}
