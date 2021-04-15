// segment tree (max subsegment query), fenwick tree (lower bound)
// https://open.kattis.com/problems/ski

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

const ll INF = 1e15;  

struct ST {
  struct node {
    ll suff, pref, bestSum, sum;
    void modify(ll nval) {suff = pref = bestSum = sum = nval;}
  };
  
  using T = node;
  
  static constexpr T unit = node{0, 0, 0, 0};
  T f(T a, T b) {
    auto nsuff = max({b.suff, b.sum + a.suff});
    auto npref = max({a.pref, a.sum + b.pref});
    auto nbestSum = max({a.bestSum, b.bestSum, a.suff + b.pref});
    auto nsum = a.sum + b.sum;
    return {nsuff, npref, nbestSum, nsum};
  }
  
  vector<T> s; int n;
  ST(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, int val) {
    for (s[pos += n].modify(val); pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    e++;
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) { // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos-1];
    return res;
  }
  int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
        pos += pw, sum -= s[pos-1];
    }
    return pos;
  }
};

ll calc_fun(ll h1, ll h2) {
  auto diff = h1 - h2;
  return h1 >= h2 ? diff * diff : -(diff * diff);
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vi a(n + 1);
  trav(i, a) cin >> i;
  vi h(n + 1);

  FT ft_cost(n + 1);
  ST st_fun(n + 1);
  auto set_op = [&](int i, int v) {
                  const array indices = {i - 1, i};
                  trav(seg, indices) {
                    if (seg < 0 or seg >= n) continue;
                    ft_cost.update(seg, -(h[seg] + h[seg + 1]));
                  }
                  h[i] = v;
                  
                  trav(seg, indices) {
                    if (seg < 0 or seg >= n) continue;
                    st_fun.update(seg, calc_fun(h[seg], h[seg + 1]));
                    ft_cost.update(seg, (h[seg] + h[seg + 1]));
                  }
                };

  rep(i, 0, n + 1) {
    set_op(i, a[i]);
  }

  if (dbg){
    rep(i, 0, n) {
      cout << "At " << i << " : " << st_fun.query(0, i).bestSum << endl;
    }
    cout << "1 to n - 1: " << st_fun.query(0, n - 1).bestSum << endl;
  }
  
  rep(it, 0, q) {
    int t;
    cin >> t;
    if (t == 0) {
      int i, v;
      cin >> i >> v;
      set_op(i, v);
    } else {
      int x; ll k;
      cin >> x >> k;

      auto rmost = ft_cost.lower_bound(ft_cost.query(x) + k + 1) - 1;
     
      

      auto got = rmost >= 0 ? st_fun.query(0, rmost).bestSum : 0LL;
      cout << got << '\n';
    }
  }
}
