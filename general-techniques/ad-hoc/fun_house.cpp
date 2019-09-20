// ad-hoc (simulation on grid)
// https://open.kattis.com/problems/funhouse
// 2014 Mid-Central USA Regional

#include <bits/stdc++.h>
using namespace std;

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

vector<int> backslashed_dir = {1, 0, 3, 2};
vector<int> forwardslashed_dir = {3, 2, 1, 0};

int r, c;
auto init_dir(int x, int y) {
    if (x == 0) return 1;
    if (y == 0) return 0;
    if (x == r - 1) return 3;
    if (y == c - 1) return 2;
    return -1;
}

int new_dir(int old_dir, char ch) {
    if (ch == '\\') {
        return backslashed_dir[old_dir];
    } else if (ch == '/') {
        return forwardslashed_dir[old_dir];
    }
    return old_dir;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int test = 1;; test++) {
        cin >> c >> r;
        if (c == 0 and r == 0) break;

        auto grid = vector(r, vector<char>(c));
        for (auto& row : grid) {
            for (auto& square : row) {
                cin >> square;
            }
        }

        int x, y;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == '*') {
                    x = i;
                    y = j;
                }
            }
        }

        int dir = init_dir(x, y);
        while (true) {
            x += dx[dir];
            y += dy[dir];
            dir = new_dir(dir, grid[x][y]);
            if (grid[x][y] == 'x') {
                grid[x][y] = '&';
                break;
            }
        }

        cout << "HOUSE " << test << '\n';
        for (auto& row : grid) {
            for (auto& elem : row) {
                cout << elem;
            }
            cout << '\n';
        }
    }
}
