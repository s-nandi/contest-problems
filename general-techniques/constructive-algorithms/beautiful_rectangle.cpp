// greedy (remove most occuring element till feasible), constructive (filling grid diagonally)
// https://codeforces.com/contest/1277/problem/F

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using ii = pair<int, int>;
 
auto middle_factor(int n) {
  ll res = 1;
  for (ll i = sqrt(n); i >= 1; i--) {
    if (n % i == 0)
      return i;
  }
  return res;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;
 
    map<int, int> cnt;
    for (auto i: a)
      cnt[i]++;
    
    priority_queue<ii, vector<ii>, less<ii>> pq;        
    for (auto [i, c]: cnt)
      pq.push({c, -i}); // tiebreak by removing smaller elements first; not actually needed
 
    int sz = n;
    while(true) {
      auto [c, val] = pq.top();
      pq.pop();
  
      if (c <= middle_factor(sz)) {
        pq.push({c, val});
        break;
      } else {
        sz--;
        if (--c > 0)
            pq.push({c, val});
      }
    }
    
    auto w = middle_factor(sz);
    auto h = sz / w;
  
    vector<int> nums;
    while(!pq.empty()) {
      auto [c, val] = pq.top();
      pq.pop();
      for (int i = 0; i < c; i++)
        nums.push_back(-val);
    }
 
    int i = 0, j = 0;
    vector<vector<int>> grid(h, vector<int>(w, -1));
    for(int it = 0; it < sz; it++) {
      if (grid[i][j] != -1) j = (j + 1) % w;      
      grid[i][j] = nums[it];
      
      i = (i + 1) % h;
      j = (j + 1) % w;
    }
 
    cout << sz << '\n';
    cout << h << " " << w << '\n';
    for (auto& row: grid) {
      for (auto& elem: row)
        cout << elem << " ";
      cout << '\n';
    }
}
