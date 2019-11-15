// shifting intervals into a canonical form, venice technique, binary search, counting # of non-intersections
// https://mausa19.kattis.com/problems/pixelated
// 2019 Mid-Atlantic Regional

#include <bits/stdc++.h>
using namespace std;

#define ALL(x) begin(x),end(x)

struct pulse {
  bool is_horizontal;
  int start, length, offset;
};

using interval = pair<int, int>;

auto left_at_time(const auto& endpoints, auto elem, auto time) {
  auto normalized = elem - time;
  return lower_bound(ALL(endpoints), normalized) - begin(endpoints);
}

auto right_at_time(const auto& endpoints, auto elem, auto time) {
  auto normalized = elem - time;
  return end(endpoints) - upper_bound(ALL(endpoints), normalized);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int num_horizontal = 0;
  vector<pulse> pulses(n);
  for (auto& p: pulses) {
    char type;
    cin >> type >> p.start >> p.length >> p.offset;
    --p.offset, --p.start; // 0-index time and offset
    p.is_horizontal = (type == 'h');
    num_horizontal += p.is_horizontal;
  }

  vector<pair<int, interval>> queries; // [c, [t1, t2]] => time range [t1, t2] s.t. pulse at column c hits row 0
  vector<int> left_endpoints, right_endpoints; // columns [l, r] covered by horizontal pulse at row 0, time = 0
  for (const auto& p: pulses){
    if (p.is_horizontal) {
      auto initial = interval{-p.start - p.length + 1, -p.start}; // columns covered at row = p.offset, time = 0
      left_endpoints.push_back(initial.first + p.offset); // normalize to row 0 by shifting to the right
      right_endpoints.push_back(initial.second + p.offset);
    } else {
      queries.push_back({p.offset, {p.start, p.start + p.length - 1}});
    }
  }
  sort(ALL(left_endpoints));
  sort(ALL(right_endpoints));

  auto sol = 0LL;
  for (const auto& [c, q_interval]: queries) {
    const auto& [t1, t2] = q_interval;
    auto num_left = left_at_time(right_endpoints, c, t2);
    auto num_right = right_at_time(left_endpoints, c, t1);
    auto intersections = num_horizontal - (num_left + num_right);
    sol += intersections;
  }
  cout << sol << '\n';
}
