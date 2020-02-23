// backtracking (brute force all permutations, rollback), pruning at each step
// https://open.kattis.com/problems/minibattleship
// 2020 North American Championships

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)

int n, k;
using changes = tuple<int, int, int>; // x, y, old
const char MISS = 'X';
const char HIT = 'O';
const char PLACED = 'Y';

auto dx = vector{0, 1};
auto dy = vector{1, 0};
auto good(auto& grid, int x, int y, int s, int dir) {
    bool valid = true;
    vector<changes> rollback;
    for(int k = 0; k < s; k++) {
        auto nx = x + k * dx[dir];
        auto ny = y + k * dy[dir];
        // cannot place ship on a miss, and cannot overlap ships
        if (nx >= n or ny >= n or grid[nx][ny] == PLACED or grid[nx][ny] == MISS) {
            valid = false;
            break;
        } else {
            rollback.push_back({nx, ny, grid[nx][ny]});
            grid[nx][ny] = PLACED;
        }
    }
    return pair{valid, rollback};
}

int solve(auto& grid, const auto& sizes, int it, int bm) {
    if (it == k) {
        bool valid = true;
        rep(i, 0, n)
            rep(j, 0, n)
              if (grid[i][j] == HIT) // hit but no ship placed
                  valid = false;
        return valid;
    }
    int dir = (bm & (1 << it)) ? 1 : 0;
    if (sizes[it] == 1 and dir == 1) return 0;
    auto acc = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            auto [valid, rollback] = good(grid, i, j, sizes[it], dir);
            if (valid)
                acc += solve(grid, sizes, it + 1, bm);
            for(auto [x, y, c]: rollback)
                grid[x][y] = c;
        }
    }
    return acc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    auto grid = vector(n, vector<char>(n));
    trav(row, grid) {
        trav(elem, row)
            cin >> elem;
    }
    vi sizes(k);
    trav(i, sizes)
        cin >> i;
    auto res = 0;
    rep(bm, 0, 1 << k)
        res += solve(grid, sizes, 0, bm);
    cout << res << '\n';
}
