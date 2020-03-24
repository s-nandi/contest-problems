// bs on ans, greedy
// https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3f5b
// 2020 Kickstart A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)a.size()

void maxx(int& a, int b) {a = max(a, b);}

bool feasible(const vector<ll>& v, int k, ll g) {
    int rem = k;
    ll curr = v[0];
    rep(i, 1, sz(v)) {
        if (v[i] > curr + g) {
            int needed = (v[i] - curr + g - 1) / g - 1;
            curr += (needed) * g;
            rem -= needed;
        }
        maxx(curr, v[i]);
    }
    return rem >= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        int n, k;
        cin >> n >> k;
        vector<ll> a(n);
        trav(i, a) cin >> i;
        ll lo = 1, hi = 1000000000;
        while (lo < hi) {
            auto mid = lo + (hi - lo) / 2;
            auto res = feasible(a, k, mid);
            if (res) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        auto sol = lo;
        cout << "Case #" << test << ": " << sol << '\n';
    }
}
