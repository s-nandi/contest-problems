// two pointers, symmetry
// https://codesprintla20-team.kattis.com/problems/codesprintla20.greedylandlords

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

ll calc(const auto& a, const auto& earliest) {
  int n = sz(a);
  ll acc = 0;
  ll best = 0;
  for (int l = 0, r = 0; l < n; l++) {
    while (r < n and r - l <= earliest[r]) {
      acc += a[r];
      r++;
    }
    best = max(best, acc);
    acc -= a[l];
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;

  vi earliest(n);
  iota(all(earliest), 0);
  rep(i, 0, n) {
    earliest[i] = min(earliest[i], n - 1 - i);
  }
  auto b1 = calc(a, earliest);
  reverse(all(a));
  auto b2 = calc(a, earliest);
  auto res = max(b1, b2);
  cout << res << '\n';
}
