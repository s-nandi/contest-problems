// dp with rolling bitmasks, tiling area with the min # of lines
// https://community.topcoder.com/stat?c=problem_statement&pm=8397&rd=10806

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(a) (int)a.size()

const int MAXN = 11;
const int INF = 10212312;
int dp[MAXN * MAXN][1 << MAXN][2];

template <typename T>
T minn(T& a, T b) {
    if (b < a) {a = b; return true;}
    else return false;
}

struct FloorBoards {
    int n, m;
    int layout(vector<string> grid) {
        n = sz(grid);
        m = sz(grid[0]);
	/*
	 * dp[i][j][k] = min cost of tiling up to tile i with the previous vertical boards
	 * being represented by the bitmask j, and k is 1 iff there is a horizontal board to the left of i
	*/
        rep(i, 0, n * m + 1) {
            rep(j, 0, 1 << m) {
                rep(k, 0, 2) {
                    dp[i][j][k] = INF;
                }
            }
        }
        dp[0][0][0] = 0;

        rep(i, 0, n * m) {
            auto row = i / m;
            auto col = i % m;
            rep(bm, 0, 1 << m) {
                int res_bm = bm >> 1;
                int with_col_mask = res_bm + (1 << (m - 1));
                int without_col_mask = res_bm;
                auto best_ignore_hor = min(dp[i][bm][0], dp[i][bm][1]);
                if (grid[row][col] == '#') {
                    auto blocked = best_ignore_hor;
                    minn(dp[i + 1][without_col_mask][0], blocked);
                    continue;
                }
                if (bm & (1 << 0)) {
                    int continue_vert = best_ignore_hor;
                    minn(dp[i + 1][with_col_mask][0], continue_vert);
                }
                if (col > 0) {
                    int continue_hor = dp[i][bm][1];
                    minn(dp[i + 1][without_col_mask][1], continue_hor);
                }
                int new_vert = best_ignore_hor + 1;
                minn(dp[i + 1][with_col_mask][0], new_vert);
                int new_hor = best_ignore_hor + 1;
                minn(dp[i + 1][without_col_mask][1], new_hor);
            }   
        }
        auto best = INF;
        rep(bm, 0, 1 << m) {
            rep(h, 0, 2) {
                minn(best, dp[n * m][bm][h]);
            }
        }
        return best;
    }
};

//  Uncomment main to run locally
/*
int main() {
  vector<string> input = {".......",".#..##.",".#....." ,".#####." ,".##..#." ,"....###"};
  cout << FloorBoards{}.layout(input) << '\n';
}
*/
