// line sweep, segment tree (find first/last one-bit), count # of axis aligned segment intersections and subtract # of overcounted intersections where the horizontal segment overshoots to the left of the vertical segment 
//                                                     but does not touch the next vertical segment to the left -- ie. does not close off any area)
// https://codeforces.com/contest/1401/problem/E
// Note: Editorial solution counts slightly different things, and the overcounting for our solution can be done more easily since the problem prevents two segments from lying on the same line -- just subtract 1 for each left endpoint
//                                                            of a horizontal that does not intersect with the unique (if any) vertical segment on that x-coordinate

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
 
const int MAXC = 1000000;

struct ST {
  vi v;
  int s;
 
  ST(int n) : v(4 * n), s{n} {}
  int f(int a, int b){return a + b;}
 
  void update(int p, int val) {update(1, p, val, 0, s - 1);}
  void update(int i, int p, int val, int lb, int rb) {
    if (lb > p or rb < p) return;
    else if (lb == p and rb == p) v[i] += val;
    else {
      int mb = (lb + rb) / 2;
      update(2 * i, p, val, lb, mb);
      update(2 * i + 1, p, val, mb + 1, rb);
      v[i] = f(v[2 * i], v[2 * i + 1]);
    }
  }
  int query(int l, int r){return query(1, l, r, 0, s - 1);}
  int query(int i, int l, int r, int lb, int rb) {
    if (lb > r or l > rb) return 0;
    else if (l <= lb and rb <= r) return v[i];
    else {
      int mb = (lb + rb) / 2;
      auto lq = query(2 * i, l, r, lb, mb);
      auto rq = query(2 * i + 1, l, r, mb + 1, rb);
      return f(lq, rq);
    }
  }
  int first_in_range(){return first_in_range(1, 0, s - 1);}
  int first_in_range(int i, int lb, int rb) {
    if (v[i] < 1) return -1;
    if (lb == rb) return lb;
    int mb = (lb + rb) / 2;
    if (v[2 * i] >= 1) return first_in_range(2 * i, lb, mb);
    else return first_in_range(2 * i + 1, mb + 1, rb);
  }
  int last_in_range(){return last_in_range(1, 0, s - 1);}
  int last_in_range(int i, int lb, int rb) {
    if (v[i] < 1) return -1;
    if (lb == rb) return lb;
    int mb = (lb + rb) / 2;
    if (v[2 * i + 1] >= 1) return last_in_range(2 * i + 1, mb + 1, rb);
    else return last_in_range(2 * i, lb, mb);
  }
};
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;
 
  ll res = 0;
  vector<vi> add(MAXC + 1), rmv(MAXC + 1);
  vector<vector<pii>> vert(MAXC + 1);
 
  rep(i, 0, n) {
    int y, l, r;
    cin >> y >> l >> r;
    add[l].PB(y);
    rmv[r].PB(y);
  }
  add[0].PB(MAXC);
  add[MAXC].PB(MAXC);
  add[0].PB(0);
  add[MAXC].PB(0);
  
  rep(i, 0, m) {
    int x, t, b;
    cin >> x >> t >> b;
    vert[x].PB({t, b});
  }
  vert[0].PB({0, MAXC});
  vert[MAXC].PB({0, MAXC});

  ST lazy_y(MAXC + 1); // use lazy_y to signal start of horizontal that might not have intersected with a vertical segment yet (avoid overcounting)
  ST st_y(MAXC + 1); // st_y[i] = 1 iff there is a horizontal segment at y = i s.t. some vertical segment has intersected with it
  rep(c, 0, MAXC + 1) {
    for (const auto& [l, r]: vert[c]) { 
      auto delta = st_y.query(l, r) - 1; // count intersections that close pieces to the left -- add AFTER this step
      res += max(0, delta);
    }
    trav(i, add[c]) lazy_y.update(i, 1);
 
    for (const auto& [l, r]: vert[c]) {
      // convert lazy to actual
      if (l == 0) {
        while (true) {
          int pos = lazy_y.first_in_range();
          if (pos == -1 or pos > r) break;
          lazy_y.update(pos, -1);
          st_y.update(pos, 1);
        }
      } else {
        while (true) {
          int pos = lazy_y.last_in_range();
          if (pos == -1 or pos < l) break;
          lazy_y.update(pos, -1);
          st_y.update(pos, 1);
        }
      }
    }
    trav(i, rmv[c]) {
      st_y.update(i, -1);
    }
  }
  cout << res << '\n';
}
