// reorder summation to be j,i,k, separating sum by bits
// https://codeforces.com/contest/1466/problem/E

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

constexpr auto MAXB = 61;
constexpr auto MOD = 1'000'000'007;

auto add(ll a, ll b){ return (a + b) % MOD; }

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  vector<ll> p2(MAXB);
  rep(i, 0, MAXB) {
    p2[i] = (1LL << i) % MOD;
  }

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<ll> a(n);
    trav(i, a) cin >> i;

    vi cnt(MAXB);
    trav(i, a) {
      rep(bit, 0, MAXB + 1) {
        if (i & (1LL << bit)) cnt[bit]++;
      }
    }
    ll res = 0;
    rep(j, 0, n) {
      ll lhs = 0; // i & j is (1 << bit) * cnt[bit] if j has bit and 0 otherwise
      ll rhs = 0; // j | k is (1 << bit) * n if j has bit and (1 << bit) * cnt[bit] otherwise
      rep(bit, 0, MAXB) {
        auto val = p2[bit];
        if (a[j] & (1LL << bit)) {
          lhs = add(lhs, val * cnt[bit] % MOD);
          rhs = add(rhs, val * n % MOD);
        } else {
          rhs = add(rhs, val * cnt[bit] % MOD);
        }
      }
      auto prod = lhs * rhs % MOD;
      res = add(res, prod);
    }
    cout << res << '\n';
  }
}
