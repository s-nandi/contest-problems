// game theory (proofy, parity argument)
// https://open.kattis.com/problems/irrationaldivision
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

constexpr auto dbg = false;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  if (n & 1 and m & 1) cout << 1 << '\n';
  else if (n & 1 and ~m & 1) {
    if (n > m) cout << 0 << '\n';
    else if (n < m) cout << 2 << '\n';
  } else cout << 0 << '\n';
}
