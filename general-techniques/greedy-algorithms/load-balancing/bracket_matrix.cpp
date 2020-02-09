// greedy, valid brackets, keeping rows balanced by swapping column-wise
// https://prognova18.kattis.com/problems/bracketmatrix
// 2018 ProgNova

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a), end(a)
#define sz(a) (int)size(a)

// open = 0, closed = 1

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  auto grid = vector(n, vector<char>(n));
  trav(r, grid) {
    trav(e, r) {
      cin >> e;
    }
  }

  auto bycol = vector(n, vector<int>(2));
  rep(j, 0, n) {
    rep(i, 0, n) {
      if (grid[i][j] == '(') {
        bycol[j][0]++;
      } else {
        bycol[j][1]++;
      }
    }
  }

  auto feasible = true;
  auto byrow = vector<int>(n);
  rep(j, 0, n) {
    sort(all(byrow));
    trav(cnt, byrow) {
      if (cnt == 0 && bycol[j][0] == 0) {
        feasible = false;
      }
      if (bycol[j][0] > 0) {
        --bycol[j][0];
        cnt++;
      } else {
        --bycol[j][1];
        cnt--;
      }
    }
  }
  trav(elem, byrow) {
    if (elem != 0) feasible = false;
  }
  
  cout << (feasible ? "Yes" : "No") << '\n';
}
