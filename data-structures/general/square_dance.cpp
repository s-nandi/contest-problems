// simulation, linked list style deletion
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1355
// 2020 GCJ Round 1A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using ii = pair<int, int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

using state = tuple<ll, int, int>; // value, i, j
vi dx{0, -1, 0, 1};
vi dy{-1, 0, 1, 0};
ii sentinel = {-1, -1};
bool inbounds(int i, int j, int r, int c) {
  return i >= 0 and j >= 0 and i < r and j < c; 
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  rep(test_case, 1, T + 1) {
    int r, c;
    cin >> r >> c;
    vector<vi> grid(r, vi(c));
    rep(i, 0, r) rep(j, 0, c)
      cin >> grid[i][j];
    
    auto acc = 0LL;
    rep(i, 0, r) rep(j, 0, c)
      acc += grid[i][j];
    set<state> pq;
    vector<vector<ll>> values(r, vector<ll>(c));
    vector<vi> purged(r, vi(c));
    vector<vector<ii>> neighbors[4];
    rep(k, 0, 4) neighbors[k] = vector<vector<ii>>(r, vector<ii>(c, sentinel));
    rep(i, 0, r) rep(j, 0, c) {
      int nn = 0;
      rep(k, 0, 4) {
        auto nx = i + dx[k];
        auto ny = j + dy[k];
        if (!inbounds(nx, ny, r, c)) continue;
        neighbors[k][i][j] = {nx, ny};
        values[i][j] -= grid[nx][ny];
        nn++;
      }
      values[i][j] += nn * grid[i][j];
      pq.insert({values[i][j], i, j});
    }
    
    ll sol = 0;
    while (!pq.empty()) {
      int num_deleted = 0;
      vector<state> deleted;
      vector<ii> changed;
      sol += acc;
      while (!pq.empty() and get<0>(*pq.begin()) < 0) {
        ll delta; int i, j;
        tie(delta, i, j) = *pq.begin();
        pq.erase(pq.begin());
        purged[i][j] = true;
        acc -= grid[i][j];
        num_deleted++;
        
        rep(k, 0, 4) {
          if (neighbors[k][i][j] == sentinel) continue;
          auto k_opp = k ^ 2;     
          int nx, ny, ox, oy;
          tie(nx, ny) = neighbors[k][i][j];
          tie(ox, oy) = neighbors[k_opp][i][j];   
          neighbors[k_opp][nx][ny] = neighbors[k_opp][i][j];
          deleted.PB({values[nx][ny], nx, ny});
          values[nx][ny] += grid[i][j];
          if (ox != -1 and oy != -1) {
            values[nx][ny] -= grid[ox][oy];
          } else {
            values[nx][ny] -= grid[nx][ny]; // since number of neighbors decreased
          }
          changed.PB({nx, ny});
        }
      }
      
      trav(d, deleted) pq.erase(d);
      trav(pos, changed) {
        int i, j;
        tie(i, j) = pos;
        if (purged[i][j]) continue;
        pq.insert({values[i][j], i, j});
      }
      if (num_deleted == 0) break;
    }
    cout << "Case #" << test_case << ": " << sol << '\n';
  }
}
