// adhoc (constructive-ish?)
// https://codeforces.com/contest/1340/problem/A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vi a(n), pos(n);
    rep(i, 0, n) {
      cin >> a[i]; --a[i];
      pos[a[i]] = i;
    }
    bool feas = true;
    int it = 0;
    vi hit(n);
    while (it < n) {
      int p = pos[it];
      while (it < n and p < n and !hit[p]) {
        feas &= (a[p] == it);
        hit[p] = true;
        p++;
        it++;
      }
      if (!feas) break;
    }
    feas &= accumulate(all(hit), 0LL) == n;
    cout << (feas ? "Yes" : "No") << '\n';
  }
}
