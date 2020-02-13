// dfs, mirrors on grid, observing lack of cycles in traversable section of graph
// https://nena19.kattis.com/problems/protectingthecollection
// 2019 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)x.size()

auto dx = vector{0, -1, 0, 1};
auto dy = vector{-1, 0, 1, 0};

auto fwd = vector{3, 2, 1, 0};
auto bck = vector{1, 0, 3, 2};

auto new_dir(int dir, char c) {
  if (c == '.') {
    return dir;
  } else if (c == '/') {
    return fwd[dir];
  } else if (c == '\\') {
    return bck[dir];
  } else {
    assert(false);
  }
}

auto in_bounds(int x, int y, int n) {
  return x >= 0 and y >= 0 and x < n and y < n;
}

constexpr auto MAXN = 2000 + 5;

int visited1[MAXN + 5][MAXN + 5][4];
int visited2[MAXN + 5][MAXN + 5][4];

auto dfs(int i, int j, int dir, auto& vis, const auto& grid, int turn) {
  if (vis[i][j][dir] & (1 << turn)) return;
  vis[i][j][dir] |= (1 << turn);

  auto ndir = new_dir(dir, grid[i][j]);
  auto nx = i + dx[ndir];
  auto ny = j + dy[ndir];
  if (!in_bounds(nx, ny, sz(grid))) return;
  else {
    dfs(nx, ny, ndir, vis, grid, turn);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, c, r;
  cin >> n >> c >> r;
  --c, --r;
  auto grid = vector(n, vector<char>(n));
  trav(row, grid) {
    trav(elem, row) {
      cin >> elem;
    }
  }

  auto visited = vector(n, vector(n, vector<int>(4)));

  dfs(0, c, 3, visited, grid, 0); // dfs from init
  dfs(r, n - 1, 0, visited, grid, 1); // dfs from end
  auto feas = false;
  rep(i, 0, n) {
    rep(j, 0, n) {
      if (grid[i][j] != '.') continue;
      auto vis_front = false, vis_back = false;
      rep(k, 0, 4) {
	vis_front |= (visited[i][j][k] & (1 << 0)) != 0;
	vis_back |= (visited[i][j][k] & (1 << 1)) != 0;
      }
      feas |= (vis_front && vis_back);
    }
  }
  cout << (feas ? "YES" : "NO") << '\n';
}
