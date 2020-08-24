// constructive, invariant maintance (length of remaining segments >= # of remaining uncovered cells), greedy (cover cells from left to right, slide segments as far left as possible while still covering every cell)
// https://codeforces.com/contest/1329/problem/A

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

auto upto(auto last_covered, auto pos, auto len) {
  return max(last_covered, pos + len - 1);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  vector<ll> a(m);
  trav(i, a) cin >> i;

  auto total_len = accumulate(all(a), 0LL);
  auto num_colors = m;
  if (!(total_len >= n and n >= num_colors)) cout << -1 << '\n';
  else {
    auto last_covered = -1LL;
    auto pos = 0LL;
    vi sol;
    trav(len, a) {
      total_len -= len;
      num_colors--;
      while (true) { // invariant: total_len >= # uncovered cells
                     // slide only as far right as necessary to maintain invariant
                     // avoids going out of bounds as much as possible
        
        if (pos == last_covered + 1) break; // cannot slide more to the right without creating a hole
        auto uncovered = max(0LL, (n - 1) - upto(last_covered, pos, len));
        if (total_len >= uncovered) break; // maintain invariant
                                          
        pos++;
      }
      sol.PB(pos);
      last_covered = upto(last_covered, pos, len);
      pos++;
    }
    if (last_covered >= n) cout << -1 << '\n'; // check to see if forced to go out of bounds
    else {trav(i, sol) cout << (i + 1) << " "; cout << '\n';}
  }
}
