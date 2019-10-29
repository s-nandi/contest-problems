// constructing bipartite graph by drawing lines on plane, line - line segment intersection
// https://open.kattis.com/problems/urbandesign
// 2017 North Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using ptT = long long;
struct pt {
    ptT x, y;

    auto operator - (const pt& o) const {return pt{x - o.x, y - o.y};}
    auto operator ^ (const pt& o) const {return x * o.y - y * o.x;};
};

auto orientation(const pt& o, const pt& a, const pt& b) {
    auto cp = (b - o) ^ (a - o);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0);
} // cw : 1, ccw : -1, col : 0

auto intersects(const auto& p, const auto& q, const auto& a, const auto& b) {
    auto o1 = orientation(p, q, a);
    auto o2 = orientation(p, q, b);
    return o1 != o2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto lines = vector<pair<pt, pt>>(n);
    for (auto& l: lines) {
        ptT x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        l = {{x1, y1}, {x2, y2}};
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        ptT x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pt a = {x1, y1}, b = {x2, y2};
        int num_split = 0;
        for (const auto& [p, q]: lines) {
            auto is_intersecting = intersects(p, q, a, b);
            num_split += is_intersecting;
        }
        if (num_split & 1) {
            cout << "different" << '\n';
        } else {
            cout << "same" << '\n';
        }
    }
}
