// mex, 2 pointer, DP (cover range with intervals)
// https://codeforces.com/group/ZFgXbZSjvp/contest/273473/problem/H
// 2020 NAPC -2

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)

const int MOD = 998244353;

int mex(vi a) {
    sort(all(a));
    rep(i, 0, sz(a) + 1)
        if (!binary_search(all(a), i))
            return i;
    return -1;
}

struct mexer {
    set<int> holes;
    map<int, int> freq;
    mexer(int n) {rep(i, 0, n + 1) holes.insert(i);}
    void push(int i) {if (++freq[i] == 1) holes.erase(i);}
    void pop(int i){ if (--freq[i] == 0) holes.insert(i);}
    int get() { return *holes.begin(); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vi a(n);
        trav(i, a) cin >> i;
        auto need = mex(a);
        vi r(n + 1);
        mexer mx(n + 1);
        for (int i = 0, j = 0; i < n; i++) {
            if (j <= i)
                mx.push(a[j++]);
            while (j < n and mx.get() != need)
                mx.push(a[j++]);
            r[i] = mx.get() == need ? j - 1 : -1;
            mx.pop(a[i]);
        }
        vector<ll> suff(n + 1), dp(n + 1);
        dp[n] = suff[n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            if (r[i] != -1)
                dp[i] = suff[r[i] + 1];
            suff[i] = (dp[i] + suff[i + 1]) % MOD;
        }
        cout << dp[0] << '\n';
    }
}
