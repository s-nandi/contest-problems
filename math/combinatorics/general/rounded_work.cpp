// combo (pattern chasing), fractions, cyclic pattern
// https://utipc19.kattis.com/problems/utipc19.roundedwork
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)

ll nchoose2(ll n) {return n * (n + 1) / 2;}

ll contrib(ll n, ll b) {
  auto h = ((b + 1) / 2) - 1;
  if (n <= h) return 0;
  n -= h;
  auto cycles = n / b;
  auto extra = n % b;
  return b * nchoose2(cycles) + (cycles + 1) * extra;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  ld res = 0;
  rep(b, 1, n + 1) {
    auto delta = contrib(n, b); // total contribution from fractions with denominator b
    res += (ld) delta / n / n;
  }
  cout << fixed << setprecision(11) << res << '\n';
}
