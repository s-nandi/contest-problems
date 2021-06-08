// dfs (expand grid incrementally)
// https://codeforces.com/gym/102021 (problem J)
// 2018 German Collegiate Programming Contest

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};

void failure() {
  cout << "impossible" << '\n';
  exit(0);
}

int get_other(const vi& v, int excl) {
  assert(sz(v) == 2);
  return v[0] ^ v[1] ^ excl;
}

void add_col(auto& g, int def = 0) {
  trav(row, g) row.PB(def);
}

void add_row(auto& g, int def = 0) {
  auto cols = sz(g[0]);
  g.PB(vi(cols, def));
}

void printstate(const auto& grid, const auto& pieces, int i, int j) {
  cout << "Current state: " << endl;
  rep(i, 0, sz(grid)) {
    rep(j, 0, sz(grid[0])) {
      auto ind = grid[i][j];
      cout << (ind+1) << " (";
      rep(k, 0, 4) {cout << pieces[ind][k]; if (k + 1 < 4) cout << '/';}
      cout << ") ";
    }
    cout << '\n';
  }
  cout << "At " << i << " " << j << endl;
}

void dfs(auto& grid, auto& vis, auto& pieces, auto& used, const auto& hasside, int i, int j) {
  if constexpr (dbg) printstate(grid, pieces, i, j);
  if (vis[i][j]) return;
  vis[i][j] = true;
  const auto curr = grid[i][j];

  rep(k, 0, 4) {
    auto ed = pieces[curr][k];
    if (ed == 0) continue;
    auto nx = i + dx[k];
    auto ny = j + dy[k];

    if (nx < 0 or ny < 0) failure();
    if (nx >= sz(grid)) {
      add_row(grid, -1);
      add_row(vis, false);
      if ((ll) sz(grid) * sz(grid[0]) > sz(pieces)) failure();
    }
    if (ny >= sz(grid[0])) {
      add_col(grid, -1);
      add_col(vis, false);
      if ((ll) sz(grid) * sz(grid[0]) > sz(pieces)) failure();
    }
    
    auto other = get_other(hasside[ed], curr);
    if (grid[nx][ny] == -1) {
      if (used[other]) failure();

      int iter = 0;
      while (pieces[other][k ^ 2] != ed) {
        rotate(begin(pieces[other]), end(pieces[other]) - 1, end(pieces[other]));
        assert(++iter <= 4);
      }
      grid[nx][ny] = other;
      used[other] = true;
    } else {
      if (grid[nx][ny] != other) failure();
      assert(grid[nx][ny] == other);
      if (pieces[other][k ^ 2] != ed) failure();
    }
    
    if (!vis[nx][ny])
      dfs(grid, vis, pieces, used, hasside, nx, ny);
  }
}

template <typename T>
auto find_last_run(T begin, T end, int target) {
  T res = end;
  for (auto it = prev(end); it != end; it = it != begin ? prev(it) : end) {
    if (*it == target) res = it;
    else if (res != end) break;
  }
  return res;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vector<array<int, 4>> pieces(n);
  vector<vi> hasside(4 * (n + 1) + 1);
  vector<vi> byn0(4 + 1);
  rep(i, 0, n) {
    int n0 = 0;
    trav(c, pieces[i]) {
      cin >> c;
      if (c == 0) n0++;
      else hasside[c].PB(i);
    }
    reverse(all(pieces[i]));
    byn0[n0].PB(i);
  }
  vi used(n);
  auto grid = vector(1, vi(1, -1));
  auto vis = vector(1, vi(1));
  int start = -1;
  for (int n0 = 4; n0 >= 1; n0--) {
    if (!empty(byn0[n0])) {
      start = byn0[n0][0];
      break;
    }
  }
  if (start == -1) failure();
  used[start] = true;
  grid[0][0] = start;
  auto it = find_last_run(all(pieces[start]), 0); // works since the top left corner must have 0's that are all adjacent to each other
                                                  // can prove by casework on number of 0's (2 or 3 are the only interesting cases)
  rotate(begin(pieces[start]), it, end(pieces[start]));
  dfs(grid, vis, pieces, used, hasside, 0, 0);
  
  auto rows = sz(grid), cols = sz(grid[0]);
  if ((ll) rows * cols != n) failure();
  rep(i, 0, rows) rep(j, 0, cols) rep(k, 0, 4) {
    if (grid[i][j] == -1) failure();
    auto nx = i + dx[k];
    auto ny = j + dy[k];
    if (nx < 0 or ny < 0 or nx >= rows or ny >= cols) {
      if (pieces[grid[i][j]][k] != 0) failure();
    } else {
      if (pieces[grid[i][j]][k] != pieces[grid[nx][ny]][k ^ 2]) failure();
      if (pieces[grid[i][j]][k] == 0) failure();
    }
  }
  
  cout << rows << " " << cols << '\n';
  trav(row, grid) {
    trav(elem, row) cout << (elem + 1) << " "; cout << '\n';
  }
}
