// dp (kadane), calculate best delta from initial value, casework (subarray starts at even/odd index)
// https://codeforces.com/contest/1373/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

void maxx(auto& a, auto b) {a = max(a, b);}

ll best(const vi& a) {
  int n = sz(a);
  vector<ll> dp(n + 1);
  rep(i, 0, n) {
    maxx(dp[i + 1], max(dp[i], 0LL) + a[i]);
  }
  return *max_element(all(dp));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;

    ll base = 0;
    rep(i, 0, n) {
      if (~i & 1)
        base += a[i];
    }
    
    vi odds, evens;
    rep(i, 0, n - 1) {
      if (i & 1) {
        odds.PB(a[i] - a[i + 1]);
      } else {
        evens.PB(a[i + 1] - a[i]);
      }
    }
    auto possible1 = best(odds);
    auto possible2 = best(evens);
    auto res = base + max({0LL, possible1, possible2});
    cout << res << '\n';
  }
}
