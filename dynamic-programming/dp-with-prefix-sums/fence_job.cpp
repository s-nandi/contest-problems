// dp (prefix sums), numbers in final array must be in same relative order as in input, monotone stack
// https://codeforces.com/gym/103102/problem/F

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

template <typename T, class F>
struct MQ {
  deque<T> e; F cmp;
  MQ(F cmp = {}) : cmp(cmp) {}
  auto insert(T elem) {
    while (!e.empty() and cmp(elem, e.back()))
      e.pop_back();
    auto res = empty(e) ? nullopt : optional{e.back()};
    e.push_back(elem);
    return res;
  }
};

const int MOD = 1'000'000'007;
int add(int a, int b) { return (a + b) % MOD; }
int sub(int a, int b) { return (a - b + MOD) % MOD; }
void sadd(int& a, int b) { a = add(a, b); }

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) {cin >> i; --i;}

  auto cmp_less = [&](int i, int j) {
                    return a[i] < a[j];
                  };

  auto bounds = vector(n, vi(2));
  rep(t, 0, 2) {
    MQ<int, decltype(cmp_less)> minq(cmp_less);
    int start = t == 0 ? 0 : n - 1;
    int diff = t == 0 ? 1 : -1;
    for (int i = start; 0 <= i and i < n; i += diff) {
      auto got = minq.insert(i);
      bounds[i][t] = got.value_or(t == 0 ? -1 : n) + diff;
    }
  }

  auto dp = vector(2, vi(n));
  auto psum = vi(n);
  dp[0][0] = 1;
  rep(i, 0, n) {
    partial_sum(all(dp[i & 1]), begin(psum), add);
    auto sum = [&](int i, int j) { return sub(psum[j], (i ? psum[i - 1] : 0)); };
    fill(all(dp[(i + 1) & 1]), 0);
    rep(j, 0, n) {
      if (bounds[j][0] <= i and i <= bounds[j][1])
        sadd(dp[(i + 1) & 1][j], sum(0, j));
    }
  }
  int res = 0;
  rep(j, 0, n) {
    sadd(res, dp[n & 1][j]);
  }
  cout << res << '\n';
}
