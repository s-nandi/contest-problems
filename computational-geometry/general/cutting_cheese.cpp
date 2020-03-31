// bs on answer, calculus (vol. of spherical cap)
// https://open.kattis.com/problems/cheese
// 2015 World Finals

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (auto i = (a); i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define PB push_back

using ptT = double;
const ptT MAXD = 100000;
const ptT PI = acos(-1);
struct sphere {
  ptT x, y, z, r;

  auto slice(ptT b) {
    b -= z;
    b = clamp(b, -r, r);
    return PI * ((b * r * r - b * b * b / 3) - (-r * r * r + r * r * r / 3));
  }
};

auto holes(auto &ss, auto b) {
  ptT acc = 0;
  trav(s, ss)
    acc += s.slice(b);
  return acc;
}

const int ITERS = 30;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<sphere> spheres(n);
  trav(s, spheres) {
    cin >> s.r >> s.x >> s.y >> s.z;
  }

  auto total = MAXD * MAXD * MAXD - holes(spheres, MAXD);
  auto target = total / k;

  ptT a = 0;
  vector<ptT> slices;
  rep(i, 0, k) {
    auto lo = a, hi = MAXD;
    rep(it, 0, ITERS) {
      auto mid = lo + (hi - lo) / 2;
      auto got = MAXD * MAXD * mid - holes(spheres, mid);
      if (got < target * (i + 1))
        lo = mid;
      else
        hi = mid;
    }
    slices.PB(lo - a);
    a = lo;
  }
  trav(s, slices) {
    cout << fixed << setprecision(11) << s / 1000 << '\n';
  }
}
