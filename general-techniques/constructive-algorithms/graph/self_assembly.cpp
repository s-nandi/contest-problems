// constructive (can always go up/right => intersections non-issue), directed cycle finding, connect side[i] to inv(side[j]) for i != j, 1 <= i,j <= 4
// https://codeforces.com/gym/101208/problem/A
// 2013 World Finals

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

auto parse(const string& s) {
  array<pii, 4> res{};
  rep(i, 0, 4) {
    if (s[2 * i] == '0') res[i] = {-1, -1};
    else {
      res[i].first = s[2 * i] - 'A';
      res[i].second = s[2 * i + 1] == '+';
    }
  }
  return res;
}

bool hascycle(const auto& g, int i, auto& vis) {
  if (vis[i] == 1) return true;
  if (vis[i] == 2) return false;
  vis[i] = 1;
  trav(e, g[i])
    if (hascycle(g, e.to, vis)) return true;
  vis[i] = 2;
  return false;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<array<pii, 4>> a(n);
  rep(i, 0, n) {
    string s;
    cin >> s;
    a[i] = parse(s);
  }

  const int nn = 2 * 26;
  auto indexof = [&](const pii& v) {
                   const auto& [i, sign] = v;
                   return i < 0 ? -1 : 2 * i + sign;
                 };

  graph g(nn);
  rep(i, 0, n) {
    rep(s, 0, 4) rep(ns, 0, 4) if (s != ns) {
      auto from = indexof(a[i][s]);
      auto to = indexof(a[i][ns]);
      if (from >= 0 and to >= 0)
        g[from].PB({to ^ 1});
    }
  }
  vi vis(nn);
  bool feas = false;
  rep(i, 0, nn) feas |= hascycle(g, i, vis);
  cout << (feas ? "unbounded" : "bounded") << '\n';
}
