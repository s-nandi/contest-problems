// bit manipulation, recursion
// https://naipc19.kattis.com/problems/xorsequences
// 2019 NAIPC

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int mult(int a, int b) { return ((long long)a * b) % MOD; }

// true iff v[l..r] is mirrored when cut in half
bool mirror(const vector<int>& v, int l, int r) {
  int m = (l + r) / 2;
  for (int i = 0; l + i <= m; i++) {
    if (v[l + i] != v[m + 1 + i]) {
      return false;
    }
  }
  return true;
}

// solving on [l, r] inclusive, while checking on the pos-th bit
int num_ways(const vector<int>& p, int l, int r, int pos = 0) {
  if (l == r) return true;

  int m = (l + r) / 2;
  set<int> first_half, second_half;
  for (int i = l; i <= m; i++) {
    first_half.insert(p[i]);
  }
  for (int i = m + 1; i <= r; i++) {
    second_half.insert(p[i]);
  }

  bool disjoint = true;
  for (auto elem : second_half) {
    if (first_half.count(elem)) disjoint = false;
  }

  if (!disjoint) {
    if (!mirror(p, l, r))
      return 0;
    else {
      // The pos-th bit of all the numbers in [l, r] can be either 0 or 1, but must all be the same
      return mult(2, num_ways(p, l, m, pos + 1));
    }
  } else {
    return mult(num_ways(p, l, m, pos + 1), num_ways(p, m + 1, r, pos + 1));
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int m, n;
  cin >> m >> n;

  vector<int> p(1 << m);
  for (auto& elem : p) {
    cin >> elem;
    --elem;
  }

  cout << num_ways(p, 0, (1 << m) - 1);
}
