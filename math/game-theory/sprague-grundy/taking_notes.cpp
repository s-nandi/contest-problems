// sprague-grundy (pattern), each turn can remove from pile (or not) and split into 2 non-empty sets
// https://www.codechef.com/problems/HCODE02

#include <bits/stdc++.h>
using namespace std;

const int MAX_TEST = 50;
int dp[MAX_TEST + 5];
int sprague_grundy(int pile) {
  if (dp[pile] != -1) return dp[pile];
  vector<int> achieved;
  achieved.reserve((pile + 1) * (pile + 1));
  for (int removed = 0; removed <= pile; removed++) {
    int remaining = pile - removed;
    for (int partition1 = 1; partition1 < remaining; partition1++) {
      int partition2 = remaining - partition1;
      assert(partition1 > 0 and partition2 > 0);
      achieved.push_back(sprague_grundy(partition1) ^ sprague_grundy(partition2));
    }
  }
  int mex = 0;
  sort(begin(achieved), end(achieved));
  achieved.erase(unique(begin(achieved), end(achieved)), end(achieved));
  for (int i: achieved) {
    if (mex != i) break;
    mex = i + 1;
  }
  dp[pile] = mex;
  return mex;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // Check formula
  memset(dp, -1, sizeof(dp));
  for (int i = 1; i <= MAX_TEST; i++)
    assert(sprague_grundy(i) == i - 1);

  int n;
  cin >> n;
  vector<int> a(n);
  for(auto& i: a) cin >> i;
  auto res = 0;
  for(auto& i: a) res ^= i - 1;
  cout << (res ? 1 : 2) << '\n';
}
