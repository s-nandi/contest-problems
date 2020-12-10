// coloring argument, pigeonhole principle (exists 2 entries from diff rows/columns on 2x3 grid w/ sum <= floor(total / 3); prove by covering matrix w/ 3 such pairs)
// https://codeforces.com/contest/1450/problem/C2

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

constexpr auto dbg = true;

const int INF = 1031231234;

int indexof(char c){return c == 'X' ? 0 : 1;}
char other(char c){assert(c == 'X' or c == 'O'); return c == 'X' ? 'O' : 'X';}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    auto grid = vector(n, string{});
    trav(row, grid) cin >> row;

    auto cnt = vector(3, vi(2));
    rep(i, 0, n) rep(j, 0, n) {
      if (grid[i][j] == '.') continue;
      auto parity = (i + j) % 3;
      auto ch_ind = indexof(grid[i][j]);
      cnt[parity][ch_ind]++;
    }

    auto best = array{-1, -1};
    auto mincost = INF;
    rep(i, 0, 3) rep(j, 0, 3) if (i != j) {
      auto possible = cnt[i][0] + cnt[j][1];
      if (possible < mincost) {
        best = {i, j};
        mincost = possible;
      }
    }

    rep(i, 0, n) rep(j, 0, n) {
      if (grid[i][j] == '.') continue;
      auto parity = (i + j) % 3;
      auto ch_ind = indexof(grid[i][j]);
      if (best[ch_ind] == parity) grid[i][j] = other(grid[i][j]);
    }
    trav(row, grid) cout << row << '\n';
  }
}
