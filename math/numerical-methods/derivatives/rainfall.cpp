// derivative (max. function), fix start/end time interval (constant speed is optimal)
// https://open.kattis.com/problems/rainfall
// 2015 UK and Ireland Programming Contest

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

constexpr double INF = 1e18;
constexpr double EPS = 1e-9;

auto solve(int n, auto c, auto d, const auto& a) {
  auto psum = a;
  partial_sum(all(a), begin(psum));
  auto sum = [&](int i, int j) {
               return i <= j ? psum[j] - (i ? psum[i - 1] : 0) : 0;
             };
  
  auto best = INF;
  rep(i, 0, n) rep(j, i, n) {
    int base;
    if (a[j] > a[i]) base = sum(i, j - 1);
    else base = sum(i + 1, j);
    
    auto gap = j - i;
    double A, B, C; // minimize cost(x) = A * x + B / (C + x)

    // if a[j] > a[i], only want partial j..j+1, otherwise want partial i..i+1
    //
    // can always slide the optimal answer in one direction so you either start
    // or end at the beginning of some time interval
    if (a[j] > a[i]) {
      A = a[j];
      B = c * 3600 * d * d;
      C = gap;
    } else {
      A = a[i];
      B = c * 3600 * d * d;
      C = gap;
    }
    auto consider = [&](double x) {
                      x = clamp(x, 0., 1.);
                      auto got = A * x + B / (C + x) + base;
                      best = min(best, got);
                    };
    if (A > 0) {
      consider(-C + sqrt(B / A));
      consider(-C - sqrt(B / A));
    } else {
      consider(1); // if no rain, optimal to bike during the whole time interval
    }
  }
  return best;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  double c, d;
  cin >> c >> d;
  vi a(n);
  trav(i, a) cin >> i;

  auto best = solve(n, c, d, a);
  cout << fixed << setprecision(7) << best << '\n';
}
