// sprague-grundy, dp on bitmasks, flood fill, wet zone cannot be too big given restrictions
// https://codeforces.com/gym/102501/problem/L
// 2020 Southwestern European Regional

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
using pii = pair<int,int>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

using bs = bitset<25 + 1>; // (N / 2) ^ 2 ~ max area in 2N perim. rectangle

const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};
bool inbounds(int i, int j, int n) {
  return i >= 0 and j >= 0 and i < n and j < n;
}
void forneighbor(int i, int j, int n, const auto& f) {
  rep(k, 0, sz(dx)) {
    auto nx = i + dx[k];
    auto ny = j + dy[k];
    if (!inbounds(nx, ny, n)) continue;
    f(nx, ny);
  }
}

void trimsort(auto& v) {
  sort(all(v));
  v.erase(unique(all(v)), end(v));
}

int flatten(int i, int j, int n) { return i * n + j; }
struct DSU {
  vi par;
  DSU(int n) : par(n, -1) {}
  int find(int i) {return par[i] < 0 ? i : (par[i] = find(par[i]));}
  void join(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    par[i] += par[j];
    par[j] = i;
  }
};

void dfs(const auto& a, int i, int j, auto& comp, int label) {
  if (~comp[i][j]) return;
  comp[i][j] = label;
  forneighbor(i, j, sz(a), [&](int nx, int ny) {
                             if (a[nx][ny] == a[i][j])
                               dfs(a, nx, ny, comp, label);
                           });
}

int solve(int bm, auto& dp, const auto& remaining) {
  auto& curr = dp[bm];
  if (!~curr) {
    vi nxt;
    bs b(bm);
    for (int i = b._Find_first(); i < sz(b); i = b._Find_next(i))
      nxt.PB(solve(bm & remaining[i], dp, remaining));
    trimsort(nxt);
    
    int mex = 0;
    trav(i, nxt) if (i == mex) ++mex;
    curr = mex;
  }
  return curr;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  auto a = vector(n, string{});
  trav(r, a) cin >> r;

  int cc = 0;
  auto comp = vector(n, vi(n, -1));
  rep(i, 0, n) rep(j, 0, n) if (comp[i][j] == -1) {
    dfs(a, i, j, comp, cc);
    cc++;
  }

  auto adjwet = vector(n, vi(n, -1));
  rep(i, 0, n) rep(j, 0, n) if (a[i][j] == '.') {
    forneighbor(i, j, n, [&](int nx, int ny) {
                           if (a[nx][ny] == '*') {
                             adjwet[i][j] = comp[nx][ny];
                           }
                         });
  }

  DSU dsu(n * n);
  rep(i, 0, n) rep(j, 0, n) if (adjwet[i][j] != -1) {
    forneighbor(i, j, n, [&](int nx, int ny) {
                           if (adjwet[nx][ny] == adjwet[i][j]) {
                             dsu.join(flatten(i, j, n), flatten(nx, ny, n));
                           }
                         });
  }
  
  vector<vector<pii>> bycomp(n * n);
  rep(i, 0, n) rep(j, 0, n) {
    if (a[i][j] == '.' and adjwet[i][j] != -1) {
      bycomp[dsu.find(flatten(i, j, n))].PB({i, j});
    }
  }

  int nimsum = 0;
  for (const auto& wet: bycomp) if (!empty(wet)) {
      const int nn = sz(wet);
      const int FULL = (1 << nn) - 1;
      auto indexof = [&](const auto& elem) -> int {
                       auto ind = lower_bound(all(wet), elem) - begin(wet);
                       if (ind < sz(wet) and wet[ind] == elem) return ind;
                       else return -1;
                     };
    
      vi remaining(nn, FULL);
      vi dp(1 << nn, -1);
      rep(it, 0, nn) {
        const auto& [i, j] = wet[it];
        int bad = 1 << it;
        forneighbor(i, j, n, [&](int nx, int ny) {
                               auto nit = indexof(pii{nx, ny});
                               if (nit != -1) bad |= 1 << nit;
                             });
        remaining[it] = FULL - bad;
      }
      nimsum ^= solve(FULL, dp, remaining);
    }
  cout << (nimsum == 0 ? "Second" : "First") << " player will win" << '\n';  
}
