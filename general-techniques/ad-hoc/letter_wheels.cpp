// fixing most positions to force last position, min # of +1/-1 to convert to same num
// https://open.kattis.com/problems/letterwheels
// 2020 North American Championship

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define sz(a) (int)size(a)
#define PB push_back

const int INF = 1031231234;

auto positions_rotations(string s) {
    map<string, vi> pos;
    vector<string> rot;
    rep(i, 0, sz(s)) {
        pos[s].PB(i);
        rot.PB(s);
        rotate(begin(s), begin(s) + 1, end(s));
    }
    return pair{pos, rot};
}

char excluded(char a, char b) {
    return 'A' + 'B' + 'C' - a - b;
}

// cost of normalizing all rots to the median rot
auto min_cost(int arot, int brot, int crot) {
    return max({arot, brot, crot}) - min({arot, brot, crot});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b, c;
    cin >> a >> b >> c;
    int n = sz(a);

    auto [bpos, brot] = positions_rotations(b);
    auto [cpos, crot] = positions_rotations(c);
    
    auto best = INF;
    rep(b_shift, 0, n) {
        string forced = "";
        bool feasible = true;
        rep(i, 0, n) {
            if (a[i] == brot[b_shift][i]) {
                feasible = false;
                break;
            }
            forced += excluded(a[i], brot[b_shift][i]);
        }
        if (!feasible or !cpos.count(forced)) continue;
        trav(c_shift, cpos[forced]) {
            auto b_shifts = vi{b_shift, b_shift - n};
            auto c_shifts = vi{c_shift, c_shift - n};
            rep(k1, 0, 2) rep(k2, 0, 2) {
                auto possible = min_cost(0, b_shifts[k1], c_shifts[k2]);
                best = min(best, possible);
            }
        }
    }
    cout << (best != INF ? best : -1) << '\n';
}
