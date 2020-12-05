// cube simulation, bfs 
// https://open.kattis.com/problems/rebeldie
// 2014 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

int noperations = 0;
const int MAXC = 31;

enum Sides { Top, Bottom, Left, Right, Back, Front };

constexpr array rotright = {Right, Left, Top, Bottom, Back, Front};
constexpr array rotdown = {Front, Back, Left, Right, Top, Bottom};

constexpr auto invert(cauto mapping) {
  auto res = mapping;
  rep(i, 0, sz(mapping)) res[mapping[i]] = Sides(i);
  return res;
}
constexpr auto rotleft = invert(rotright);
constexpr auto rotup = invert(rotdown);

// left, up, right, down
constexpr auto dx = array{0, -1, 0, 1};
constexpr auto dy = array{-1, 0, 1, 0};
constexpr auto rotations = array{rotleft, rotup, rotright, rotdown};

constexpr auto dirs = {0, 1, 2, 3};

struct Dice {
  int x{}, y{};
  array<int, 6> faces{};
  Dice rotate(int dir) const {
    Dice res{};
    res.x = x + dx[dir];
    res.y = y + dy[dir];
    rep(i, 0, 6) res.faces[rotations[dir][i]] = faces[i];
    return res;
  }
  bool set(int val) {
    if (faces[Top] and faces[Top] != val) return false;
    faces[Top] = val;
    return true;
  }
  bool inbounds(int n, int m) const {
    return x >= 0 and y >= 0 and x < n and y < m;
  }
  bool operator < (const auto& o) const {
    return faces < o.faces;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  auto grid = vector(n, vi(m));
  for (auto& row: grid) for (auto& elem: row) {cin >> elem; ++elem;}

  Dice start{}; start.faces[Top] = grid[0][0];
  auto vis = vector(n, vector(m, set<Dice>{}));

  stack<Dice> q;
  q.push(start);
  vis[0][0].insert(start);
  while (!empty(q)) {
    auto dice = q.top(); q.pop();
    const auto& [x, y, faces] = dice;
    // cout << "At " << x << " " << y << endl;
    vis[x][y].insert(dice);
    noperations++;
    
    if (dice.x == n - 1 and dice.y == m - 1) {
      if constexpr(dbg) cout << noperations << endl;
      cout << "YES" << '\n'; exit(0);}
    
    for (const auto& k: dirs) {
      auto ndice = dice.rotate(k);
      const auto& [nx, ny, nfaces] = ndice;
      if (!ndice.inbounds(n, m)) continue;
      if (!ndice.set(grid[ndice.x][ndice.y])) continue;
      if (vis[nx][ny].count(ndice)) continue;
      q.push(ndice);
    }
  }
  if constexpr (dbg) cout << noperations << endl;
  cout << "NO" << '\n';
}
