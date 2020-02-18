// Divide and Conquer DP (monotone on # of people), 2D prefix sums
// https://codeforces.com/contest/321/problem/E
// Note: Runtime is dominated by i/o, runs in ~800ms with a fast i/o template 

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
using vi = vector<int>;

const int MAXN = 4000 + 10;
const int MAXK = 800 + 10;
const int INF = 1031231234;

vi dp(MAXN), old(MAXN, INF);
int cost[MAXN][MAXN], psums[MAXN][MAXN];

bool minn(auto& a, auto b) {
    if (b < a) {a = b; return true;}
    return false;
}

void dac_dp(int lo, int hi, int l, int r) {
    if (lo > hi || l > r) return;
    int i = (lo + hi) / 2;
    int m = l; dp[i] = INF;
    rep(k, l, min(r, i) + 1)
        if (minn(dp[i], old[k - 1] + cost[k][i]))
            m = k;
    dac_dp(lo, i - 1, l, m);
    dac_dp(i + 1, hi, m, r);
}

struct SubMatrix {
    SubMatrix(int n) {
        rep(r,1,n+1) rep(c,1,n+1)
            psums[r+1][c+1] = cost[r][c] + psums[r][c+1] + psums[r+1][c] - psums[r][c];
    }
    int sum(int u, int l, int d, int r) {
        return psums[d][r] - psums[d][l] - psums[u][r] + psums[u][l];
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    rep(i, 1, n + 1) {
        rep(j, 1, n + 1) {
            getchar();
            cost[i][j] = getchar() - '0';
        }
    }
    
    SubMatrix sm(n);
    rep(i, 1, n + 1)
        rep(j, i, n + 1)
            cost[i][j] = sm.sum(i, i, j + 1, j + 1) / 2;
    
    old[0] = 0;
    rep(j, 1, k + 1) {
        dac_dp(1, n, 1, n);
        swap(dp, old);
    }
    printf("%d\n", old[n]);
}
