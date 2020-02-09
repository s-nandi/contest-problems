// brute force (permutations)
// https://prognova18.kattis.com/problems/xorequation
// 2018 ProgNova

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a), end(a)
#define sz(a) (int)size(a)

auto getholes(const auto& s) {
    vector<int> holes;
    rep(i, 0, sz(s)) {
        if (s[i] == '?')
            holes.push_back(i);
    }
    return holes;
}

auto fillup(const auto& s, const auto& fixed, auto& it) {
    string res;
    trav(c, s) {
        if (c != '?') res += c;
        else {
            res += ('0' + fixed[it]);
            it++;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, x, b, eq, c;
    cin >> a >> x >> b >> eq >> c;

    auto aq = count(all(a), '?');
    auto bq = count(all(b), '?');
    auto cq = count(all(c), '?');

    vector<pair<int, string>> v = {{aq, a}, {bq, b}, {cq, c}};
    sort(all(v));

    tie(a, b, c) = tuple{v[0].second, v[1].second, v[2].second};
    tie(aq, bq, cq) = tuple{v[0].first, v[1].first, v[2].first};

    auto holes_a = getholes(a);
    auto holes_b = getholes(b);
    
    function<int(vector<int>&, int)> recurse =
        [&](vector<int>& fixed, int d) {
            int acc = 0;
            if (d < aq + bq) {
                auto ind = d < aq ? holes_a[d] : holes_b[d - aq];
                auto sz = d < aq ? sz(a) : sz(b);
                rep(place, 0, 10) {
                    if (sz != 1 && place == 0 && ind == 0) continue;
                    fixed.push_back(place);
                    acc += recurse(fixed, d + 1);
                    fixed.pop_back();
                }
            } else {
                int it = 0;
                auto fill_a = fillup(a, fixed, it);
                auto fill_b = fillup(b, fixed, it);
                auto res = to_string(stoi(fill_a) ^ stoi(fill_b));
                auto feasible = sz(res) == sz(c);
                if (feasible) {
                    rep(i, 0, sz(c)) {
                        if (c[i] != '?' and res[i] != c[i]) feasible = false;
                    }
                }
                acc = feasible;
            }
            return acc;
        };

    vector<int> fixed;
    auto sol = recurse(fixed, 0);
    cout << sol << '\n';
}
