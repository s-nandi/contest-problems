// bin search on answer, radial sweep (rotating circle around point), circular interval intersection (duplicate trick)
// https://open.kattis.com/problems/greatfireball
// 2018 South Central USA Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const auto MAXR = 1001.L;
const auto EPS = 1e-9;
constexpr auto PI2 = 2 * acos(-1.L);

using ptT = double;
struct pt {
    ptT x, y;
    ptT dist() const {return sqrt(x * x + y * y);}
};

auto normalize(auto theta) {
    // Normalizes to [0, 2PI] range, 0 radians is due east, angle increasing going ccw
    return (theta < 0) ? theta + PI2 : (theta > PI2 ? theta - PI2 : theta);
}

auto sgn_val(int i) {
    return i > 0 ? pair{i, 1} : pair{-i, -1};
}

auto num_feasible(const auto& p, auto r) {
    vector<pair<double, int>> q;
    rep(i, 0, sz(p)) {
        auto ang = normalize(atan2(p[i].y, p[i].x));
        auto d = p[i].dist();
        if (d >= 2 * r) continue;
        auto theta = acos(d / (2 * r));
        
        auto lang = normalize(ang - theta);
        auto rang = normalize(ang + theta);
        q.PB({lang, -(i + 1)}); // flip sign so increments come first in sort
        q.PB({rang, i + 1}); // 1-indexed since can't differentiate +0 and -0
    }
    sort(all(q));
    int m = sz(q);

    int best = 0, curr = 0;
    vi used(sz(p) + 1); // + 1 since 1-indexed above
    rep(i, 0, 2 * m) {
        auto [ang, sind] = i < m ? q[i] : q[i - m];
        auto [ind, delta] = sgn_val(sind);
        if (!used[ind] and delta == 1) continue;
        curr -= delta; // subtract since we flipped these earlier
        best = max(best, curr);
        used[ind] = (delta == -1);
    }
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pt> p(n);
    rep(i, 0, n) {
        cin >> p[i].x >> p[i].y;
    }
    auto lo = 0.L, hi = MAXR * MAXR;
    bool found = false;
    rep(iter, 0, 35) {
        auto mid = lo + (hi - lo) / 2;
        if (num_feasible(p, mid) >= k) {
            hi = mid;
            found = true;
        } else {
            lo = mid;
        }
    }
    if (!found) cout << -1 << '\n';
    else cout << fixed << setprecision(10) << lo << '\n';
}
