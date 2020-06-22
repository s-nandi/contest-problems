// constructive, sieve (spf factorization), proofy (modular arith)
// https://codeforces.com/contest/1366/problem/D

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;
 
#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int MAXN = 10000000;
bool cmp[MAXN + 5];
int spf[MAXN + 5];
vi primes;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  rep(i, 2LL, MAXN + 1) {
    if (cmp[i]) continue;
    primes.PB(i);
    spf[i] = i;
    for (auto j = i * i; j <= MAXN; j += i) {
      if (!cmp[j]) spf[j] = i, cmp[j] = true;
    }
  }
 
  int n;
  cin >> n;
  vi s1(n), s2(n);
  rep(i, 0, n) {
    int a;
    cin >> a;
 
    vi factors;
    while (a != 1) {
      int fac = spf[a];
      factors.PB(fac);
      while (a % fac == 0) {
        a /= fac;
      }
    }
 
    ii sol{-1, -1};
    if (sz(factors) >= 2) {
      auto f1 = 1, f2 = 1;
      f1 = factors[0];
      rep(i, 1, sz(factors))
        f2 *= factors[i];
      sol = {f1, f2};
    }
    s1[i] = sol.first;
    s2[i] = sol.second;
  }
  rep(i, 0, n) cout << s1[i] << " "; cout << '\n';
  rep(i, 0, n) cout << s2[i] << " "; cout << '\n';
}
