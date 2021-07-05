// constructive (recursive), snake path, proofy
// https://open.kattis.com/problems/bells
// 2015 Nordic Subregional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

vector<vi> solve(int n) {
  if (n == 1) {return {{1}}; }
  auto base = solve(n - 1);
  auto res = vector<vi>{};
  rep(i, 0, sz(base)) rep(it, 0, n) {
    auto from_front = i & 1;
    auto& curr = res.emplace_back(base[i]);
    auto pos = from_front ? it : n - 1 - it;
    curr.insert(begin(curr) + pos, n);
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  auto res = solve(n);
  trav(row, res) {
    trav(elem, row) cout << elem << " "; cout << '\n';
  }
}
