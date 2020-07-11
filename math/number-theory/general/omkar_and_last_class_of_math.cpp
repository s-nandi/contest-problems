// num thy, fix gcd and solve for coprime a,b s.t. a + b = n, Use a * b = gcd * lcm => gcd(a, b) * (a / gcd + b / gcd) = n / gcd
// https://codeforces.com/contest/1372/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

auto getbest(int sum, int gcd) {
  return tuple{gcd * (sum - 1), gcd * 1, gcd * (sum - 1)};
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    auto best = getbest(n, 1);
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        auto f = i, f2 = n / i;
        auto got = getbest(f2, f);
        auto got2 = getbest(f, f2);
        best = min(best, got);
        best = min(best, got2);
      }
    }
    auto [_, x, y] = best;
    cout << x << " " << y << '\n';
  }
}
