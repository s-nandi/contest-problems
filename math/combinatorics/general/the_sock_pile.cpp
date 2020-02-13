// expected value, dp, combinatorics (casework)
// https://nena19.kattis.com/problems/thesockpile
// 2019 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)

constexpr auto MAXN = 505;
const auto sentinel = -1.0L;
long double P[MAXN][MAXN][MAXN];

auto choose2(auto num) {
    return num * (num - 1) / 2;
}

long double solve(int n, int m, int w) {
    if (n < 0 or m < 0 or w < 0) return 0.0L;
    if (2 * n + m + w < 2) return 1.0L;
    if (P[n][m][w] != sentinel) {
        return P[n][m][w];
    }
    auto c1 = 2 * n * w * solve(n - 1, m + 1, w - 1);
    auto c2 = m * w * solve(n, m - 1, w - 1);
    auto c3 = choose2(m) * solve(n, m - 2, w);
    auto c4 = n * (2 * n - 2) * solve(n - 2, m + 2, w);
    auto c5 = 2 * n * m * solve(n - 1, m, w);
    auto denom = choose2(2 * n + m + w);
    auto res = (c1 + c2 + c3 + c4 + c5) / denom;
    P[n][m][w] = res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    rep(i, 0, MAXN) rep(j, 0, MAXN) rep(k, 0, MAXN) {
        P[i][j][k] = sentinel;
    }
    auto sol = solve(m, 0, n);
    cout << fixed << setprecision(11) << sol << '\n';
    
}
