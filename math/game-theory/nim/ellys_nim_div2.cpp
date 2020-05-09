// nim (adding > 1024 stones is never useful in this problem), dp
// Topcoder: EllysNimDiv2 [SRM 785 Div 2 1000 pt]

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()

const int MAXN = 50;
const int MAXB = 1 << 11;
int dp[MAXN + 5][MAXB + 5];

void minn(int& a, int b) {
  if (a == -1 and b != -1) a = b;
  else a = min(a, b);
}

struct EllysNimDiv2 {
  int getMin(vi a) {
    memset(dp, -1, sizeof(dp));
    int n = sz(a);
    dp[0][0] = 0;
    rep(i, 0, n) {
      rep(bm, 0, MAXB) {
        if (dp[i][bm] == -1) continue;
        rep(transition, 0, MAXB) {
          auto nv = a[i] + transition;
          auto nbm = bm ^ nv;
          if (nbm >= MAXB) continue;
          minn(dp[i + 1][nbm], dp[i][bm] + transition);
        }
      }
    }
    return dp[n][0];
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  EllysNimDiv2 solver;
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  cout << solver.getMin(a) << '\n';
}
