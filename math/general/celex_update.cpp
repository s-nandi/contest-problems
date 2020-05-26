// adhoc, diff between minimum and maximum path
// https://codeforces.com/contest/1358/problem/C
// note: editorial formula is much simpler

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll sum(ll n){return n * (n + 1) / 2;}
ll sum(ll a, ll b){return sum(b) - sum(a - 1);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    ll x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    auto dx = x2 - x1;
    auto dy = y2 - y1;
    auto diff = abs(dx - dy);
    auto sm = min(dx, dy);
    auto res = sum(sm) + sum(sm - 1) + diff * sm + 1;
    cout << res << '\n';
  }
}
