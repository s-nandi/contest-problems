// sliding window, prefix sums, doubling interval trick, window size s.t. all windows have > 0 sum
// https://codeforces.com/contest/1358/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(a) (int)size(a)
#define PB push_back

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  int ch = (n + 1) / 2;
  int fh = n / 2;
  vector<ll> a(ch);
  ll tot = 0;
  trav(i, a) {cin >> i; tot += i;}
  ll x;
  cin >> x;
  trav(i, a) i = x - i;
  auto psum = a;
  partial_sum(all(a), begin(psum));
  auto pmin = psum;
  auto minner = [](auto a, auto b){return min(a, b);};
  partial_sum(all(psum), begin(pmin), minner);
  reverse(all(pmin));
  rep(k, ch, n + 1) {
    ll s = tot + (k - ch) * x;
    auto worst = k - fh < sz(pmin) ? pmin[k - fh] : 0;
    if (s > 0 and s + worst > 0) {
      cout << k << '\n';
      exit(0);
    }
  }
  cout << -1 << '\n';
}
