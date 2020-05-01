// binary search, maintaining invariant (answer always reachable after i decisions)
// https://codeforces.com/contest/1348/problem/D

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)

ll minget(ll x, ll cnt, int rem) {
  return x + cnt * rem;
}

ll maxget(ll x, ll cnt, int rem) {
  rep(i, 0, rem) {
    cnt *= 2;
    x += cnt;
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    
    int steps = 0;
    while ((1LL << steps) <= n) steps++;
    steps--;

    int curr = 1;
    int cnt = 1;
    int rem = steps;
    vi sol(steps);
    rep(i, 0, steps) {
      int lo = 0, hi = cnt;
      int choice = -1;
      while (lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        auto ncnt = cnt + mid;
        auto ncurr = curr + ncnt;
        auto nrem = rem - 1;
        if (minget(ncurr, ncnt, nrem) > n) {
          hi = mid - 1;
        } else if (maxget(ncurr, ncnt, nrem) < n) {
          lo = mid + 1;
        } else {
          choice = mid;                    
          break;
        }
      }
      sol[i] = choice;
      cnt += sol[i];
      curr += cnt;
      rem--;
    }
    cout << sz(sol) << '\n';
    trav(i, sol) cout << i << " ";
    cout << '\n';
  }
}
