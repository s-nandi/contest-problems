// binary search on reals, dynamic programming (shortest path on DAG, reconstructing solution)
// https://codeforces.com/contest/489/problem/E

#include <bits/stdc++.h>
using namespace std;

// returns true iff it is possible to have a path with a frustration below the given guess
// stores optimal path if non-null path passed in, as long as the given guess is also optimal
auto frustration_is_higher(const auto& positions, const auto& beauty, auto ideal_length,
                           auto frustration_guess, auto& optimal_path) -> bool {
  auto n = int(positions.size());
  // cost of travelling from site i (start) to site j (end) in a single day
  // precondition: position[i] < position[j]
  auto cost = [&](int i, int j) {
    assert(positions[i] < positions[j]);
    auto distance = positions[j] - positions[i];
    auto diff_from_ideal = (long double)(distance - ideal_length);
    return sqrt(abs(diff_from_ideal)) - (long double)frustration_guess * beauty[j];
  };

  // dp[i] = (cost c, prev p) --> the optimal path ending at
  // site i has a minimum cost of c and the prior site is p
  using dp_cell = pair<long double, int>;
  vector<dp_cell> dp(n);
  for (int i = 1; i < n; i++) {
    dp[i] = {cost(0, i), 0};
    for (int prior = 1; prior < i; prior++) {
      auto possible_cost = dp_cell{dp[prior].first + cost(prior, i), prior};
      dp[i] = min(dp[i], possible_cost);
    }
  }
  if (dp[n - 1].first > 0.L) {
    if (optimal_path.has_value()) {
      auto& path = optimal_path.value();
      path.clear();
      for (int curr = n - 1; curr != 0; curr = dp[curr].second) {
        path.push_back(curr);
      }
      reverse(begin(path), end(path));
    }
    return true;
  } else {
    return false;
  }
}

int main() {
  int n, ideal_length;
  cin >> n >> ideal_length;

  vector<int> positions(n + 1), beauty(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> positions[i] >> beauty[i];
  }

  optional<vector<int>> optimal_path = {{n}}, null_path = nullopt;
  {
    long double lb = 0, ub = 1e6;
    for (int iter = 0; iter < 100; iter++) {
      auto mid = (lb + ub) / 2;
      if (frustration_is_higher(positions, beauty, ideal_length, mid, null_path)) {
        lb = mid;
      } else {
        ub = mid;
      }
    }
    frustration_is_higher(positions, beauty, ideal_length, lb, optimal_path);
  }
  for (const auto& resting_point : optimal_path.value()) {
    cout << resting_point << " ";
  }
  cout << '\n';
}
