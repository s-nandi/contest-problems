// dp (state reduction, bitmasks, space saving), greedy (sort then dp)
// https://codeforces.com/contest/1316/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(int i = a; i < (b); ++i)

const int MAXP = 7;
const int MAXN = 100'000 + 5;
ll dp[2][1 << MAXP];
pair<int, int> a[MAXN];
int b[MAXN][MAXP];

void maxx(auto& a, auto b) {a = max(a, b);}

int main() {
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);
    rep(i, 0, n) {
      scanf("%d", &a[i].first);
      a[i].second = i;
    }
    rep(i, 0, n) {
      rep(j, 0, p) {
	scanf("%d", &b[i][j]);
      }
    }
    sort(begin(a), begin(a) + n, greater<>{});

    auto acc = accumulate(begin(a), begin(a) + k, 0LL, [](auto a, const auto& b){return a + b.first;});
    memset(dp, -1, sizeof(dp));
    dp[0][0] = acc; // i, j, k => first i people considered, bm j positions filled
    // init assuming those w/ highest k audience scores are used as audience members
    rep(it, 0, n) {
      auto i = it & 1;
      auto i2 = i ^ 1;
      auto ind = a[it].second;
      rep(j, 0, (1 << p)) {
	if (dp[i][j] == -1) continue;
	auto num = __builtin_popcount(j); // state-reduction; avoids additional O(p) term
	maxx(dp[i2][j], dp[i][j]); // don't use ind as teammate
	rep(pos, 0, p) {
	  if (j & (1 << pos)) continue;
	  auto j2 = j | (1 << pos);
	  // If current dp[i][j] includes ind's audience score (ie. it < num + k),
	  // remove this score and add the next best audience score (score of num + k)
	  auto audience_delta = (it < num + k) ? a[num + k].first - a[it].first : 0LL;
	  maxx(dp[i2][j2], dp[i][j] + b[ind][pos] + audience_delta); // use ind as teammate pos
	}
      } // No need to reset dp[i] since dp[i2][j] >= dp[i][j]
    }
    auto best = dp[n & 1][(1 << p) - 1];
    printf("%I64d\n", best);
}
