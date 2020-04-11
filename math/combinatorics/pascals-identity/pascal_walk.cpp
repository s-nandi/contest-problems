// constructive, pascal triangle (sum of row is power of 2), greedy
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1353
// 2020 GCJ 1A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int num_tests;
  cin >> num_tests;
  for (int test_num = 1; test_num <= num_tests; test_num++) {
    int n;
    cin >> n;
    
    vi take(31);
    bool first = true;
    for (int x = 30, rem = n; x >= 0; x--) {
      auto cost = (1LL << x) + (first ? x : 0);
      if (rem >= cost) {
        take[x] = true;
        rem -= cost;
        first = false;
      }
    }
    bool left = true;
    vector<pair<int, int>> sol;
    for (int x = 0, acc = 0; acc < n; x++) {
      if (x < sz(take) and take[x]) {
        int lb = left ? 0 : x;
        int rb = left ? x : 0;
        int delta = left ? 1 : -1;
        for (int i = lb; i != rb + delta; i += delta)
          sol.PB({x, i});
        acc += (1 << x);
        left = !left;
      } else {
        int pos = left ? 0 : x;
        sol.PB({x, pos});
        acc++;
      }
    }
    cout << "Case #" << test_num << ": ";
    cout << '\n';
    trav(elem, sol)
      cout << elem.first + 1 << " " << elem.second + 1 << '\n';
  }
}
