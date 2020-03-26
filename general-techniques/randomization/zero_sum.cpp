// randomized (proving runtime w/ random walk expectation), dp (knapsack w/ small weights)
// https://codeforces.com/group/ZFgXbZSjvp/contest/273473/problem/A
// 2020 NAPC -1

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)

const ll INF = 1e16;
auto minn(auto& a, auto b){a = min(a, b);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937 mt{(unsigned)chrono::high_resolution_clock::now().time_since_epoch().count()};

    int n, k;
    cin >> n >> k;
    
    vi indices(n);
    iota(all(indices), 0);
    shuffle(all(indices), mt);
    
    auto a = vector(n, vi(2 * k + 1));
    rep(i, 0, n)
        trav(elem, a[indices[i]])
            cin >> elem;

    int lim = int(2 * k * sqrt(n) + 5);
    auto dp = vector(n + 1, vector<ll>(2 * lim + 1, INF));
    dp[0][lim] = 0;
    rep(i, 0, n) {
        rep(j, 0, size(dp[i])) {
            if (dp[i][j] == INF) continue;
            rep(delta, -k, k + 1) {
                if (j + delta < 0 or j + delta >= size(dp[0])) continue;
                minn(dp[i + 1][j + delta], dp[i][j] + a[i][delta + k]);
            }
        }
    }
    cout << dp[n][lim] << '\n';
}
