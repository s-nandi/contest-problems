// 2 pointer, fix element whose contiguous block we are maximizing
// https://utipc20s.kattis.com/problems/utipc20s.coloredsquares
// 2020 UT Spring Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()
#define PB push_back

int getbest(const auto& pos, int k) {
  int best = 0;
  int n = sz(pos);
  for (int l = 0, r = 0; l < n; l++) {
    while (r < n and (pos[r] - pos[l] + 1) - (r - l + 1) <= k)
      r++;
    best = max(best, r - l);
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, c, k;
  cin >> n >> c >> k;
  vi a(n);
  vector<vi> pos(c);
  rep(i, 0, n) {
    cin >> a[i];
    --a[i];
    pos[a[i]].PB(i);
  }
  int best = 0;
  rep(i, 0, c) {
    auto feas = getbest(pos[i], k);
    best = max(best, feas);
  }
  cout << best << '\n';
}
