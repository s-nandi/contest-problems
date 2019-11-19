// ternary search on integers, divisors of number, greedy (bundle first k 1's together, then next k, etc)
// https://codeforces.com/contest/1255/problem/E1

#include <bits/stdc++.h>
using namespace std;

constexpr auto INF = 123123123123123123LL;

auto simulate(const auto& positions, int f) {
  auto res = 0LL;
  for (auto p: positions) {
    res += abs(p - f);
  }
  return res;
}

auto cost(const auto& positions, int n) {
  auto lo = 0, hi = n - 1;
  while (lo < hi) {
    auto mid = (lo + hi) / 2;
    auto inc = simulate(positions, mid + 1) > simulate(positions, mid);
    if (inc) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  return simulate(positions, lo);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;

    auto total = accumulate(begin(a), end(a), 0, plus<>{});
    if (total < 2) {
      cout << -1 << '\n';
      return 0;
    }

    vector<int> divisors;
    for (int i = 1; i * i <= total; i++) {
      if (total % i == 0) {
	if (i != 1) divisors.push_back(i);
	divisors.push_back(total / i);
      }
    }
    
    auto best = INF;
    for (auto d: divisors) {
      vector<int> window;
      auto possible = 0LL;
      for (int i = 0; i < n; i++) {
	if (a[i] == 1) {
	  window.push_back(i);

	  if (window.size() == d) {
	    auto c = cost(window, n);
	    possible += cost(window, n);
	    window.clear();
	  }
	}
      }
      best = min(best, possible);
    }
    cout << best << '\n';
}
