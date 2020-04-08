// prefix sums (venice technique), # of subarrays avoiding predetermined ranges
// https://codeforces.com/contest/1333/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define PB push_back

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  map<ll, vi> positions;
  vector<ll> ps(n + 1);
  rep(i, 0, n) {
    cin >> a[i];
    ps[i + 1] = a[i] + ps[i];
    positions[ps[i + 1]].push_back(i);
  }
  vector<pair<int, int>> inv;
  rep(i, 0, n) {
    auto& pos = positions[ps[i]];
    auto it = lower_bound(all(pos), i);
    auto j = it != end(pos) ? *it : n;
    inv.PB({i, j});
  }
  map<int, int> byl;
  for (auto [a, b]: inv) {
    if (!byl.count(a)) byl[a] = b;
    else byl[a] = min(byl[a], b);
  }
  multiset<int> rs;
  for (auto [l, r]: byl) rs.insert(r);
  ll sol = 0;
  rep(i, 0, n) {
    auto upto = rs.empty() ? n : *rs.begin();
    sol += upto - i;
    rs.erase(rs.find(byl[i]));
  }
  cout << sol << '\n';
}
