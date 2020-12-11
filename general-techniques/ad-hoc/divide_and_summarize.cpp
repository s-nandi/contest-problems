// repeated halving implies logarithmic tree height, precompute answers
// https://codeforces.com/contest/1461/problem/D

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

constexpr auto dbg = false;

void solve(auto begin, auto end, auto& possible) {
  if (begin == end) return;
  auto total = accumulate(begin, end, 0LL);
  possible.PB(total);

  auto mn = *begin, mx = *(end - 1);
  auto mid = (mn + mx) / 2;
  auto it = partition(begin, end, [&mid](const auto& val){return val <= mid;});
  if (it != end) solve(begin, it, possible);
  if (it != begin) solve(it, end, possible);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, q;
    cin >> n >> q;
    vi a(n);
    trav(i, a) cin >> i;
    sort(all(a));
    
    vector<ll> possible;
    solve(all(a), possible);
    sort(all(possible));
    rep(it, 0, q) {
      int s;
      cin >> s;
      cout << (binary_search(all(possible), s) ? "Yes" : "No") << '\n';
    }
  }
}
