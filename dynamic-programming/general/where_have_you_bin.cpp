// fixing permutations, dp (space-saving), optimally placing spaces in order to minimize differences
// https://open.kattis.com/problems/wherehaveoubin
// 2019 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto INF = 1231231234;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.length();

  vector<int> bins(n);
  for (auto &i : bins) {
    cin >> i;
  }
  s.insert(begin(s), 'X'); // 1-index
  bins.insert(begin(bins), 0); // same as above

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int pos;
    cin >> pos;
    s[pos] = 'X';
    bins[pos] = 0;
  }

  map<char, int> counts;
  for (auto c : s) {
    if (c != 'X')
      counts[c]++;
  }

  string additions;
  cin >> additions;
  if (additions != "X") {
    for (auto c : additions) {
      counts[c]++;
    }
  }

  auto final_x = n;
  string alphabet = "";
  for (auto [c, count] : counts) {
    final_x -= count;
    alphabet += c;
  }

  int best = INF;
  do {
    string tape = "";
    for (auto c : alphabet) {
      for (int i = 0; i < counts[c]; i++) {
        tape += c;
      }
    }
    int len = tape.length();
    tape.insert(begin(tape), 'X');

    auto dp = vector(len + 1, vector<int>(final_x + 1, INF));
    dp[0][0] = 0;
    for (int i = 0; i <= len; i++) {
      for (int j = 0; j <= final_x; j++) {
	int pos = i + j;
        if (i == 0 and j == 0)  continue;

	// Case 1: Assign the pos-th bin to company tape[i]
	if (i >= 1) {
	  auto possible = dp[i - 1][j] + (s[pos] != tape[i] ? bins[pos] : 0);
	  dp[i][j] = min(dp[i][j], possible);
	}
	// Only allow empty bin at start or between bins belonging to different companies
	auto transition = i == 0 or tape[i] != tape[i + 1];
	// Case 2: Assign the pos-th bin to be empty
	if (j >= 1 and transition) {
	  auto possible =  dp[i][j - 1] + (s[pos] != 'X' ? bins[pos] : 0);
	  dp[i][j] = min(dp[i][j], possible);
	}
      }
    }
    auto possible = dp[len][final_x];
    best = min(possible, best);
  } while (next_permutation(begin(alphabet), end(alphabet)));
  cout << best << '\n';
}
