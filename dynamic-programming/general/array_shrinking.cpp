// dp (covering range with intervals), greedy (stack trick - while top of stack can combine with curr, keep combining)
// https://codeforces.com/contest/1312/problem/E
// Neal says you can do this in N lg N: https://codeforces.com/blog/entry/74656

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

void minn(auto& a, auto b){a = min(a, b);}

int reduce(const vi& a, int l, int r) {
  stack<int> s;
  rep(i, l, r + 1) {
    int curr = a[i];
    while (!s.empty() and s.top() == curr) {
      s.pop();
      curr++;
    }
    s.push(curr);
  }
  if (sz(s) == 1) return s.top();
  else return -1;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  auto feas = vector(n, vi(n, -1));
  rep(i, 0, n) rep(j, i, n)
    feas[i][j] = reduce(a, i, j);

  const int INF = 1031231234;
  auto dp = vi(n + 1, INF);
  dp[0] = 0;
  rep(i, 0, n) {
    rep(j, i, n) {
      if (feas[i][j] == -1) continue;
      minn(dp[j + 1], dp[i] + 1);
    }
  }
  cout << dp[n] << '\n';
}
