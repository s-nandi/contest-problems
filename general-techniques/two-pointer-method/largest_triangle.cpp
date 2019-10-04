// 2 pointer trick, convex hull, maximal triangle in point set is subset of convex hull
// https://open.kattis.com/problems/largesttriangle
// 2018 Singapore Regional

#include <bits/stdc++.h>
using namespace std;

using ptT = long long;
struct pt {
    ptT x, y;

    auto operator*(const auto& o) const { return x * o.x + y * o.y; }
    auto operator^(const auto& o) const { return x * o.y - y * o.x; }
    auto operator-(const auto& o) const { return pt{x - o.x, y - o.y}; }
    auto operator<(const auto& o) const { return tie(y, x) < tie(o.y, o.x); }
    auto operator==(const auto& o) const { return x == o.x and y == o.y; }
};

auto triangle_area(const pt& o, const pt& a, const pt& b) { return (b - o) ^ (a - o); }
auto area(const pt& o, const pt& a, const pt& b) { return abs(triangle_area(o, a, b)); }
auto orientation(const auto& o, const auto& a, const auto& b) {
    auto cp = triangle_area(o, a, b);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0);
}  // cw : 1, ccw : -1, col : 0

auto convex_hull(auto& points) {
    sort(points.begin(), points.end());
    vector<pt> hull;
    for (int i = 0; i < 2; i++) {
        int s = hull.size();
        for (auto& p : points) {
            while (hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.back(), p) != 1) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(begin(points), end(points));
    }
    if (hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}

int next(auto i, auto step, auto mod) { return (i + step) % mod; }
int prev(auto i, auto step, auto mod) { return (i - step + mod) % mod; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pt> points(n);
    for (auto& p : points) {
        cin >> p.x >> p.y;
    }
    auto hull = convex_hull(points);
    n = hull.size();

    auto sol = 0LL;
    for (int l = 0; l < n; l++) {
        int k = l;
        for (int r = 0; r < n; r++) {
            while (true) {
                auto knext = next(k, 1, n);
                if (area(hull[l], hull[r], hull[knext]) > area(hull[l], hull[r], hull[k])) {
                    k = knext;
                } else {
                    break;
                }
            }
            auto possible = area(hull[l], hull[r], hull[k]);
            sol = max(possible, sol);
        }
    }
    cout << setprecision(11) << fixed << (double)sol / 2.0 << '\n';
}
