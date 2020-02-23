// binary search on answer, greedy matching (max element pairs with largest possible)
// https://open.kattis.com/problems/icpccamp
// 2020 North American Championship

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)

const int INF = 1000000000 + 100;

auto check(const auto& p, const auto& q, int s, int d) {
    int days = 0;
    auto qs = q;
    trav(i, p) {
        auto ub = min(s - i, i + d);
        auto lb = i - d;
        // Find highest element <= ub
        auto it = qs.upper_bound(ub);
        if (it == begin(qs)) continue;
        else --it;
        // Check that element found is >= lb
        if ((it -> first) < lb) continue;
        // Use element and remove
        days++;
        if (--(it -> second) == 0)
            qs.erase(it);
    }
    return days;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b, s;
    cin >> n >> a >> b >> s;

    vi p(a), q(b);
    trav(i, p) cin >> i;
    trav(i, q) cin >> i;
    sort(all(p), greater<>{});
    sort(all(q), greater<>{});
    map<int, int> qs;
    trav(i, q)
        qs[i]++;

    bool feasible = false;
    int lo = 0, hi = INF;
    while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        auto possible = check(p, qs, s, mid);
        if (possible >= n) {
            hi = mid;
            feasible = true;
        } else {
            lo = mid + 1;
        }
    }
    cout << (feasible ? lo : -1) << '\n';
}
