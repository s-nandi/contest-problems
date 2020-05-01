// greedy (even distribution is best), expected value (only # of pips on dice matters, not distribution)
// https://utipc19.kattis.com/problems/utipc19.paintingpips
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vi cnt(n);
  rep(i, 0, n) {
    cnt[i] += (m / n);
  }
  rep(i, 0, m % n) {
    cnt[i]++;
  }

  ll ways = 1;
  rep(i, 0, n) {
    ways *= cnt[i];
  }
  auto res = (ld) ways;
  rep(i, 0, n) {
    res /= 6;
  }
  cout << fixed << setprecision(11) << res << '\n';
}
