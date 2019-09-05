// interactive, dfs, reserving backtrack edge first
// https://open.kattis.com/problems/amazing
// 2016 Greater NY Regional

#include <bits/stdc++.h>
using namespace std;

vector direction_names = {"down", "left", "up", "right"};
vector dx = {1, 0, -1, 0};
vector dy = {0, -1, 0, 1};
using edge = tuple<int, int, int>;

auto opposite(int dir) -> int { return (dir + 2) % dx.size(); }

auto ask(int dir) -> bool {
  cout << direction_names[dir] << endl;
  string response;
  cin >> response;
  if (response == "ok") {
    return true;
  } else if (response == "wall") {
    return false;
  } else {
    exit(0);
  }
}

auto dfs(int x, int y, set<edge> &visited, int backtrack_dir = 0) -> void {
  visited.insert({x, y, backtrack_dir});
  for (int i = 0; i < 4; i++) {
    if (i == backtrack_dir)
      continue;
    auto nx = x + dx[i];
    auto ny = y + dy[i];
    if (visited.count({x, y, i})) {
      continue;
    }
    visited.insert({x, y, i});
    if (ask(i)) {
      dfs(nx, ny, visited, opposite(i));
    }
  }
  ask(backtrack_dir);
}

int main() {
  set<edge> visited;
  dfs(0, 0, visited);
  cout << "no way out" << endl;
}
