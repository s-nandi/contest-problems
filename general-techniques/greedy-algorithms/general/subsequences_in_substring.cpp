// greedy, fixing left endpoint and finding all valid right endpoints
// https://naipc19.kattis.com/problems/subsequencesinsubstrings
// 2019 NAIPC

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int index(char c) { return c - 'a'; }

int find_first_bigger(const vector<int>& v, int elem) {
  return *upper_bound(v.begin(), v.end(), elem);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  string s, t;
  cin >> s >> t;
  int n = s.length();
  int m = t.length();

  vector<int> char_positions[26];  // 0-indexed positions of letter i
  for (int i = 0; i < n; i++) {
    char_positions[index(s[i])].push_back(i);
  }
  for (int k = 0; k < 26; k++) {
    char_positions[k].push_back(n);  // sentinel
  }

  ll sol = 0;
  for (int l = 0; l < n; l++) {
    // For each l, find the smallest right endpt r s.t. t is a subsequence in substring s[l, r]
    int r = l - 1;
    bool contains = true;
    for (int j = 0; j < m; j++) {
      r = find_first_bigger(char_positions[index(t[j])], r);
      if (r >= n) break;
    }
    if (r < n) {
      sol += n - r;
    }
  }
  cout << sol << '\n';
}
