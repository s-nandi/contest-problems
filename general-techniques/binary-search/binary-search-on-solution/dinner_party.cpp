// binary search on answer (not obvious), recover array given circular prefix sums
// https://dmoj.ca/problem/dmopc19c7p2

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int next(int i, int n){return i + 1 < n ? i + 1 : 0;}

const int INF = 1231231234;
int simulate(const auto& a, int i, int val, vi* out = nullptr) {
  vi b(sz(a));
  b[i] = val;
  int j = next(i, sz(a));
  int prev = val;
  do {
    b[j] = a[j] - prev;
    if (b[j] < 0) return INF;
    prev = b[j];
    j = next(j, sz(a));
  } while (j != i);
  int need = a[i] - prev;
  if (out != nullptr) *out = b;
  return need;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  auto min_pos = min_element(all(a)) - begin(a);
  int lo = 0, hi = a[min_pos];
  int choice = -1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    auto res = simulate(a, min_pos, mid);
    if (res < mid) {
      hi = mid - 1;
    } else if (res > mid) {
      lo = mid + 1;
    } else {
      choice = mid;
      break;
    }
  }
  if (choice == -1) {
    cout << "NO" << '\n';
  } else {
    vi res;
    simulate(a, min_pos, choice, &res);
    cout << "YES" << '\n';
    vector<pair<int, int>> construct;
    rep(i, 0, sz(a)) {
      rep(it, 0, res[i]) {
        construct.PB({i, next(i, sz(a))});
      }
    }
    cout << sz(construct) << '\n';
    for (auto [a, b]: construct) cout << a << " " << b << '\n';
  }
}
