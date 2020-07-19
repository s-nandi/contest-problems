// number theory, greedy (find x,y in [l, r] s.t. x - y = diff => x can be either l or r)
// https://codeforces.com/contest/1379/problem/B

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using ii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

vector<ll> withdiff(ll diff, ll l, ll r) {
  if (r - diff <= r and r - diff >= l) {
    return {r, r - diff};
  } else if (l - diff <= r and l - diff >= l) {
    return {l, l - diff};
  } else {
    assert(false);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    ll l, r, m;
    cin >> l >> r >> m;

    ll min_delta = l - r;
    ll max_delta = r - l;

    vector<ll> res{};
    rep(a, l, r + 1) {
      auto rem = m % a;
      auto lo = m - rem;
      auto hi = m + a - rem;
      for(auto target: vector{lo, hi}) {
        auto delta = m - target;
        if (delta <= max_delta and delta >= min_delta and target >= l) {
          assert(target % a == 0);
          auto n = target / a;
          assert(n >= 1);
          auto got = withdiff(delta, l, r);
          res = {a, got[0], got[1]};
          assert(n * res[0] + res[1] - res[2] == m);
        }
      }
      if (!empty(res)) break;
    }
    trav(i, res) cout << i << " "; cout << '\n';
  }

}
