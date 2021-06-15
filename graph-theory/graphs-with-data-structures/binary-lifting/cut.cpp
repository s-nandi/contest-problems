// binary lifting (cover range w/ min number of jumps), prod == lcm on range if pairwise gcd == 1, factorization
// https://codeforces.com/contest/1516/problem/D

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

const int MAXA = 100'000 + 5;
const int MAXL = 17;

auto getfactors(int val) {
  vi res;
  for (int fac = 2; fac * fac <= val; fac++) {
    if (val % fac == 0) {
      res.PB(fac);
      while (val % fac == 0) val /= fac;
    }
  }
  if (val != 1) res.PB(val);
  return res;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vi a(n);
  trav(i, a) cin >> i;
  vector<pii> qs(q);
  trav(qry, qs) trav(c, qry) {cin >> c; --c;}

  vector<vi> factors(n);
  vector<vi> positions(MAXA);
  rep(i, 0, n) {
    trav(fac, getfactors(a[i])) {
      factors[i].PB(fac);
      positions[fac].PB(i);
    }
  }
  trav(pos, positions) pos.PB(n);
  
  vi upto(n + 1);
  upto[n] = n;
  for (int i = n - 1; i >= 0; i--) {
    upto[i] = n;
    for (const auto& fac: factors[i]) {
      int nxt = *upper_bound(all(positions[fac]), i);
      upto[i] = min(nxt, upto[i]);
    }
    if (i + 1 < n) upto[i] = min(upto[i], upto[i + 1]);
  }

  auto jmp = vector(MAXL + 1, vi(n + 1));
  jmp[0] = upto;
  rep(lev, 1, MAXL + 1) {
    rep(i, 0, n + 1) {
      jmp[lev][i] = jmp[lev - 1][jmp[lev - 1][i]];
    }
  }

  for (const auto& [lo, hi]: qs) {
    int curr = lo;
    int dist = 0;
    for (int lev = MAXL; lev >= 0; lev--) {
      if (jmp[lev][curr] <= hi) {
        dist += (1 << lev);
        curr = jmp[lev][curr];
      }
    }
    cout << (dist + 1) << '\n';
  }  
}
