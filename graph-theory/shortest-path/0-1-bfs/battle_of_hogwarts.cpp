// connect (bottom or left) to (top or right) with potentially diagonal walls, 0-1 BFS (& INF edges)
// https://open.kattis.com/problems/battleofhogwarts
// 2020 Vietnam Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int INF = 1031231234;

const vi dx = {0, -1, -1, -1, 0, 1, 1, 1};
const vi dy = {-1, -1, 0, 1, 1, 1, 0, -1};

int cost(char c) {
  if (c == '#') return 0;
  else if (c == '.') return 1;
  else if (c == '@') return INF;
  else assert(false);
}

auto minn(auto& a, auto b){return b < a ? a = b, true : false;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  while (true) {
    int n, m;
    cin >> n >> m;
    if (n == 0 and m == 0) break;
    auto grid = vector(n, string(m, ' '));
    trav(row, grid) trav(elem, row) cin >> elem;

    auto wall1 = [&](int i, int j){return j == 0 or i == n - 1;};
    auto wall2 = [&](int i, int j){return j == m - 1 or i == 0;};
    auto inbounds = [&](int i, int j){return i >= 0 and j >= 0 and i < n and j < m;};

    auto dist = vector(n, vi(m, INF));
    auto vis = vector(n, vi(m));
    deque<pii> q;
    rep(i, 0, n) rep(j, 0, m) {
      if (wall1(i, j)) {
        int c = cost(grid[i][j]);
        dist[i][j] = c;
        if (c == 0) q.push_front({i, j});
        else if (c == 1) q.push_back({i, j});
      }
    }

    auto best = INF;
    while (!empty(q)) {
      auto [x, y] = q.front(); q.pop_front();
      if (wall2(x, y)) {
        best = dist[x][y];
        break;
      }
      
      rep(k, 0, sz(dx)) {
        auto nx = x + dx[k];
        auto ny = y + dy[k];
        if (!inbounds(nx, ny)) continue;

        auto c = cost(grid[nx][ny]);
        auto ncost = dist[x][y] + c;
        if (minn(dist[nx][ny], ncost)) {
          if (c == 0) {
            q.push_front({nx, ny});
          } else if (c == 1) {
            q.push_back({nx, ny});
          }
        }
      }
    }
    cout << (best < INF ? best : -1) << '\n';
  }
}
