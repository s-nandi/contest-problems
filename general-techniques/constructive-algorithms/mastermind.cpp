// constructive, greedy (optimal permutation to minimize intersections => rotate by max{cnt_elem}, choose fixed points first and assign sentinels last)
// https://codeforces.com/contest/1381/problem/C

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

int getmissing(const auto& a, int n) {
  set<int> holes;
  rep(i, 1, n + 2) holes.insert(i);
  trav(i, a) holes.erase(i);
  assert(!empty(holes));
  return *begin(holes);
}

vi fixedset(int k, auto bycolor) {
  set<pii, greater<>> freq_col(greater<>{});
  for (const auto& [color, row]: bycolor)
    freq_col.insert({sz(row), color});
  vi res;
  while (sz(res) < k) {
    auto [cnt, col] = *begin(freq_col);
    freq_col.erase(begin(freq_col));
    auto pos = bycolor[col].back(); bycolor[col].pop_back();
    res.PB(pos);
    if (--cnt) {
      freq_col.insert({cnt, col});
      assert(!empty(bycolor[col]));
    }
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n, x, y;
    cin >> n >> x >> y;
    vi a(n);
    trav(i, a) cin >> i;

    map<int, vi> bycolor; // bycolor[col] = {pos1, pos2, ...}
    rep(i, 0, n)
      bycolor[a[i]].PB(i);
    auto fixed = fixedset(x, bycolor);
    
    vi b(n, -1);
    trav(i, fixed) b[i] = a[i];

    vi free;
    rep(i, 0, n) if (b[i] == -1)
      free.PB(i);
    sort(all(free), [&](const int& i, const int &j){return a[i] < a[j];});

    int maxocc = 0;
    map<int, int> freefreq;
    trav(i, free)
      maxocc = max(maxocc, ++freefreq[a[i]]);

    auto rotated = free;
    rotate(begin(rotated), begin(rotated) + maxocc, end(rotated));
    rep(i, 0, sz(free))
      b[free[i]] = a[rotated[i]];

    auto hole = getmissing(a, n);
    int nhole = n - y;
    trav(i, free) {
      if (a[i] == b[i]) {
        b[i] = hole;
        --nhole;
      }
    }
    trav(i, free) {
      if (b[i] != hole and nhole > 0) {
        b[i] = hole;
        --nhole;
      }
    }
    if (nhole < 0) cout << "NO" << '\n';
    else {
      cout << "YES" << '\n';
      trav(i, b) cout << i << " "; cout << '\n';
    }    
  }
}
