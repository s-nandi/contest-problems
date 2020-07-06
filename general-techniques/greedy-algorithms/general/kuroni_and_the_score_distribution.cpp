// constructive, binary search on (canonical form of) answer, greedy (1..n maximizes balance, incrementing tail by 1 doesn't skip over any values)
// https://codeforces.com/contest/1305/problem/E

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

bool contains(const pii& p, int i) {
  return p.first <= i and i <= p.second;
}

auto generate(int initial, int split, int n) {
  vi res(n);
  iota(all(res), initial);
  rep(i, n - split, n)
    ++res[i];
  return res;
}

int balance(int initial, int split, int n) {
  // either 1 continuous range, or two continuous ranges (left, right) s.t. max(left) + 1 = min(right) - 1
  int res = 0;
  pii range1, range2;
  if (split > 0) {
    int rem = n - split;
    range1 = {initial, initial + rem - 1};
    range2 = {initial + rem + 1, initial + n};
  } else {
    range1 = {initial, initial + n - 1};
    range2 = {-1, -2}; // empty range
  }
  auto a = generate(initial, split, n);
  rep(i, 0, n) rep(j, i + 1, n) {
    int sum = a[i] + a[j];
    if (contains(range1, sum) or contains(range2, sum))
      res++;
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, target;
  cin >> n >> target;
  
  vi a(n);
  iota(all(a), 1);

  auto initial = balance(1, 0, n); // [1..n] maximizes balance, then we shift the tail up to incrementally reduce balance
  if (initial < target) {
    cout << -1 << '\n';
    exit(0);
  }
  
  int lo = 1 * n + 0, hi = (n + 1) * n + (n - 1); // (i / n) => smallest # in range(s), (i % n) => len of 2nd range, can be 0
  while (lo < hi) {
    auto mid = lo + (hi - lo) / 2;
    auto [initial, split] = pii{mid / n, mid % n};
    auto got = balance(initial, split, n);
    if (got <= target) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  auto sol = generate(lo / n, lo % n, n);
  trav(i, sol) cout << i << " "; cout << '\n';
}
