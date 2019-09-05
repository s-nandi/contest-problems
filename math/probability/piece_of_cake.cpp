// expected value, shoelace theorem, probability of some items being picked while others excluded

#include <bits/stdc++.h>
using namespace std;

using ptT = double;
struct pt {
  ptT x, y;
  ptT operator^(const pt& o) const { return x * o.y - y * o.x; }
};

int num_between_on_circle(int i, int j, int n) {
  if (i > j) j += n;
  return j - i - 1;
}

const int MAXN = 2505;
// combos[i] = probability that two points are chosen when there are i points between them
array<double, MAXN> combos;
void precompute(int n, int k) {
  combos[0] = 1.0 * k * (k - 1) / (1.0 * n * (n - 1));
  for (int i = 1; i < n; i++) {
    combos[i] = (1.0 * n - k - i + 1) / (1.0 * n - i - 1) * combos[i - 1];
  }
}

auto prob_both_chosen(int num_between) { return combos[num_between]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  precompute(n, k);

  vector<pt> points(n);
  for (auto& point : points) {
    cin >> point.x >> point.y;
  }

  double ev = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = 0; j < points.size(); j++) {
      if (i == j) continue;

      auto contribution = (points[i] ^ points[j]) / 2.0;
      int between = num_between_on_circle(i, j, n);
      auto prob = prob_both_chosen(between);
      ev += contribution * prob;
    }
  }
  cout << fixed << setprecision(10) << abs(ev) << '\n';
}
