// dp + ds, maintain stack invariant, segment tree
// https://codeforces.com/contest/1482/problem/E

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

constexpr bool dbg = true;

struct edge{int to;};
using graph = vector<vector<edge>>;

const ll INF = 1e18;
auto maxx(auto& a, auto b){a = max(a, b);}

int midpoint(int lo, int hi){return (lo + hi) / 2;}

struct ST {
  using T = ll;
  static constexpr T def = -INF;
  T f(T v1, T v2){return max(v1, v2);}
  
  int s;
  vector<T> a;
  ST(int n) : s{n}, a(4 * n, def) {}
  void update(int pos, T val){update(1, 0, s - 1, pos, val);}
  void update(int i, int lo, int hi, int pos, T val) {
    if (pos < lo or hi < pos) return;
    else if (pos <= lo and hi <= pos) a[i] = val;
    else {
      auto mid = midpoint(lo, hi);
      update(2 * i, lo, mid, pos, val);
      update(2 * i + 1, mid + 1, hi, pos, val);
      a[i] = f(a[2 * i], a[2 * i + 1]);
    }
  }
  
  T query(int l, int r){return query(1, 0, s - 1, l, r);}
  T query(int i, int lo, int hi, int l, int r) {
    if (hi < l or r < lo) return def;
    else if (l <= lo and hi <= r) return a[i];
    else {
      auto mid = midpoint(lo, hi);
      auto lq = query(2 * i, lo, mid, l, r);
      auto rq = query(2 * i + 1, mid + 1, hi, l, r);
      return f(lq, rq);
    }
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi h(n + 1);
  rep(i, 1, n + 1) cin >> h[i];
  vi b(n + 1);
  rep(i, 1, n + 1) cin >> b[i];

  ST st(n + 1); // st[i] = dp[i] = best sum for [1..i] prefix (1-indexed, inclusive)
  stack<int> stk; // sorted by increasing height
  
  priority_queue<pair<ll, int>> active; // {{best, ind} if ind in stk}
  vi dead(n + 1);
  auto bestactive = [&]() {
                      while (!empty(active)) {
                        const auto& [best, ind] = active.top();
                        if (!dead[ind]) return best;
                        active.pop();
                      }
                      return -INF;
                    };
  
  st.update(0, 0);
  rep(i, 1, n + 1) {
    while (!empty(stk) and h[i] < h[stk.top()]) {
      dead[stk.top()] = true;
      stk.pop();
    }
    auto last_smaller = empty(stk) ? 0 : stk.top(); // can use any elem in [last_smaller + 1..i] in current partition
    auto best = st.query(last_smaller, i - 1) + b[i]; // => can use any dp value in [last_smaller .. i - 1]
    stk.push(i);
    active.push({best, i});
    st.update(i, bestactive());
  }
  cout << st.query(n, n) << '\n';
}
