// ad-hoc, only store necessary information (store length otherwise)
// https://codeforces.com/contest/1280/problem/A

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
constexpr auto MOD = 1'000'000'007;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
    while(T--) {
      int x;
      cin >> x;
      string s;
      cin >> s;
      vector<int> a(s.length());
      for (int i = 0; i < s.length(); i++) {
	      a[i] = s[i] - '0';
      }

      ll extra = 0;
      ll right = s.length();
      for (int i = 0; i < x; i++) {
        right--;
        auto init_right = right;
        vector<int> relems;
        for (int k = 0; k < (a[i] - 1); k++) {
          if (a.size() <= x) {
            if (relems.empty()) {
              copy(next(begin(a), i + 1), end(a), back_inserter(relems));
            }
            copy(begin(relems), end(relems), back_inserter(a));
          } else {
            extra = (extra + init_right) % MOD;
          }
          right = (right + init_right) % MOD;
        }
      }
      ll sol = (extra + a.size()) % MOD;
      cout << sol << '\n';
    }
}
