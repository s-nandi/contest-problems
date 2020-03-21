// manacher algorithm (longest palindromic prefix), greedy
// https://codeforces.com/contest/1326/problem/D2

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
 
auto manacher(const string &s) {
    auto pal = vector(2, vi(sz(s)));
    for (int even = 0; even < 2; even++) {
        for (int i = 0, l = 0, r = -1; i < sz(s); i++) {
            int k = (i > r) ? !even : min(pal[even][l + r - i + even], r - i + even);
            while (0 <= i - k - even and i + k < sz(s) and s[i - k - even] == s[i + k])
                k++;
            pal[even][i] = k--;
            if (i + k > r)
                l = i - k - even, r = i + k;
        }
    }
    return pal;
}

auto lpps(const auto& pal) {
    auto best = pair{0, -1};
    int n = sz(pal[0]);
    for (int even = 0; even < 2; even++) {
        for (int i = 0; i < n; i++) {
            if (pal[even][i]) {
                int l = i - pal[even][i] + !even, r = i + pal[even][i] - 1;
                auto pref_or_suff = l == 0 or r == n - 1;
                if (pref_or_suff and r - l + 1 > best.second - best.first + 1)
                    best = pair{l, r};
            }
        }
    }
    return best;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = sz(s);
 
        auto [fit, rit] = mismatch(begin(s), begin(s) + n / 2, rbegin(s));
        int len = fit - begin(s);
        
        auto table = manacher(s.substr(len, n - 2 * len));
        auto [l, r] = lpps(table);
        
        auto left = s.substr(0, len);
        auto mid = s.substr(len + l, r - l + 1);
        auto right = s.substr(n - len, len);
        cout << left << mid << right << '\n';
    }    
}
