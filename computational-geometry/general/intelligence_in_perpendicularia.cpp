// geometry, counting length by pushing sides out to fill perimeter
// https://codeforces.com/gym/101612/attachments (problem I)
// 2017 NEERC Northern Subregional

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
 
using ptT = int;
struct pt {
    ptT x, y;
 
    auto dist(const auto& o) const {
        auto dx = x - o.x;
        auto dy = y - o.y;
        return abs(dx) + abs(dy);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    freopen("intel.in", "r", stdin);
    freopen("intel.out", "w", stdout);
 
    int n;
    cin >> n;
 
    auto a = vector<pt>(n);
    auto xs = vector<int>{}, ys = vector<int>{};
    trav(p, a) {
        cin >> p.x >> p.y;
        xs.push_back(p.x);
        ys.push_back(p.y);
    }
 
    auto perim = 0LL;
    rep(i, 0, n) {
        auto inext = i + 1 < n ? i + 1 : 0;
        perim += a[i].dist(a[inext]);
    }
 
    auto max_x = *max_element(all(xs));
    auto max_y = *max_element(all(ys));
    auto min_x = *min_element(all(xs));
    auto min_y = *min_element(all(ys));
    auto total = abs(2 * ((max_x - min_x) + (max_y - min_y)));
  
    auto sol = perim - total;
    cout << sol << '\n';
}
