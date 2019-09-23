// implicit graph, does a node dominate every other node
// https://open.kattis.com/problems/pearwise
// 2018 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

struct ballot {
    int votes;
    vector<int> ordering;
};

auto beats(int i, int j, const vector<ballot>& ballots) {
    array vote_counts = {0, 0};
    for (const auto& [votes, ordering] : ballots) {
        // earlier in ballot => wins ballot
        auto ipos = find(begin(ordering), end(ordering), i);
        auto jpos = find(begin(ordering), end(ordering), j);
        auto winner = ipos < jpos ? 0 : 1;
        vote_counts[winner] += votes;
    }
    return vote_counts[0] > vote_counts[1];
}

auto dfs(auto& g, int i, auto& visited) {
    if (visited[i]) return;
    visited[i] = true;
    for (int j = 0; j < g.size(); j++) {
        if (g[i][j]) {
            dfs(g, j, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<ballot> ballots(m);
    for (int i = 0; i < m; i++) {
        cin >> ballots[i].votes;
        string ordering;
        cin >> ordering;
        transform(begin(ordering), end(ordering), back_inserter(ballots[i].ordering),
                  [](char c) { return c - 'A'; });
    }

    auto can_beat = vector(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            can_beat[i][j] = beats(i, j, ballots);
        }
    }

    for (int i = 0; i < n; i++) {
        auto visited = vector<int>(n);
        dfs(can_beat, i, visited);

        auto candidate = char('A' + i);
        auto can_win = all_of(begin(visited), end(visited), [](auto vis) { return vis == 1; });
        cout << candidate << ": " << (can_win ? "can win" : "can't win") << '\n';
    }
}
