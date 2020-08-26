// 2d prefix sum, fix j, l in (i,j,k,l) tuple and find all (i, k) s.t. 0 <= i < j and j < k < l with rectangular sum queries
// https://codeforces.com/contest/1400/problem/D

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXA = 3000;

template<class T>
struct SubMatrix {
  vector<vector<T>> p;
  SubMatrix(vector<vector<T>>& v) {
    int R = sz(v), C = sz(v[0]);
    p.assign(R+1, vector<T>(C+1));
    rep(r,0,R) rep(c,0,C)
      p[r+1][c+1] = v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c];
  }
  T sum(int u, int l, int d, int r) {
    return p[d][r] - p[d][l] - p[u][r] + p[u][l];
  }
};


int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;

    auto grid = vector(n + 1, vector<int>(n + 1));
    rep(i, 0, n) rep(j, i + 1, n) {
      grid[i][j] = a[i] == a[j];
    }
    
    SubMatrix ps(grid);
    ll res = 0;
    rep(i, 0, n) rep(j, i + 1, n) {
      if (grid[i][j]) {
        auto delta = ps.sum(0, i + 1, i, j);
        res += delta;
      }
    }
    cout << res << '\n';
  }
}
