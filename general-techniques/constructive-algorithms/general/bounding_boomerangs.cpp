// constructive, greedy, working backwards (right to left), if a[i] == 2 and A[r][i]=A[r][j]=X then a[j] = 1 (look at subpath of the paths that 2's and 3's trace)
// https://codeforces.com/contest/1428/problem/D

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

struct edge{int to;};
using graph = vector<vector<edge>>;

void failure() {
  cout << -1 << '\n';
  exit(0);
}

auto poll(auto& cont) { // can return an arbitrary element in cont
  auto e = cont.back(); cont.pop_back();
  return e;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  vector<pii> res;
  array<vector<pii>, 4> topleft{}; // tracks the top-left X of a 3 (L shape), 2 (horizontal line), 1 (single point)

  // In general, the element at column i lays claim to row (n - 1 - i),
  // except for 2's, which must match with a 1 to their right (the 2's row is left unused)
  // Also, 3's must anchor onto a topleft corner that is to their right (the corner will automatically be below them by construction)
  auto add1 = [&](int r, int c) {
                res.PB({r, c});
                topleft[1].PB({r, c});
              };
  auto add2 = [&](int r, int c, int c2) {
                assert(c < c2);
                res.PB({r, c});
                topleft[2].PB({r, c});
              };
  auto add3 = [&](int r, int c, int r2, int c2) {
                assert(r > r2 and c < c2);
                res.PB({r, c});
                res.PB({r, c2});
                topleft[3].PB({r, c});
              };
  
  for (int i = n - 1; i >= 0; i--) {
    switch(a[i]) {
    case 3: {
      bool matched = false;
      for (int t = 3; t >= 1; t--) { // must try matching with 3/2's first, since 2's NEED 1's -> using a 1 when a 2/3 would do is suboptimal
        if (empty(topleft[t])) continue;
        auto [r2, c2] = poll(topleft[t]);
        add3(n - 1 - i, i, r2, c2);
        matched = true;
        break;
      }
      if (!matched) failure();
      break;
    }
    case 2: {
      if (empty(topleft[1])) failure();
      auto [r, c2] = poll(topleft[1]);
      add2(r, i, c2);
      break;
    }
    case 1: {
      add1(n - 1 - i, i);
      break;
    }
    }
  }
  cout << sz(res) << '\n';
  trav(e, res) cout << (n - e.first) << " " << (e.second + 1) << '\n';
}
