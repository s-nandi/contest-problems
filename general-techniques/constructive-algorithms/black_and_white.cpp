// constructive algorithm, create grid with w white-connected-components and b black-connected-components
// https://codeforces.com/gym/100801/attachments (problem B)
// 2015 NEERC Northern Subregional

#include <bits/stdc++.h>
 
using namespace std;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
 
constexpr auto W = '.';
constexpr auto B = '@';
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    freopen("black.in", "r", stdin);
    freopen("black.out", "w", stdout);
  
    int b, w;
    cin >> b >> w;
 
    auto len = max(b, w) * 2;
    auto sol = vector(2, vector<char>(len, '0'));
 
    for (int i = 0; i < len; i += 2) {
        sol[0][i] = W;
        sol[0][i + 1] = B;
    }
 
    auto diff = abs(b - w);
    auto merge = (w < b ? W : B);
 
    if (b < w) {
        for (int i = 1; i < 2 * diff + 1; i++) {
            sol[1][i] = merge;
        }
    } else {
        for (int i = 0; i < 2 * diff; i++) {
            sol[1][i] = merge;
        }
    }
 
    rep(i, 0, len) {
        if (sol[1][i] == '0') {
            sol[1][i] = sol[0][i];
        }
    }
 
    int r = sol.size();
    int c = sol[0].size();
    cout << r << " " << c << '\n';
    for (auto& row: sol) {
        for (auto& elem: row) {
            cout << elem;
        }
        cout << '\n';
    } 
}
