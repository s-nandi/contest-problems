// greedy, string processing
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05
// 2019 Google Code Jam - Round 1A

#include <bits/stdc++.h>
using namespace std;

string suffix(const string& a, int len) { return a.substr(a.length() - len, len); }

int longest_common_suffix(const string& a, const string& b) {
  auto it = mismatch(a.rbegin(), a.rend(), b.rbegin());
  return it.first - a.rbegin();
}

using matching = tuple<int, int, int>;  // length, string i, string j

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  for (int test = 1; test <= T; test++) {
    int n;
    cin >> n;
    vector<string> words(n);
    for (auto& word : words) {
      cin >> word;
    }

    vector<matching> matches;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        auto lcs = longest_common_suffix(words[i], words[j]);
        for (int k = 1; k <= lcs; k++) {
          matches.push_back({k, i, j});
        }
      }
    }
    sort(matches.begin(), matches.end(), greater<>());

    int result = 0;
    set<string> used_suffix;
    vector<int> used_string(n);
    for (const auto& match : matches) {
      int len, i, j;
      tie(len, i, j) = match;
      auto curr_suffix = suffix(words[i], len);

      if (used_string[i] or used_string[j]) continue;
      if (used_suffix.count(curr_suffix)) continue;

      used_string[i] = used_string[j] = true;
      used_suffix.insert(curr_suffix);
      result += 2;
    }
    cout << "Case #" << test << ": " << result << '\n';
  }
}
