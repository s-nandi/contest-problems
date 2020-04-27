// prefix sums, invariant (only merging blocks with endpoints changes coefficient value)
// https://www.hackerrank.com/contests/hacktheinterview3/challenges/flipped-beauty

#include <bits/stdc++.h>
using namespace std;

#define int long long

using ll = long long;
using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

int solve(auto& blocks, int p) {
  auto psum = vector<ll>(sz(blocks));
  partial_sum(all(blocks), begin(psum));
  trav(elem, psum)
    if (elem <= 0)
      assert(false);
  auto sum = [&](int i, int j){return i ? psum.at(j) - psum.at(i - 1) : psum.at(j);};
  auto best = psum.back();
  rep(fr, 0, p + 1) {
    auto bk = p - fr;
    int left = 2 * fr, right = sz(blocks) - 1 - 2 * bk;
    auto possible = sum(left, right);
    best = min(best, possible);
  }
  assert(p == 0 or psum.back() != best);
  return best;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, p;
  cin >> n >> p;
  string s;
  cin >> s;
  s += '?';

  vi blocks;
  int ppos = 0;
  rep(i, 0, sz(s)) {
    if (s[i] != s[ppos]) {
      blocks.PB(i - ppos);
      ppos = i;
    }
  }
  assert(accumulate(all(blocks), 0LL) == sz(s) - 1);
  vi nblocks;
  rep(i, 1, sz(blocks) - 1)
    nblocks.PB(blocks.at(i));
  blocks = nblocks;
  if (blocks.empty()) {
    cout << 0 << '\n';
    exit(0);
  }
  if (2 * p >= sz(blocks)) {
    cout << 0 << '\n';
    exit(0);
  } 
  auto best = solve(blocks, p);
  if (sz(blocks) >= 3 and p > 0) {
    blocks.erase(begin(blocks));
    blocks.erase(prev(end(blocks)));
    auto best2 = solve(blocks, p - 1);
    best = min(best, best2);
  }
  cout << best << '\n';
}
