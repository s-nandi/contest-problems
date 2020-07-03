// combo, binary search (identifying monotonicity was non-trivial), minor num thy
// https://codeforces.com/contest/1371/problem/E2

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

bool works(int init, const vi& vals, const vi& cnts, int p) {  
  int ngood = 0;
  auto have = init;
  int it = 0;
  while (it < sz(vals) and have >= vals[it]) {
    ngood += cnts[it];
    it++;
  }
  while (ngood > 0) {
    if (ngood % p == 0) return false;
    ngood--;
    have++;
    while (it < sz(vals) and have >= vals[it]) {
      ngood += cnts[it];
      it++;
    }
  }
  return it == sz(vals);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, p;
  cin >> n >> p;
  vi a(n);
  trav(i, a) cin >> i;

  map<int, int> freq;
  trav(i, a) freq[i]++;

  vi vals, cnts;
  for (auto [val, cnt]: freq) vals.PB(val), cnts.PB(cnt);

  // needed will be the min # of starting candies to satisfy the >= a[i] constraints
  int needed = *min_element(all(a)); 
  int behind = 0;
  rep(i, 0, sz(vals)) {
    if (vals[i] > needed + behind) {
      needed = vals[i] - behind;
    }
    behind += cnts[i];
  }

  // since the # of ways is (cnt_1 * (cnt_1 - 1) * ... * (cnt_1 + cnt_2 - k) ... * (sum cnt - m) * (sum cnt - m - 1) * ...)
  // adding 1 to the initial # of candies, just shifts all the terms up by 1 => the function f(x) % p == 0 is monotonic,
  // since once any of the terms is >= p, the product is divisible by p, and shifting up merely preserves this property
  // and if all of the terms are < p, the product is not divisible by p
  //
  // so we can binary search on the maximum # of up-shifts s.t. the product is not divisible by p
  int highest = needed - 1;
  int lo = needed, hi = *max_element(all(a)) + 1;
  while (lo <= hi) {
    auto mid = lo + (hi - lo) / 2;
    auto feas = works(mid, vals, cnts, p);
    if (feas) {
      highest = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  vi good;
  rep(i, needed, highest + 1) {
    good.PB(i);
  }
  cout << sz(good) << '\n';
  trav(i, good) cout << i << " "; cout << '\n';
}
