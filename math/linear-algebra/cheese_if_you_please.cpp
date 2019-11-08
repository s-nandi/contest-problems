// linear programming (basic)
// https://open.kattis.com/problems/cheeseifyouplease
// 2019 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
constexpr ld EPS = 1e-9;

struct lp_constraints {
    vector<vector<ld>> A;
    vector<ld> b{0};

    lp_constraints(int n) : A{vector<ld>(n)} {}

    void add(auto lhs, bool less, ld rhs) {
        if (!less) {
            for (auto &e : lhs) e = -e;
            rhs = -rhs;
        }
        A.push_back(move(lhs));
        b.push_back(rhs);
    }
};

struct LPSolver {
    int m, n;
    vector<int> B, N;
    vector<vector<ld>> D;

    LPSolver(const auto &constraints, const vector<ld> &c)
        : m(constraints.b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<ld>(n + 2)) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) D[i][j] = constraints.A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = constraints.b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        ld inv = 1.0 / D[r][s];
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                for (int j = 0; j < n + 2; j++)
                    if (j != s) D[i][j] -= D[r][j] * D[i][s] * inv;
        for (int j = 0; j < n + 2; j++)
            if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++)
            if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (s < 0 || D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                    D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r])
                    r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    auto solve() -> tuple<optional<vector<ld>>, ld> {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] <= -EPS) {
            pivot(r, n);
            if (!simplex(1) || D[m + 1][n + 1] < -EPS)
                return {nullopt, -numeric_limits<ld>::infinity()};
            for (int i = 0; i < m; i++)
                if (B[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s])
                            s = j;
                    pivot(i, s);
                }
        }
        if (!simplex(2)) return {nullopt, numeric_limits<ld>::infinity()};
        auto x = vector<ld>(n);
        for (int i = 0; i < m; i++)
            if (B[i] < n) x[B[i]] = D[i][n + 1];
        return {x, D[m][n + 1]};
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<ld> limit(n);
    for (auto &lim : limit) {
        cin >> lim;
    }

    auto blend = vector(m, vector<ld>(n));
    auto profit = vector<ld>(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> blend[i][j];
        }
        cin >> profit[i];
    }

    auto constraints = lp_constraints(m);
    for (int i = 0; i < n; i++) {
        vector<ld> amt_in_each_blend(m);
        for (int j = 0; j < m; j++) {
            amt_in_each_blend[j] = blend[j][i];
        }
        constraints.add(amt_in_each_blend, true, limit[i]);
    }

    auto solver = LPSolver(constraints, profit);
    auto [sol, best] = solver.solve();
    best *= 100;  // scale up by 100 since coeffs were percentages in problem statement
    best = (long long)((best * 100) + 0.5);  // round to 2 decimal points

    cout << setprecision(2) << fixed << (best / 100.0) << '\n';
}
