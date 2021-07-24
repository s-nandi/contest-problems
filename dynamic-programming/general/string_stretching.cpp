// dp (200^4 fits in time), automata -- conseq. chars at the same level are separated by whole recursive strings
// https://open.kattis.com/problems/stretching
// 2015 NAIPC

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

const int MAXN = 201;
auto dp = vector(MAXN, vector(MAXN, vector<int8_t>(MAXN)));

auto orr(auto& a, auto b){a |= b;}

int recur(const auto& s, const auto& t, auto& dp, int i, int repeats, int match) {
  if (repeats == 0 and match == 0) return true;
  
  auto& curr = dp[i][repeats][match];
  if (!~curr) {
    curr = false;
    
    int j = i + sz(t) * repeats + match - 1;
    if (match > 0 and s[j] == t[match - 1]) {
      orr(curr, recur(s, t, dp, i, repeats, match - 1));
    }
    if (match == 0) {
      orr(curr, recur(s, t, dp, i, repeats - 1, sz(t)));
    }
    rep(rep, 1, repeats + 1) {
      if (rep == repeats and match == 0) continue;
      orr(curr, recur(s, t, dp, i, repeats - rep, match) and recur(s, t, dp, j - rep * sz(t) + 1, rep, 0));
    }
  }
  return curr;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  int n = sz(s);
  rep(len, 1, n + 1) if (n % len == 0) {
    string_view best;
    rep(start, 0, n - len + 1) {
      auto t = string_view(s).substr(start, len);
      rep(i, 0, n + 1) rep(j, 0, (n / len) + 1) rep(k, 0, len + 1) dp[i][j][k] = -1;
      if (recur(s, t, dp, 0, n / len, 0))
        best = empty(best) ? t : min(best, t);
    }
    if (!empty(best)) {cout << best << '\n'; exit(0);}
  }
  assert(false);
}
