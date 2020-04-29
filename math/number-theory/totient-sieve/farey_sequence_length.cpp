// totient sieve, prefix sums
// https://open.kattis.com/problems/farey
// 2015 Greater NY Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a);i<(b);++i)

const int MAXN = 10000;
int phi[MAXN + 5];
bool comp[MAXN + 5];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  phi[1] = 1;
  rep(i, 2LL, MAXN + 1) if (!comp[i]) {
    phi[i] = i - 1;
    rep(j, 2, MAXN / i + 1) {
      comp[i * j] = true;
      phi[i * j] = j % i ? phi[i] * phi[j] : i * phi[j];
    }
  }
  vector<int> ps(MAXN + 1);
  ps[0] = 1; // (0 / n) is also contained in a n-length farey sequence
  for (int i = 1; i <= MAXN; i++)
    ps[i] = ps[i - 1] + phi[i];

  int T;
  cin >> T;
  while (T--) {
    int tnum, n;
    cin >> tnum >> n;
    cout << tnum << " " << ps[n] << '\n';
  }
}
