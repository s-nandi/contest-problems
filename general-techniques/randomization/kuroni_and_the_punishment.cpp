// randomization, sieve (factorization), at least 1/2 elements move <= 1 steps => trying factors of a[i],a[i]-1,a[i]+1 gives 1/2 chance of finding optimal
// https://codeforces.com/contest/1305/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)
#define PB push_back

const int MAXS = 1'000'000;
bool comp[MAXS + 1];
vi primes;

const int ITERS = 40;
ll operations(const auto& a, auto p) {
  ll res = 0;
  trav(i, a) {
    auto best = p;
    auto target1 = (i / p) * p;
    auto target2 = (i / p + 1) * p;
    if (target1 > 0) best = min(best, i - target1);
    best = min(best, target2 - i);
    res += best;
  }
  return res;
}

auto primefactors(auto i) {
  vector<ll> res;
  trav(p, primes) {
    if (i % p == 0) {
      res.PB(p);
      while (i % p == 0) i /= p;
    }
  }
  if (i != 1) res.PB(i);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  rep(i, 2LL, MAXS + 1) {
    if (comp[i]) continue;
    primes.PB(i);
    for (auto j = i * i; j <= MAXS; j += i)
      comp[j] = true;
  }
  assert(sz(primes) <= 5e5);

  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;

  int best = n;
  unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  mt19937 gen{seed};
  uniform_int_distribution<> dist(0, n - 1);
  rep(it, 0, ITERS) {
    auto i = dist(gen);
    rep(delta, -1, 2) {
      auto val = a[i] + delta;
      if (val <= 1) continue;
      trav(fac, primefactors(val)) {
        best = min<ll>(best, operations(a, fac));
      }
    }
  }
  cout << best << '\n';
}
