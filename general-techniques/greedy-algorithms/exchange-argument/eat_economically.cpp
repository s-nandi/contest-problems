// exchange argument, min sum of 2 * k (k in 0..n) elems from n pairs without taking 2 elements from same pair
// https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/E
// 2020 NAPC -2

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const ll INF = 1e16;
auto maxx(auto& a, auto b) {
  if (a < b) {a = b; return true;}
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  n *= 2;
  vi a(n), b(n), d(n);
  rep(i, 0, n) {
    cin >> a[i] >> b[i];
    d[i] = a[i] - b[i];
  }
  auto dcmp = [&](int i, int j){return tie(d[i], i) < tie(d[j], j);};
  auto dcmpr = [&](int i, int j){return tie(d[i], i) > tie(d[j], j);};
  auto acmp = [&](int i, int j){return tie(a[i], i) > tie(a[j], j);};
  auto bcmp = [&](int i, int j){return tie(b[i], i) > tie(b[j], j);};
  set<int, decltype(dcmpr)> a_diff(dcmpr); // so front of set corresponds to partition
  set<int, decltype(dcmp)> b_diff(dcmp);   // between a and b
  set<int, decltype(acmp)> a_mag(acmp);
  set<int, decltype(bcmp)> b_mag(bcmp);
  auto apush = [&](const auto& v){a_mag.insert(v); a_diff.insert(v);};
  auto bpush = [&](const auto& v){b_mag.insert(v); b_diff.insert(v);};
  auto apoll = [&](auto& s) {
                 auto res = *begin(s);
                 assert(a_mag.erase(res) > 0);
                 assert(a_diff.erase(res) > 0);
                 return res;
               };
  auto bpoll = [&](auto& s) {
                 auto res = *begin(s);
                 assert(b_mag.erase(res) > 0);
                 assert(b_diff.erase(res) > 0);
                 return res;
               };
  vi indices(n);
  iota(all(indices), 0);
  sort(all(indices), dcmp);
  auto acc = 0LL;
  rep(i, 0, n) {
    auto ind = indices[i];
    if (i < n / 2) {
      apush(ind);
      acc += a[ind];
    } else {
      bpush(ind);
      acc += b[ind];
    }
  }
  vector<ll> sols(n / 2);
  for (int i = sz(sols) - 1; i >= 0; i--) {
    sols[i] = acc;
    auto best = -INF;
    int option = -1;
    if (!a_mag.empty() and !b_mag.empty()) { // 1 from a & b
      int aind = *begin(a_mag);
      int bind = *begin(b_mag);
      auto possible = (ll) a[aind] + b[bind];
      if (maxx(best, possible)) option = 0;
    }
    if (sz(a_mag) >= 2) { // 2 from a
      auto aind1 = *begin(a_mag);
      auto aind2 = *next(begin(a_mag));
      auto bswap = *begin(b_diff);
      auto possible = (ll) a[aind1] + a[aind2] + b[bswap] - a[bswap];
      if (maxx(best, possible)) option = 1;
    }
    if (sz(b_mag) >= 2) { // 2 from b
      auto bind1 = *begin(b_mag);
      auto bind2 = *next(begin(b_mag));
      auto aswap = *begin(a_diff);
      auto possible = (ll) b[bind1] + b[bind2] + a[aswap] - b[aswap];
      if (maxx(best, possible)) option = 2;
    }
    acc -= best;
    switch (option) {
      int boundary;
    case 0:
      apoll(a_mag);
      bpoll(b_mag);
      break;
    case 1:
      rep(i, 0, 2) apoll(a_mag);
      boundary = bpoll(b_diff);
      apush(boundary);
      break;
    case 2:
      rep(i, 0, 2) bpoll(b_mag);
      boundary = apoll(a_diff);
      bpush(boundary);
      break;
    }
  }
  trav(i, sols) cout << i << '\n';
}
