// greedy (if pos p mod k is kept 1, no other mod k can contain 1), digit dp
// https://codeforces.com/contest/1353/problem/E

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

const int MAXN = 1000000;
const int INF = 1031231234;
int dp[MAXN + 5][3]; // i, stage (before start, during, after end)

auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    
    int total = 0;
    trav(c, s) total += (c == '1');

    int best = INF;
    rep(start, 0, k) {
      vi groups;
      int len = 0;
      int oneshere = 0;
      for (int i = start; i < n; i += k) {
        if (i > start and s[i] != s[i - k]) {
          groups.PB(len);
          len = 1;
        } else len++;
        oneshere += (s[i] == '1');        
      }
      groups.PB(len);

      int gsz = sz(groups);
      rep(i, 0, gsz + 1) rep(j, 0, 3)
        dp[i][j] = INF;
      dp[0][0] = dp[0][1] = dp[0][2] = 0;
      rep(i, 0, gsz) {
        bool iszero = (s[start] == '1') ? (i & 1) : (~i & 1);
        int switchtozero = iszero ? 0 : groups[i];
        int switchtoone = !iszero ? 0 : groups[i];
        minn(dp[i + 1][0], dp[i][0] + switchtozero);
        minn(dp[i + 1][1], dp[i][0] + switchtoone);
        minn(dp[i + 1][1], dp[i][1] + switchtoone);
        minn(dp[i + 1][2], dp[i][1] + switchtozero);
        minn(dp[i + 1][2], dp[i][2] + switchtozero);
      }
      auto minswitch = *min_element(all(dp[gsz]));
      auto possible = minswitch + (total - oneshere);
      minn(best, possible);
    }
    cout << best << '\n';
  }
}
