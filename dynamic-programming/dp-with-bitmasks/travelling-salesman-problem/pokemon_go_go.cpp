// tsp (handling multiple positions for indistinguishable objects in the same category)
// https://open.kattis.com/problems/pokemongogo
// 2017 North Central NA Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto INF = 1031231234;

struct pt {
    int x, y;

    auto dist(const auto& o) const { return abs(x - o.x) + abs(y - o.y); }
};

// n pokemon, m categories
template <typename T>
T tsp(vector<vector<T>>& costs, auto& categories, auto& positions, int source, int num_ids) {
    int n = costs.size() - 1;
    int m = num_ids;

    vector<vector<T>> dp(1 << m, vector<T>(n, INF));
    for (int pokemon = 0; pokemon < n; pokemon++) {
        int category = categories[pokemon];
        dp[1 << category][pokemon] = costs[source][pokemon];
    }

    for (int bm = 1; bm < (1 << m); bm++) {
        for (int pokemon = 0; pokemon < n; pokemon++) {
            int i = categories[pokemon];
            if (bm & (1 << i)) {
                int sm = bm - (1 << i);
                for (int k2 = 0; k2 < n; k2++) {
                    int j = categories[k2];
                    if (sm & (1 << j))
                        dp[bm][pokemon] = min(dp[bm][pokemon], dp[sm][k2] + costs[k2][pokemon]);
                }
            }
        }
    }
    T sol = INF;
    int FULL = (1 << m) - 1;
    for (int i = 0; i < n; i++) sol = min(sol, dp[FULL][i] + costs[i][source]);
    return sol;
}

auto indexer(auto& mapping, auto elem) {
    if (mapping.count(elem)) {
        return mapping[elem];
    } else {
        int res = mapping.size();
        mapping[elem] = res;
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<string, int> names;
    vector<pt> positions;
    vector<int> ids;
    for (int i = 0; i < n; i++) {
        int x, y;
        string name;
        cin >> x >> y >> name;
        int id = indexer(names, name);
        ids.push_back(id);
        positions.push_back({x, y});
    }
    positions.push_back({0, 0});
    ids.push_back(names.size());
    n++;

    auto costs = vector(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            costs[i][j] = positions[i].dist(positions[j]);
        }
    }

    auto sol = tsp(costs, ids, positions, n - 1, names.size());
    cout << sol << '\n';
}
