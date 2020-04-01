// ray-tracing on mirrors, axis-aligned line intersection (finding lexicographic min intersection)
// https://open.kattis.com/problems/safebet
// 2012 World Finals

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const int MAXR = 1000000;
vector<pair<int, char>> byr[MAXR + 5], byc[MAXR + 5];

struct pt {
  int r, c;
  auto operator == (const auto& o) const {return r == o.r and c == o.c;}
  auto operator < (const auto& o) const {return tie(r, c) < tie(o.r, o.c);}
};

auto max_lt(const auto& vec, int pos) {
  return *(prev(lower_bound(all(vec), pair{pos, numeric_limits<char>::min()})));
}

auto min_gt(const auto& vec, int pos) {
  return *(upper_bound(all(vec), pair{pos, numeric_limits<char>::max()}));
}

void getpath(int r, int c, int dir, vector<pt>& path) {
  path.PB({r, c});
  char ch = ' ';
  while (ch != 'W') {
    if (ch == '\\') dir ^= 1;
    else if (ch == '/') dir ^= 3;

    if (dir == 0) tie(c, ch) = max_lt(byr[r], c);
    else if (dir == 1) tie(r, ch) = max_lt(byc[c], r);
    else if (dir == 2) tie(c, ch) = min_gt(byr[r], c);
    else tie(r, ch) = min_gt(byc[c], r);
    path.PB({r, c});
  }
}

struct fenwickTree {
  vi elements;
  fenwickTree(int s) : elements(s + 1) {}
  void modify(int i, int v) {
    for (; i < elements.size(); i += i&(-i)) elements[i] += v;
  }
  auto query(int i) {
    int ans = 0;
    for (; i > 0; i -= i&(-i)) ans += elements[i];
    return ans;
  }
  auto query(int i, int j) {return i ? query(j) - query(i - 1) : query(j);}
};

struct line {
  int same, diff1, diff2;
  line(auto same, auto d1, auto d2) : same{same}, diff1{min(d1,d2) + 1}, diff2{max(d1, d2) - 1} {}
  bool operator < (line o) const {
    return same != o.same ? same < o.same : make_pair(diff1, diff2) < make_pair(o.diff1, o.diff2);
  }
};

struct event {
  int type, pos, lower, upper;
  bool operator < (event o) const { return pos != o.pos ? pos < o.pos : type < o.type; }
};

auto redblueintersection(const auto& h, const auto& v) {
  vector <event> events;
  trav(segment, h) {
    events.push_back({0, segment.diff1, segment.same, -1});
    events.push_back({2, segment.diff2, segment.same, -1});
  }
  trav(segment, v)
    events.push_back({1, segment.same, segment.diff1, segment.diff2});
  sort(all(events));
  ll intersections = 0;
  pt isect = {MAXR + 5, MAXR + 5};
  fenwickTree ft(MAXR + 1);
  for (event e: events) {
    if (e.type == 0) ft.modify(e.lower, 1);
    else if(e.type == 2) ft.modify(e.lower, -1);
    else {
      auto delta = ft.query(e.lower, e.upper);
      intersections += delta;
      if (delta == 0) continue;
      int lo = e.lower, hi = e.upper;
      while (lo < hi) { // binary search for lexic. min intersection
        int mid = lo + (hi - lo) / 2;
        if (ft.query(e.lower, mid) > 0)
          hi = mid;
        else
          lo = mid + 1;
      }
      isect = min(isect, pt{lo, e.pos});
    }
  }
  return pair{intersections, isect};
}

auto solve(const auto& a, const auto& b) {
  vector<line> h, v;
  rep(i, 0, sz(a) - 1)
    if (a[i].r == a[i + 1].r)
      h.PB({a[i].r, a[i].c, a[i + 1].c});
  rep(i, 0, sz(b) - 1)
    if (b[i].c == b[i + 1].c)
      v.PB({b[i].c, b[i].r, b[i + 1].r});
  sort(all(h)); sort(all(v));
  return redblueintersection(h, v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int TC = 1;
  int r, c, m, n;
  while (cin >> r >> c >> m >> n) {
    cout << "Case " << TC++ << ": ";
    rep(i, 0, r + 1) {
      byr[i].clear();
      byr[i].PB({0, 'W'});
      byr[i].PB({c + 1, 'W'});
    }
    rep(j, 0, c + 1) {
      byc[j].clear();
      byc[j].PB({0, 'W'});
      byc[j].PB({r + 1, 'W'});
    }
    rep(i, 0, m + n) {
      int x, y;
      cin >> x >> y;
      char ch = i < m ? '/' : '\\';
      byr[x].PB({y, ch});
      byc[y].PB({x, ch});
    }
    rep(i, 0, r + 1) sort(all(byr[i]));
    rep(j, 0, c + 1) sort(all(byc[j]));
    vector<pt> forward;
    getpath(1, 0, 2, forward);
    if (forward.back() == pt{r, c + 1}) {
      cout << 0 << '\n';
      continue;
    }
    vector<pt> backward;
    getpath(r, c + 1, 0, backward);
    auto [cnt1, isect1] = solve(forward, backward);
    auto [cnt2, isect2] = solve(backward, forward);
    auto cnt = cnt1 + cnt2;
    auto isect = min(isect1, isect2);
    if (cnt == 0) cout << "impossible" << '\n';
    else cout << cnt << " " << isect.r << " " << isect.c << '\n';
  }
}
