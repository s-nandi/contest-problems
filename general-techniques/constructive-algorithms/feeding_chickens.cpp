// constructive algorithm, zigzag path to get contiguous partitions, greedy
// https://codeforces.com/contest/1255/problem/D

#include <bits/stdc++.h>
using namespace std;

char mapping(int i) {
  return i < 10 ? '0' + i : (i < 36 ? (i - 10) + 'a' : (i - 36) + 'A');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int r, c, k;
    cin >> r >> c >> k;

    int num_rice = 0;
    auto grid = vector(r, vector<char>(c));
    for (auto& row: grid) {
      for (auto& elem: row) {
	cin >> elem;
	num_rice += (elem == 'R');
      }
    }

    auto target = num_rice / k + (num_rice % k != 0);
    auto num_large = num_rice % k;

    auto curr = 0;
    auto contained = 0;
    auto sol = vector(r, vector<char>(c));
    for (int i = 0; i < r; i++) {
      int start = 0, delta = 1;
      if (i & 1)
	start = c - 1, delta = -1;

      for (int j = start; j >= 0 && j < c; j += delta) {
	sol[i][j] = mapping(curr);
	contained += (grid[i][j] == 'R');

	if (curr + 1 < k and contained == target) {
	  curr++;
	  contained = 0;
	  if (curr == num_large) --target;
	}
      }
    }
      
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
	cout << sol[i][j];
      }
      cout << '\n';
    }
  }
}
