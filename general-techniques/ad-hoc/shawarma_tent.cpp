// ad-hoc, check if point is on manhattan shortest path between two other points
// https://codeforces.com/contest/1271/problem/C

#include <bits/stdc++.h>
using namespace std;

auto dx = vector{0, -1, 0, 1};
auto dy = vector{-1, 0, 1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, sx, sy;
    cin >> n >> sx >> sy;
    vector<pair<int, int>> students(n);
    for (auto& elem: students) {
      cin >> elem.first >> elem.second;
    }

    auto canget = [&](int px, int py) {
		    int res = 0;
		    for (auto [x, y]: students)
		      res += abs(x - sx) + abs(y - sy) == abs(x - px) + abs(y - py) + abs(px - sx) + abs(py - sy);
		    return res;
		  };
    int best = 0;
    pair<int, int> sol = {-1, -1};
    for (int k = 0; k < dx.size(); k++) {
      auto nx = sx + dx[k];
      auto ny = sy + dy[k];
      auto possible = canget(nx, ny);
      if (possible > best) {
	best = possible;
	sol = {nx, ny};
      }
    }
    cout << best << '\n';
    cout << sol.first << " " << sol.second << '\n';
}
