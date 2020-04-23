// divide and conquer, combo, counting number of mod m elements in [l, r] range
// https://codeforces.com/contest/1105/problem/C

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const int MOD = 1000000007;
array<int, 3> cnt;

auto floordiv(auto a, auto b){return a >= 0 ? a / b : (a - b + 1) / b;}
auto ceildiv(auto a, auto b){return a >= 0 ? (a + b - 1) / b : a / b;}

array<int, 3> ways(int n) {
  if (n == 1) return {cnt[0] % MOD, cnt[1] % MOD, cnt[2] % MOD};
  auto ways1 = ways(n / 2), ways2 = ways(n - n / 2);
  array<int, 3> res{};
  rep(i, 0, 3) {
    rep(j, 0, 3) {
      auto& acc = res[(i + j) % 3];
      acc = (acc + 1LL * ways1[i] * ways2[j] % MOD) % MOD;
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, l, r;
  cin >> n >> l >> r;
  rep(m, 0, 3) cnt[m] = floordiv(r - m, 3) - ceildiv(l - m, 3) + 1;
  cout << ways(n)[0] << '\n';
}
