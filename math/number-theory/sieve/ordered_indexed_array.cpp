// dp, bitset squeezing, sieve
// https://www.codechef.com/HALO2020/problems/INDMOV

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

const int MAXP = 40;
const int MAXN = 1000000;
vi pf[MAXN + 5];
bool cmp[MAXN + 5];
const vi dx{-1, 1};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  rep(i, 2, MAXN + 1) {
    if (cmp[i]) continue;
    pf[i] = {i};
    rep(j, 2, (MAXN / i) + 1) {
      cmp[i * j] = true;
      pf[i * j].PB(i);
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;
    int m;
    cin >> m;
    vector<bitset<MAXP + 1>> moves(n);
    rep(i, 0, n) {
      trav(fac, pf[a[i]]) {
        trav(sgn, dx) {
          auto nx = i + sgn * fac;
          if (nx < 0 or nx >= n) continue;
          moves[i][nx] = true;
        }
      }
    }
    bitset<MAXP + 1> old, curr;
    old[0] = true;
    rep(it, 0, m) {
      rep(i, 0, n) {
        if (old[i]) curr |= moves[i];
      }
      old = curr;
      curr.reset();
    }
    cout << (old[n - 1] ? "YES" : "NO") << '\n';
  }
}
