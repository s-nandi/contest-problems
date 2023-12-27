// greedy (op1 op2 alternating is optimal after zero-ing out, because you can't gain points at both i, j -- let i < j, since we add +1 to a prefix, a[i] >= a[j], but to gain points, we need a[i] < a[j]), initial op1 is <= 2n since alternating is just as good otherwise
// https://codeforces.com/contest/1917/problem/C 

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (auto i = (a); i < (b); ++i)
#define trav(a, x) for (auto& a : x)

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(10) << fixed;

    int T;
    cin >> T;
    while(T--) {
        int n, k, d;
        cin >> n >> k >> d;
        vector<int> a(n);
        vector<int> v(k);

        trav(i, a) {
            cin >> i;
        }
        trav(i, v) {
            cin >> i;
        }

        int num_match = 0;
        rep(i, 0, n) {
            if (a[i] == i + 1) {
                num_match++;
            }
        }

        auto best = 0;
        auto a_after = a;
        rep(first_op1, 0, min(d, 2 * n + 2)) {
            auto rem = d - (first_op1 + 1);
            auto possible = num_match + rem / 2;
            best = max(best, possible);

            auto b_val = v[first_op1 % k];
            rep(i, 0, b_val) {
                if (a_after[i] == i + 1) {
                    num_match--;
                }
                a_after[i]++;
                if (a_after[i] == i + 1) {
                    num_match++;
                }
            }
        }
        cout << best << '\n';
    }
}
