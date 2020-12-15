// greedy (always best to only have 1 type of lemonade), track the max amt of each lemonade that you could possibly have, work in log-space since numbers can be exponentially big
// https://open.kattis.com/problems/lemonadetrade
// 2017 Benelux Algorithm Programming Challenge

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr ld threshold = log2(10.L);
constexpr auto pink = "pink";
constexpr auto blue = "blue";

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  map<string, ld> best;
  best[pink] = 0.L;
  rep(i, 0, n) {
    string given, wanted; ld rat;
    cin >> given >> wanted >> rat;
    if (!best.count(wanted)) continue;
    auto possible = best[wanted] + log2(rat);
    if (best.count(given)) best[given] = max(possible, best[given]);
    else best[given] = possible;
  }
  if (!best.count(blue)) cout << 0.L << '\n';
  else {
    best[blue] = min(best[blue], threshold);
    cout << fixed << setprecision(11) << pow(2.L, best[blue]) << '\n';
  }
}
