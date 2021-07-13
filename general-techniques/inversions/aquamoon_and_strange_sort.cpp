// inversions, proofy, segtree
// https://codeforces.com/contest/1545/problem/A
// Note: editorial and comments provide simpler solution

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;
 
struct Tree {
  typedef int T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a + b; } 
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] += val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { 
    ++e;
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

/*
* Given an array of 0's and 1's, can you convert it to 0's with any number of:
* 
* Op i: If a[i] == a[i + 1], do a[i] ^= 1, a[i + 1] ^= 1. Otherwise, do nothing.
*/
bool canzero(const vi& a) {
  vi ones;
  rep(i, 0, sz(a)) if (a[i] == 1) {
    if (!empty(ones) and (i - ones.back() - 1) % 2 == 0)
      ones.pop_back();
    else
      ones.PB(i);
  }
  return sz(ones) == 0;
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;
    auto sorted = a;
    sort(all(sorted));
    sorted.erase(unique(all(sorted)), end(sorted));
    auto indexof = [&](int i){return lower_bound(all(sorted), i) - begin(sorted);};
    trav(i, a) i = indexof(i);
    int maxa = sz(sorted);
 
    vi freq(maxa);
    trav(i, a) freq[i]++;
 
    vi behind(n);
    vi ahead(n);
    {
      Tree st(maxa);
      rep(i, 0, n) {
        behind[i] = st.query(a[i] + 1, maxa - 1);
        st.update(a[i], 1);
      }
    }
    {
      Tree st(maxa);
      for (int i = n - 1; i >= 0; i--) {
        ahead[i] = st.query(0, a[i] - 1);
        st.update(a[i], 1);
      }
    }
    
    vector<vi> byvalue(maxa);
    rep(i, 0, n) {
      // Cannot avoid swaps with strictly smaller and bigger values
      int inv = (ahead[i] + behind[i]) & 1;
      byvalue[a[i]].PB(inv);
    }
    
    bool ok = true;
    rep(val, 0, maxa) {
      // Try to zero out with swaps within the same value
      ok &= canzero(byvalue[val]);
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
