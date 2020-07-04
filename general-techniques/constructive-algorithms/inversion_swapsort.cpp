// greedy (expanding prefix while maintaining inversions in suffix, processing all inversions with fixed start index in descending order of right elements), reducing to problem on permutation
// https://codeforces.com/contest/1375/problem/E

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

vi to_permutation(const vi& v) {
  auto sorted = v;
  sort(all(sorted));
  vi res(sz(v));
  map<int, int> bump;
  rep(i, 0, sz(v)) {
    res[i] = lower_bound(all(sorted), v[i]) - begin(sorted) + bump[v[i]];
    ++bump[v[i]];
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  a = to_permutation(a);

  vector<vi> inversions(n);
  rep(i, 0, n) rep(j, i + 1, n)
    if (a[i] > a[j])
      inversions[i].PB(j);

  vector<pii> sol;
  rep(i, 0, n) {
    auto& curr = inversions[i];
    sort(all(curr), [&](int i, int j){return a[i] > a[j];});
    trav(j, curr) {
      sol.PB({i, j});
      swap(a[i], a[j]);
    }
  }
  cout << sz(sol) << '\n';
  for (const auto& [u, v]: sol)
    cout << (u + 1) << " " << (v + 1) << '\n';
}
