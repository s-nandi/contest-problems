// Greedy (Exchange argument), proof by symmetry
// https://open.kattis.com/problems/piecesofparentheses
// NAIPC 2017

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using vi = vector<int>;

const int INF = 1031231234;
const int MAXD = (300 * 300) + 100;

bool maxx(auto& a, auto b) {
    if (a < b) {a = b; return true;}
    return false;
}

using state = tuple<int, int, int, int>; // left close, right open, total diff, len
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int total_len = 0;
    vector<string> a(n);
    trav(i, a) {
        cin >> i;
        total_len += sz(i);
    }

    vector<state> s(n);
    rep(i, 0, n) {
        // lc = # of closed paran on left after cancelling out self-matches
        // ro = # of right paran on right after cancelling out self-matches
        int cnt = 0, lc = 0, ro = 0;
        trav(c, a[i])
            lc = max(lc, cnt += (c == ')') ? 1 : -1);
        reverse(all(a[i])); cnt = 0;
        trav(c, a[i])
            ro = max(ro, cnt += (c == ')') ? -1 : 1);
        s[i] = {lc, ro, ro - lc, sz(a[i])};
    }

    // Easier to understand if you view the right-half as a reflection of the left
    // The comparator makes sense on the left-half, and must be symmetric
    sort(all(s), [&](state s1, state s2) {
                     auto [lc1, ro1, delta1, len1] = s1;
                     auto [lc2, ro2, delta2, len2] = s2;
                     if (delta1 > 0 and delta2 <= 0) {
                         return true;
                     } else if (delta1 <= 0 and delta2 > 0) {
                         return false;
                     } else if (delta1 <= 0 and delta2 <= 0){
                         return tie(ro2, delta1) < tie(ro1, delta2);
                     } else if (delta1 > 0 and delta2 > 0) {
                         return tie(lc1, delta2) < tie(lc2, delta1);
                     } else assert(false);
                 });

    // dp[i][j + offset] = max len using first i strings w/ acc of j
    auto dp = vector(n + 1, vector<int>(2 * MAXD + 100, -INF)); 
    auto offset = MAXD;
    dp[0][offset] = 0;
    rep(i, 0, n) {
        auto [lclose, ropen, delta, len] = s[i];
        rep(j, 0, sz(dp[i])) {
            if (dp[i][j] == -INF) continue;
            maxx(dp[i + 1][j], dp[i][j]);
            if (j - offset >= lclose && j + delta >= 0 && j + delta  < sz(dp[i]))
                maxx(dp[i + 1][j + delta], dp[i][j] + len);
        }
    }
    auto res = dp[n][offset];
    cout << res << '\n';
}
