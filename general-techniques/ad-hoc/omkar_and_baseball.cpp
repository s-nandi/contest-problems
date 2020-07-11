// adhoc, can always be done in 2 operations (rotate all fixed points -- a[i] == i in 1 step, then permute the entire array in 1 step)
// https://codeforces.com/contest/1372/problem/C

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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) {cin >> i; --i;}

    if (is_sorted(all(a))) {
      cout << 0 << '\n';
    } else {
      int best = 1;

      deque<int> d(all(a));
      int head = 0;
      while (!empty(d) and d.front() == head) {
        d.pop_front();
        head++;
      }
      int tail = n - 1;
      while (!empty(d) and d.back() == tail) {
        d.pop_back();
        tail--;
      }
      auto sorted = d;
      sort(all(sorted));
      rep(i, 1, sz(sorted))
        assert(sorted[i] == sorted[i - 1] + 1);

      int curr = sorted[0];
      trav(i, d) {
        if (i == curr) {
          best = 2;
        }
        curr++;
      }
      cout << best << '\n';
    } 
  }
}
