// greedy (MSB first, end chunk asap), non-trivial proof
// https://open.kattis.com/problems/bitwise
// 2018 Singapore Regional
// Note: Proving that "if you try ending with X, trying to end with some submask(x) is redundant"
//       is a good exercise

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()

const int MAXP = 29;

auto submask_of(int i, int j) {
  return (i & j) == i;
}

auto check(auto a, int bm) {
  int checked = 0;
  trav(i, a) i &= bm;
  int mx = 0;
  rep(i, 0, sz(a)) {
    if (submask_of(a[i], checked)) continue;
    checked |= a[i];
    int curr = 0, cnt = 0;
    rep(j, 0, sz(a)) {
      int it = (i + 1 + j) % sz(a);
      curr |= a[it];
      if (submask_of(bm, curr)) {
        curr = 0;
        cnt++;
      }
    }
    mx = max(mx, cnt);
  }
  return mx;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vi a(n);
  rep(i, 0, n) {
    cin >> a[i];
  }

  int target = 0;
  for (int i = MAXP; i >= 0; i--) {
    if (check(a, target | (1 << i)) >= k) {
      target |= (1 << i);
    }
  }
  cout << target << '\n';
}
