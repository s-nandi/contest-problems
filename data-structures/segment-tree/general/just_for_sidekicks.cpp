// segment tree (range sum query, point delta query), keep MAXP independent segment trees to count each gem type separately
// https://open.kattis.com/problems/justforsidekicks

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr int MAXP = 6;

struct ST {
  int s;
  vi v;
  ST() = default;
  ST(int n) : s{n}, v(2 * n) {}
  void update(int p, int delta) {
    v[p += s] += delta;
    for (p >>= 1; p; p >>= 1)
      v[p] = v[2 * p] + v[2 * p + 1];
  }
  auto query(int l, int r) {
    auto acc = 0;
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) acc += v[l];
      if (~r & 1) acc += v[r];
    }
    return acc;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vi value(MAXP);
  trav(i, value) cin >> i;
  string s;
  cin >> s;
  array<ST, MAXP> sts{};
  fill(all(sts), ST(n));
  vi type(n);
  rep(i, 0, n) {
    type[i] = (int)(s[i] - '1');
    sts[type[i]].update(i, 1);
  }

  rep(it, 0, q) {
    int t;
    cin >> t;
    if (t == 1) {
      int k, p;
      cin >> k >> p;
      --k; --p;
      sts[type[k]].update(k, -1);
      type[k] = p;
      sts[type[k]].update(k, 1);
    } else if (t == 2) { 
      int p, val;
      cin >> p >> val;
      value[--p] = val;
    } else { assert(t == 3);
      int l, r;
      cin >> l >> r;
      --l; --r;
      ll acc = 0;
      rep(t, 0, MAXP) {
        auto cnt = sts[t].query(l, r);
        acc += (ll) cnt * value[t];
      }
      cout << acc << '\n';
    }
  }
}
