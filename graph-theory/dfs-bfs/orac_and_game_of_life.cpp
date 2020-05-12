// bfs, finding cyclic pattern (bfs to get preperiod/period is 2)
// https://codeforces.com/contest/1349/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define PB push_back

const int INF = 1031231234;
const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};

bool minn(auto& a, auto b){
  if (b < a){a = b; return true;}
  else return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;
  vector<vi> grid(n, vi(m));
  rep(i, 0, n) rep(j, 0, m) {
    char c;
    cin >> c;
    grid[i][j] = (c == '1');
  }
  
  vector<vi> dist(n, vi(m, INF));
  queue<ii> q;
  rep(i, 0, n) rep(j, 0, m) {
    rep(k, 0, 4) {
      auto nx = i + dx[k];
      auto ny = j + dy[k];
      if (nx >= 0 and ny >= 0 and nx < n and ny < m) {
        if (grid[i][j] == grid[nx][ny]) {
          dist[i][j] = 0;
          q.push({i, j});
          break;
        }
      }
    }
  }

  while(!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    rep(k, 0, 4) {
      auto nx = i + dx[k];
      auto ny = j + dy[k];
      if (nx >= 0 and ny >= 0 and nx < n and ny < m) {
        if (minn(dist[nx][ny], dist[i][j] + 1))
          q.push({nx, ny});
      }
    }
  }

  rep(it, 0, k) {
    int x, y; ll t;
    cin >> x >> y >> t;
    --x; --y;
    if (dist[x][y] == INF or t <= dist[x][y]) {
      cout << grid[x][y] << '\n';
    } else {
      if ((t - dist[x][y]) & 1) {
        cout << 1 - grid[x][y] << '\n';
      } else {
        cout << grid[x][y] << '\n';
      }
    }
  }
}
