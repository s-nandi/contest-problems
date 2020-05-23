// bitmask, normalizing
// https://codesprintla20-individual.kattis.com/problems/codesprintla20.braceletmaking

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

auto normalize(vi v) {
  auto res = v;
  int n = sz(v);
  rep(i, 0, n) {
    rotate(begin(v), begin(v) + 1, end(v));
    rep(t, 0, 2) {
      res = min(res, v);
      reverse(all(v));
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int b, g;
  cin >> b >> g;
  int n = b + g;
  vector<vi> res;
  rep(bm, 0, 1 << n)  { // blues
    vi chunks;
    rep(i, 0, n) chunks.PB(!!(bm & (1 << i)));
    if (accumulate(all(chunks), 0) != b) continue;
    res.PB(normalize(chunks));
  }
  sort(all(res));
  res.erase(unique(all(res)), end(res));
  cout << sz(res) << '\n';
}
