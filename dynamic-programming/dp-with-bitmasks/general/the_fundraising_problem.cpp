// dp with bitmasks, enumerating submasks
// https://www.hackerrank.com/contests/hack-the-interview-u-s-2/challenges/charity

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

int n, m, t, lim;
int charm[20][20];
ll dp[16][1 << 16];
vi groups[15];
vi tables[1 << 15];
ll costs[16][1 << 16];
vector<int> guests[20];

ll max_dot_product(int group, int tables_bm) {
  vi& a = groups[group];
  vi& b = tables[tables_bm];
  if (sz(b) > sz(a)) return -1;
  auto best = 0LL;
  rep(i, 0, sz(b)) {
    best += (ll) b[i] * a[i];
  }
  return best;
}

template <typename T>
void maxx(T& a, T b) {
  if (a < b) a = b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tc;
  cin >> tc;
  while(tc--) {
    cin >> n >> m >> t;
    rep(i, 0, n) {
      rep(j, 0, m) {
        cin >> charm[i][j];
      }
    }
    rep(i, 0, t) {
      guests[i].clear();
      int x;
      cin >> x;
      rep(j, 0, x) {
        int v;
        cin >> v;
        guests[i].PB(v);
      }
    }
    cin >> lim;

    rep(it, 0, n) {
      groups[it].clear();
      groups[it].resize(m * lim);
      int pos = 0;
      rep(i, 0, m) {
        rep(j, 0, lim) {
          groups[it][pos] = charm[it][i];
          pos++;
        }
      }
      sort(all(groups[it]), greater<>{});
    }
    rep(it, 0, 1 << t) {
      tables[it].clear();
      rep(i, 0, t) {
        if ((1 << i) & it) {
          trav(val, guests[i]) {
            tables[it].PB(val);
          }
        }
      }
      sort(all(tables[it]), greater<>{});
    }

    rep(i, 0, n) {
      rep(bm, 0, (1 << t)) {
        costs[i][bm] = max_dot_product(i, bm);
      }
    }
      
    auto FULL = (1 << t) - 1;
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    rep(i, 0, n) {
      rep(bm, 0, (1 << t)) {
	      if (dp[i][bm] < 0) continue;
        auto inv = FULL - bm;
        for (int sm = inv; sm; sm = (sm - 1) & inv) {
          if (costs[i][sm] < 0) continue;
            maxx(dp[i + 1][bm | sm], dp[i][bm] + costs[i][sm]);
        }
        maxx(dp[i + 1][bm], dp[i][bm]);
      }
    }
    cout << dp[n][FULL] << '\n';
  }
}
