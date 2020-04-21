// inverse edit distance, bounding # of distinct rows in an edit distance table (-1,0,1)
// https://open.kattis.com/problems/editingexplosion
// 2020 North American Championships
// Note: There are automata-based solutions, check judge solutions for details
//       Also, this is a dp on bitmasks in disguise, we could have encoded rows into
//       base-3 masks

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

const int MOD = 998244353;
const int MAXL = 20 + 5;
map<vi, int> dp[MAXL];

auto minn(auto& a, auto b){a = min(a, b);}
auto add(auto& a, auto b){a = (a + b) % MOD;}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int d, n;
    cin >> s >> d;
    n = sz(s);

    /*
     * Why is init length n + 1 instead of n + d + 1? 
     * Explanation:
     * It's important that the vectors in dp[i] represent the edit dist when comparing
     * all of s against a specific i-length prefix of the target string, NOT vice-versa,
     * since we need to minimize vector length, ie. want n len vecs instead of n+d len
     * Need to minimize vector length since complexity includes a 3^len term
     */
    auto res = 0LL;
    vi init(n + 1);
    iota(all(init), 0);
    dp[0][init] = 1;
    rep(i, 1, n + d + 1) { // <= 20 iterations
        for (const auto& [row, cnt]: dp[i - 1]) { // <= 3 ^ sz(row) <= 3 ^ 10 iterations
            for (char ch = 'A'; ch <= 'Z'; ch++) { // 26 iterations
                vi nrow(n + 1);
                nrow[0] = i; // distance between i-long prefix of target and empty str
                rep(j, 1, n + 1) { // <= 20 iterations
                    nrow[j] = nrow[j - 1] + 1;
                    minn(nrow[j], row[j] + 1);
                    minn(nrow[j], row[j - 1] + (ch != s[j - 1]));
                }
                add(dp[i][nrow], cnt);
            }
        }
    }
    rep(i, 0, n + d + 1) {
        for (const auto& [row, cnt]: dp[i]) {
            if (row.back() == d)
                add(res, cnt);
        }
    }
    cout << res << '\n';
}
