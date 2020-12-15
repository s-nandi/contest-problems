// longest non-decreasing subsequence, mirroring input to reduce implementation, optimal manhattan path must be optimal at each step (no slack)
// https://open.kattis.com/problems/manhattanmornings
// 2017 Benelux Algorithm Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto

struct edge{int to;};
using graph = vector<vector<edge>>;

template<class I> vi lis(const vector<I>& S) {
  if (S.empty()) return {};
  vi prev(sz(S));
  typedef pair<I, int> p;
  vector<p> res;
  rep(i,0,sz(S)) {
    // change 0 -> i for longest non-decreasing subsequence
    auto it = lower_bound(all(res), p{S[i], i});
    if (it == res.end()) res.emplace_back(), it = res.end()-1;
    *it = {S[i], i};
    prev[i] = it == res.begin() ? 0 : (it-1)->second;
  }
  int L = sz(res), cur = res.back().second;
  vi ans(L);
  while (L--) ans[L] = cur, cur = prev[cur];
  return ans;
}

auto between(auto a, auto b, auto c){return (a <= b and b <= c) or (c <= b and b <= a);}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  vector<pii> a(n);
  trav(i, a) cin >> i.first >> i.second;

  
  if (x1 > x2) // make sure x1 -> x2 is left to right
    swap(x1, x2), swap(y1, y2);

  if (y1 > y2) { // make sure y1 -> y2 is bottom to top
                 // if flipped, reflect everything across the x-axis so we can still compute LIS instead of LD(ecreasing)S
    y1 *= -1, y2 *= -1;
    trav(i, a) i.second *= -1; 
  }
  assert(x1 <= x2 and y1 <= y2); // going from bottom-left to top-right

  vector<pii> b;
  trav(i, a) { // throw out points outside the [x1, x2] x [y1, y2] bounding box
    if (!between(x1, i.first, x2) or !between(y1, i.second, y2)) continue;
    b.PB(i);
  }
  sort(all(b));
  
  vi ys;
  trav(i, b) ys.PB(i.second);
  auto res = sz(lis(ys));
  cout << res << '\n';
}
