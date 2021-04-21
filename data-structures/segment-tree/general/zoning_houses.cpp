//segment tree, finding 2nd min/max element in range queries
//https://open.kattis.com/problems/zoninghouses
//2018 NAIPC

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

constexpr auto dbg = false;

const int INF = 1231231234;

struct node {
  int mn{INF}, mx{-INF}, mn2{INF}, mx2{-INF};

  void init(int i) {
    mn = mx = i;
  }

  node combine(const node &o) {
    vector<int> mxv = {mx, mx2, o.mx, o.mx2};
    vector<int> mnv = {mn, mn2, o.mn, o.mn2};
    sort(all(mxv), greater<>{});
    sort(all(mnv), less<>{});
    return node{mnv[0], mxv[0], mnv[1], mxv[1]};
  }

  int val() { return abs(mx - mn); }

  int val2(bool excludeMin, int &excluded) {
    if (excludeMin) {
      excluded = mn;
      return abs(mx - mn2);
    } else {
      excluded = mx;
      return abs(mx2 - mn);
    }
  }
};

struct segmentTree {
  int s;
  vector <node> elements;

  segmentTree(vector <int> &v) {
    s = v.size();
    elements.resize(2 * s);
    build(v);
  }

  void build(vector <int> &v) {
    for (int i = 0; i < s; i++) elements[i + s].init(v[i]);
    for (int i = s - 1; i >= 1; i--)
      elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
  }

  node query(int l, int r){
    node acc;
    for (l += s, r += s; l <= r; ++l >>= 1, --r >>= 1) {
      if (l & 1) acc = acc.combine(elements[l]);
      if (!(r & 1)) acc = elements[r].combine(acc);
    }
    return acc;
  }
};

struct pt {
  int x, y, index;
  bool operator < (const pt &o) const {
    return tie(x, y, index) < tie(o.x, o.y, o.index);
  }
};

bool inRange(vector <pt> &points, int ex, int ey, int lb, int rb) {
  pt obj = {ex, ey, -1};
  auto p = *lower_bound(points.begin(), points.end(), obj);
  return p.x == ex and p.y == ey and p.index >= lb and p.index <= rb;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  cin>>n>>q;

  vector <int> x(n), y(n);
  vector <pt> points(n);
  for (int i = 0; i < n; i++) {
    cin>>x[i]>>y[i];
    points[i] = {x[i], y[i], i};
  }
  sort(points.begin(), points.end());
  segmentTree stx(x), sty(y);

  for (int i = 0; i < q; i++) {
    int lb, rb;
    cin>>lb>>rb;
    --lb, --rb;

    node resx = stx.query(lb, rb), resy = sty.query(lb, rb);
    int normalX = resx.val(), normalY = resy.val();
    int best = max(normalX, normalY);

    if (best == 0) {cout<<0<<'\n'; continue;}

    int ex, ey;
    for (int e1 = 0; e1 < 2; e1++) {
      for (int e2 = 0; e2 < 2; e2++) {
        int excludeX = resx.val2(e1, ex);
        int excludeY = resy.val2(e2, ey);
        if (inRange(points, ex, ey, lb, rb)) {
          best = min(best, max(excludeX, excludeY));
        }
        best = min(best, max(excludeX, normalY));
        best = min(best, max(excludeY, normalX));
      }
    }
    cout << best << '\n';
  }
}
