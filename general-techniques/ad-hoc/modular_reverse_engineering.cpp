// basic math, fix denominator to find smallest numerator
// https://utipc20s.kattis.com/problems/utipc20s.modularreverseengineering
// 2020 UT Spring Programming Contest

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll v, x, m;
  cin >> v >> x >> m;
  pair<int, int> best{m + 1, 0};
  rep(q, 0LL, m) {
    auto p = q * v % m;
    if (q * x <= p and p < q * (x + 1))
      best = min(best, {p, q});
  }
  if (best.first > m)
    cout << -1 << '\n';
  else
    cout << best.first << " " << best.second << '\n';
}
