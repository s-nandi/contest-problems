// prefix sums on grid, binary search on answer, ensure no false positives then check for no false negatives
// https://codeforces.com/contest/1262/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
 
struct Psum2d {
  using sumT = ll; // PS: Careful of overflow
  vector<vector<sumT>> p;
  Psum2d(const auto& v) {
    auto n = sz(v), m = sz(v[0]);
    p.assign(n+1, vector<sumT>(m+1));
    rep(i, 0, n) rep(j, 0, m)
      p[i+1][j+1] = v[i][j] + p[i+1][j] + p[i][j+1] - p[i][j];
  }
  auto sum(int x1, int y1, int x2, int y2) { // 0-indexed
    assert(x1 <= x2 && y1 <= y2); // Warning: Check precondition
    return p[x2+1][y2+1] - p[x2+1][y1] - p[x1][y2+1] + p[x1][y1];
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, m;
  cin >> n >> m;
  auto grid = vector(n + 2, vi(m + 2));
  rep(i, 1, n + 1) {
    rep(j, 1, m + 1) {
      char c;
      cin >> c;
      grid[i][j] = (c == 'X');
    }
  }
  n += 2, m += 2;
  auto ps = Psum2d(grid);
  
  auto feasible_set = [&](int t) {
			auto original = vector(n, vi(m));
			rep(i, 0, n) rep(j, 0, m) {
			  auto x1 = max(0, i - t), y1 = max(0, j - t);
			  auto x2 = min(n - 1, i + t), y2 = min(m - 1, j + t);
			  auto total = (x2 - x1 + 1) * (y2 - y1 + 1);
			  original[i][j] = ps.sum(x1, y1, x2, y2) == total;
			}
			return original;
		      };
 
  auto feasible = [&](int t) {
		    auto original = feasible_set(t);
		    auto onfire = vector(n + 1, vi(m + 1));
		    rep(i, 0, n) rep(j, 0, m) if (original[i][j]) {
		      auto x1 = max(0, i - t), y1 = max(0, j - t);
		      auto x2 = min(n - 1, i + t), y2 = min(m - 1, j + t);
		      onfire[x1][y1] += 1;
		      onfire[x1][y2 + 1] -= 1;
		      onfire[x2 + 1][y1] -= 1;
		      onfire[x2 + 1][y2 + 1] += 1;
		    }
		    auto onfire_ps = Psum2d(onfire);
		    for (int i = 0; i < n; i++) {
		      for (int j = 0; j < m; j++) {
			if (onfire_ps.sum(0, 0, i, j) < grid[i][j]) {
			  return false;
			}
		      }
		    }
		    return true;
		  };
 
  auto lo = 0, hi = min(n, m);
  while (lo < hi) {
    auto mid = lo + (hi - lo + 1) / 2;
    if (feasible(mid)) {
      lo = mid;
    } else {
      hi = mid - 1;
    }
  }
  
  auto certificate = feasible_set(lo);
  cout << lo << '\n';
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      cout << (certificate[i][j] ? 'X' : '.');
    }
    cout << '\n';
  }
}
