// congruence groups, amortized analysis, fix snooze period
// https://codesprintla20-team.kattis.com/problems/codesprintla20.snoozedalarm

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

const int INF = 1031231234;
const int MAXN = 1500;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  vi freq(MAXN);
  trav(i, a) {cin >> i; freq[i]++;}

  int best = INF;
  rep(diff, 1, MAXN) {
    int possible = 0;
    auto cnt = freq;
    for (int i = 0; i < MAXN; i++) {
      while (cnt[i]) {
        possible++;
        for (int j = i; j < MAXN and cnt[j]; j += diff)
          --cnt[j];
      }
    }
    best = min(best, possible);
  }
  cout << best << " " << n << '\n';
}
