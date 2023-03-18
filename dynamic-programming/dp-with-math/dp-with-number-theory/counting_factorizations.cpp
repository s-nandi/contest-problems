// dp (over prime factorization), factorial modulo inverse
// https://codeforces.com/contest/1794/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXV = 1'000'000;
constexpr int MOD = 998'244'353;

auto is_prime(int val) {
  if (val == 1) {
    return false;
  }
  for (int i = 2; i * i <= val; i++) {
    if (val % i == 0) {
      return false;
    }
  }
  return true;
}

auto mult(int a, int b) -> int { return (ll)a * b % MOD; }
auto add(int a, int b) {
  if (a + b < 0) {
    return a + b + MOD;
  }
  if (a + b >= MOD) {
    return a + b - MOD;
  }
  return a + b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> fac(MAXV + 1);
  vector<int> inv(MAXV + 1);
  vector<int> invfac(MAXV + 1);
  for (int i = 0; i < 2; i++) {
    fac[i] = inv[i] = invfac[i] = 1;
  }
  for (int i = 2; i <= MAXV; i++) {
    inv[i] = add(0, -mult(MOD / i, inv[MOD % i]));
    fac[i] = mult(fac[i - 1], i);
    invfac[i] = mult(invfac[i - 1], inv[i]);
  }

  auto multrange = [&](int a, int b) {
    if (b < a) {
      return 1;
    }
    if (a == 1) {
      return fac[b];
    }
    return mult(fac[b], invfac[a - 1]);
  };

  int n;
  cin >> n;
  vector<int> vals(2 * n);
  for (auto& i : vals) {
    cin >> i;
  }

  map<int, int> primes;
  map<int, int> nonprimes;
  for (auto i : vals) {
    if (is_prime(i)) {
      primes[i]++;
    } else {
      nonprimes[i]++;
    }
  }

  int nontaken_base = 0;
  ll cnt_base = 1;
  for (const auto& [val, freq] : nonprimes) {
    cnt_base = mult(cnt_base, invfac[freq]);
    nontaken_base += freq;
  }
  cnt_base = mult(cnt_base, fac[nontaken_base]);

  using table = map<pair<int, int>, ll>;
  table dp = {
      {{0, nontaken_base}, cnt_base},
  };

  for (const auto& [val, freq] : primes) {
    table dp_next;
    for (const auto& [key, cnt] : dp) {
      const auto& [taken, nontaken] = key;
      const auto& options = {pair{1, freq - 1}, pair{0, freq}};
      for (const auto& [take, nontake] : options) {
        auto new_taken = taken + take;
        auto new_nontaken = nontaken + nontake;

        if (new_taken > n or new_nontaken > n) {
          continue;
        }

        auto new_cnt = mult(mult(cnt, multrange(nontaken + 1, new_nontaken)),
                            invfac[nontake]);
        auto new_key = pair{new_taken, new_nontaken};
        dp_next[new_key] = add(dp_next[new_key], new_cnt);
      }
    }
    dp = move(dp_next);
  }

  auto res = dp[{n, n}];
  cout << res << '\n';
}
