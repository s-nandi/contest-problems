// combo (casework), sum of a to b modulo prime p
// https://atcoder.jp/contests/abc163/tasks/abc163_d

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)

const int MOD = 1000000007;
const int inv2 = 500000004;
auto add(auto a, auto b){return ((ll) a + b) % MOD;}
auto sub(auto a, auto b){return ((ll) a - b + MOD) % MOD;}
auto mult(auto a, auto b){return (ll) a * b % MOD;}
auto sum(auto a, auto b) { // inclusive
  auto gap = (b - a + 1);
  auto res = add(mult(gap, a), mult(mult(gap, gap - 1), inv2));
  return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    ++n; // so we can work on range [1...n]
    auto res = 0LL;
    rep(taken, k, n + 1) {
      auto lo = sum(1, 1 + taken - 1);
      auto hi = sum(n - taken + 1, n);
      auto delta = add(sub(hi, lo), 1);
      res = add(res, delta);
    }
    cout << res << '\n';    
}
