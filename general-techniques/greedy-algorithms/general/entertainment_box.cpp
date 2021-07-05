// greedy (maintain lowest k end times)
// https://open.kattis.com/problems/entertainmentbox

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

const int INF = 1031231234;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<pii> a(n);
  trav(i, a) {cin >> i.first >> i.second;}
  a.PB({INF, INF + 1});
  sort(all(a));

  int done = 0;
  multiset<int> byend;
  for (const auto& [l, r]: a) {
    while (!empty(byend) and *begin(byend) <= l) {
      byend.erase(begin(byend));
      done++;
    }

    byend.insert(r);
    if (sz(byend) > k) { assert(sz(byend) == k + 1);
      byend.erase(prev(end(byend)));
    }
  }
  cout << done << '\n';
}
