// constructive (2 consecutive ops insertion-sorts element 'i' to either the front or back), heuristic spamming (why does 191 (better than 2(n-1)) work?)
// https://open.kattis.com/problems/keepitsorted
// 2019 Asia Dahang Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

vector<pii> splitat(vi a, int pos, bool flipped, bool naive) {
  assert(pos >= 0 and pos < sz(a));
  vector<pii> sol;
  auto op = [&](int l, int r) {
              assert(l >= 0 and r < sz(a));
              if (l < r) {
                if (!sol.empty() and sol.back() == pii{l, r}) sol.pop_back(); // required for some case? which...
                else sol.PB({l, r});
                reverse(begin(a) + l, begin(a) + r + 1);
              }
            };

  auto from_front = [&](int first, int last) { // [first..last] is already sorted
                      for (int i = last + 1; i < sz(a); i++) { // know that [first .. last .. i - 1] is already sorted
                        int it = -1;
                        for (int k = first; k < i; k++) {
                          if (a[k] > a[i]) {
                            it = k;
                            break;
                          }
                        }
                        if (it != -1) {
                          op(it, i - 1);
                          op(it, i);
                        }
                        assert(is_sorted(begin(a) + first, begin(a) + i + 1));
                      }
                    };

  auto from_back = [&](int first, int last) { // [first..last] is already sorted
                     for (int i = first - 1; i >= 0; i--) { // know that [i+1 ..first .. last] is already sorted
                       int it = -1;
                       for (int k = last; k > i; k--) {
                         if (a[k] < a[i]) {
                           it = k;
                           break;
                         }
                       }
                       if (it != -1) {
                         op(i + 1, it);
                         op(i, it);
                       }
                       assert(is_sorted(begin(a) + i, begin(a) + last + 1));
                     }
                   };

  if (naive and !flipped) {
    from_front(0, 0);
  } else if (naive and flipped) {
    from_back(sz(a) - 1, sz(a) - 1);
  } else if (!flipped) { // necessary just for the last test case...
    from_front(pos, pos);
    from_back(pos, sz(a) - 1);
  } else {
    from_back(pos, pos);
    from_front(0, pos);
  }
  return sol;
}

auto print(const auto& sol) {
  cout << sz(sol) << '\n';
  for (const auto& [l, r]: sol) {
    cout << (l + 1) << " " << (r + 1) << '\n';
  }
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  
  vi a(n);
  trav(i, a) {cin >> i; --i;}

  auto best = splitat(a, 0, false, false);
  rep(flipped, 0, 2) {
    auto possible = splitat(a, 0, flipped, true); // try naive flipped/unflipped, split point doesn't matter
    if (sz(possible) < sz(best)) best = move(possible);
  }
  rep(it, 0, sz(a)) {
    rep(flipped, 0, 2) {
      auto possible = splitat(a, it, flipped, false); // try splitting at 'it' flipped/unflipped
      if (sz(possible) < sz(best)) best = move(possible);
    }
  }
  assert(sz(best) <= 2 * (n - 1));
  assert(sz(best) <= 191);
  print(best);
}
