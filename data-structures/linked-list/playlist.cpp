// linked list (splicing)
// https://codeforces.com/contest/1483/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;

    list<list<int>> inds;
    rep(i, 0, n) {
      inds.push_back({});
      inds.back().push_back(i);
    }
    auto it = begin(inds);
    auto getnext = [&](auto iter) {
                     auto nit = next(iter);
                     if (nit == end(inds)) nit = begin(inds);
                     return nit;
                   };
    auto canmerge = [&](auto it1, auto it2) {
                      assert(!empty(*it1));
                      assert(!empty(*it2));
                      auto last1 = a[it1 -> back()];
                      auto first2 = a[it2 -> front()];
                      return gcd(last1, first2) != 1;
                    };

    vi removed;
    while (true) {
      auto nit = getnext(it);
      if (canmerge(it, nit)) {
        if (it == nit) break;
        else {
          it -> splice(end(*it), *nit);
          inds.erase(nit);
        }
      } else {
        auto ind = *begin(*nit);
        removed.PB(ind);
        nit -> erase(begin(*nit));
        if (empty(*nit)) {
          inds.erase(nit);
	  if (empty(inds)) break;
          it = getnext(it);
        } else {
          it = nit;
        }
      }
    }
    cout << sz(removed) << " "; trav(i, removed) cout << (i + 1) << " "; cout << '\n';
  }
}
